#include "model3d.h"
#include <QFile>
#include <QTextStream>
#include <QVarLengthArray>
#include <QtOpenGL>

Model3D::Model3D(QString _filename)
    : filename(_filename)
{
}

QString Model3D::getFilename() const
{
    return filename;
}

void Model3D::setFilename(QString _filename)
{
    filename = _filename;
}

void Model3D::loadModel()
{
    if (filename.isEmpty()) return;

    QString ext = filename.toLower().mid(filename.size()-4);
    if ( ext != ".obj" && ext != ".off")
        return;

    // loading the model
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    QVector3D boundsMin( 1e9, 1e9, 1e9);
    QVector3D boundsMax(-1e9,-1e9,-1e9);

    if (ext == ".off")
    { // readOff

        QString input = in.readLine();

        if (!input.toUpper().contains("OFF"))
            return;

        input = in.readLine();
        QStringList tokens = input.split(' ');
        int faces, vertex;

        if (tokens.size() < 2) return;

        vertex = QString( tokens[0] ).toInt();
        faces = QString( tokens[1] ).toInt();

        while(vertex > 0) // reading the vertex
        {
            QVector3D p;
            input = in.readLine();
            tokens = input.split(' ');

            if (tokens.size() < 3) return;

            p.setX( tokens[0].toDouble() );
            p.setY( tokens[1].toDouble() );
            p.setZ( tokens[2].toDouble() );

            boundsMin.setX( qMin(boundsMin.x(), p.x()) );
            boundsMin.setY( qMin(boundsMin.y(), p.y()) );
            boundsMin.setZ( qMin(boundsMin.z(), p.z()) );

            boundsMax.setX( qMax(boundsMax.x(), p.x()) );
            boundsMax.setY( qMax(boundsMax.y(), p.y()) );
            boundsMax.setZ( qMax(boundsMax.z(), p.z()) );

            points.push_back(p);
            vertex -= 1;
        }

        while(faces > 0) // reading the faces
        {
            input = in.readLine();
            tokens = input.split(' ');

            if (tokens.size() < 4) return;

            pointIndices << tokens[1].toInt();
            pointIndices << tokens[2].toInt();
            pointIndices << tokens[3].toInt();

            faces -= 1;
        }
    }
    else if (ext == ".obj")
    { // readObj

        while (!in.atEnd())
        {
            QString input = in.readLine();
            if (input.isEmpty() || input[0] == '#')
                continue;

            QTextStream ts(&input);
            QString id;
            ts >> id;

            if (id == "v")
            {
                double tmp;
                QVector3D p;
                ts >> tmp; p.setX(tmp);
                ts >> tmp; p.setY(tmp);
                ts >> tmp; p.setZ(tmp);

                boundsMin.setX( qMin(boundsMin.x(), p.x()) );
                boundsMin.setY( qMin(boundsMin.y(), p.y()) );
                boundsMin.setZ( qMin(boundsMin.z(), p.z()) );

                boundsMax.setX( qMax(boundsMax.x(), p.x()) );
                boundsMax.setY( qMax(boundsMax.y(), p.y()) );
                boundsMax.setZ( qMax(boundsMax.z(), p.z()) );

                points.push_back(p);
            }
            else if (id == "f" || id == "fo")
            {
                QVarLengthArray<int, 4> p;

                while (!ts.atEnd())
                {
                    QString vertex;
                    ts >> vertex;
                    const int vertexIndex = vertex.split('/').value(0).toInt();
                    if (vertexIndex)
                        p.append(vertexIndex > 0 ? vertexIndex - 1 : points.size() + vertexIndex);
                }

                for (int i = 0; i < p.size(); ++i)
                {
                    int edgeA = p[i];
                    int edgeB = p[(i + 1) % p.size()];

                    if (edgeA < edgeB)
                        edgeIndices << edgeA << edgeB;
                }

                for (int i = 0; i < 3; ++i)
                    pointIndices << p[i];

                if (p.size() == 4)
                {
                    for (int i = 0; i < 3; ++i)
                        pointIndices << p[(i + 2) % 4];
                }
            }
        }
    }

    QVector3D bounds = boundsMax - boundsMin;
    qreal scale = 1 / qMax(bounds.x(), qMax(bounds.y(), bounds.z()));
    for (int i = 0; i < points.size(); ++i)
        points[i] = (points[i] - (boundsMin + bounds * 0.5)) * scale;

    computeNormals();

    // set the length
    QVector3D len;
    len.setX( ( fabs(boundsMin.x()) + fabs(boundsMax.x()) ) * scale );
    len.setY( ( fabs(boundsMin.y()) + fabs(boundsMax.y()) ) * scale );
    len.setZ( ( fabs(boundsMin.z()) + fabs(boundsMax.z()) ) * scale );

    setLength(len);
}

void Model3D::computeNormals()
{
    normals.resize(points.size());
    for (int i = 0; i < pointIndices.size(); i += 3) {
        QVector3D a = points.at(pointIndices.at(i));
        QVector3D b = points.at(pointIndices.at(i+1));
        QVector3D c = points.at(pointIndices.at(i+2));

        QVector3D normal = QVector3D::crossProduct(b - a, c - a);
        normal.normalize();

        for (int j = 0; j < 3; ++j)
            normals[pointIndices.at(i + j)] += normal;
    }

    for (int i = 0; i < normals.size(); ++i)
        normals[i].normalize();
}

void Model3D::draw()
{   
    glColor3f(color.redF(), color.greenF(), color.blueF());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, (float *)points.data());
    glNormalPointer(GL_FLOAT, 0, (float *)normals.data());
    glDrawElements(GL_TRIANGLES, pointIndices.size(), GL_UNSIGNED_INT, pointIndices.data());

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

QVector<QVector3D> Model3D::getPoints() const
{
    return points;
}

QVector<QVector3D> Model3D::getNormals() const
{
    return normals;
}

QVector<int> Model3D::getEdgeIndices() const
{
    return edgeIndices;
}

QVector<int> Model3D::getPointIndices() const
{
    return pointIndices;
}

void Model3D::setPoints(QVector<QVector3D> _points)
{
    points =_points;
}

void Model3D::setNormals(QVector<QVector3D> _normals)
{
    normals = _normals;
}


void Model3D::setEdgeIndices(QVector<int> _indices)
{
    edgeIndices = _indices;
}

void Model3D::setPointIndices(QVector<int> _indices)
{
    pointIndices = _indices;
}
