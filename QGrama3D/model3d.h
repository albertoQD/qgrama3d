#ifndef MODEL3D_H
#define MODEL3D_H
#include "object3d.h"
#include <QVector>
#include <QFile>

using namespace std;

class Model3D : public Object3D
{
public:
    Model3D(QString _filename = QString());

    virtual void draw();
    QString getFilename() const;
    void setFilename(QString _filename);
    void loadModel();
    QVector<QVector3D> getPoints() const;
    QVector<QVector3D> getNormals() const;
    QVector<int> getEdgeIndices() const;
    QVector<int> getPointIndices() const;
    void setPoints(QVector<QVector3D> _points);
    void setNormals(QVector<QVector3D> _normals);
    void setEdgeIndices(QVector<int> _indices);
    void setPointIndices(QVector<int> _indices);

protected:
    void computeNormals();

private:
    QString filename;
    QVector<QVector3D> points;
    QVector<QVector3D> normals;
    QVector<int> edgeIndices;
    QVector<int> pointIndices;
};

#endif // MODEL3D_H
