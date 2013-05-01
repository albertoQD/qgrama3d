#include "qgrama3d.h"
#include "cube.h"
#include "model3d.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <QVector3D>
#include <QtOpenGL>
#include <QtGui>
#include <math.h>
#include <QDomDocument>
#include <iostream>
#include <QInputDialog>

#define MODE_SELECT     0x0000
#define MODE_MOVE       0x0001
#define MODE_CONNECT    0x0002
#define MODE_DISCONNECT 0x0003
#define VELOCITY        3.5


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

using namespace std;

QGrama3D::QGrama3D(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    , xRot(0), yRot(0), zRot(0), scale(1)
    , xTrans(0.0f), yTrans(0.0f), selectedItem(-1)
    , lastSelected(-1)
    , background(17, 17, 17)
    , mode(MODE_SELECT)
    , fileLoaded("")
    , linksVisible(true)
    , selectionColor(255, 255, 255)
    , axisColor(255, 255, 0)
    , labelsColor(255, 255, 255)
    , labelsVisible(true)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setCursor(Qt::OpenHandCursor);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
}

QGrama3D::~QGrama3D()
{
}

QSize QGrama3D::minimumSizeHint() const
{
    return QSize(100, 50);
}

QSize QGrama3D::sizeHint() const
{
    return QSize(800, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0) angle += 360 * 16;
    while (angle > 360 * 16) angle -= 360 * 16;
}

void QGrama3D::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void QGrama3D::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void QGrama3D::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void QGrama3D::setXTranslation(int amount)
{
    if (amount != xTrans)
    {
        xTrans = amount;
        emit xTranslated(amount);
        updateGL();
    }
}

void QGrama3D::setYTranslation(int amount)
{
    if (amount != yTrans)
    {
        yTrans = amount;
        emit yTranslated(amount);
        updateGL();
    }
}

void QGrama3D::initializeGL()
{
    qglClearColor(background);
    GLfloat light_pos[] = {1.0, 1.0, 1.0, 0.0};

    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
}

void QGrama3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef( -xTrans, yTrans, -10.0); // -5 So it's in the range on the zNear and zFar projection
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glScalef(scale, 2*scale, scale); // *2 because of the windows size
    glRasterPos2f(0, 0);

    // draw all objects
    if (linksVisible) drawLinks();

    for (unsigned int i=0;i<objects.size(); i+=1)
    {
        if (!deleted[i])
        {

            glLoadName((GLuint) i);

            QVector3D center = objects[i]->getCenter();
            glPushMatrix();
            glTranslatef( center.x(), center.y(), center.z() );
            objects[i]->draw();
            glPopMatrix();

            if (objects[i]->isSelected())
            {

                glColor3f(selectionColor.redF(), selectionColor.greenF(), selectionColor.blueF());
                objects[i]->drawSelected();

                if (mode == MODE_MOVE)
                {
                    glColor3f(axisColor.redF(), axisColor.greenF(), axisColor.blueF());
                    objects[i]->drawAxis();
                }
            }

            if (labelsVisible)
            {
                glColor3f(labelsColor.redF(), labelsColor.greenF(), labelsColor.blueF());
                objects[i]->drawLabel();
            }
        }
    }
}

void QGrama3D::drawLinks()
{
    glLineWidth(2.0);
    map< pair<int, int>, QColor >::iterator it;

    for (it = links.begin(); it != links.end(); it++)
    {
        QVector3D c1 = objects[it->first.first]->getCenter(); // first node
        QVector3D c2 = objects[it->first.second]->getCenter(); // second node
        QColor color = it->second; // link color

        glColor3f(color.redF(), color.greenF(), color.blueF());
        glBegin(GL_LINES);
            glVertex3f( c1.x(), c1.y(), c1.z());
            glVertex3f( c2.x(), c2.y(), c2.z());
        glEnd();
    }

    glLineWidth(1.0);
}

void QGrama3D::resizeGL(int width, int height)
{
    // the size of the viewport is the new size of the window
    glViewport(0, 0, width, height);

    // select the PROJECTION matrix to operate on
    glMatrixMode(GL_PROJECTION);

    // load a clean Identity matrix
    glLoadIdentity();

    // glOrtho for an orthographic projection
//    glOrtho(-150, 150, -150, 150, 5.0, 200);

    // glFrustum for a perspective projection
    glFrustum(-2, 2, -2, 2, 2.0, 40.0);

    // change now to the normal MODELVIEW mode
    glMatrixMode(GL_MODELVIEW);
}

void QGrama3D::mousePressEvent(QMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);

    lastPos = event->pos();
    int selection = selectObject(lastPos.x(), lastPos.y());

    if (mode == MODE_SELECT)
    {
        if (selectedItem != -1)
        {
            objects[selectedItem]->unselect();
            selectedItem = -1;
        }
        if (selection != -1)
        {
            selectedItem = selection;
            objects[selectedItem]->select();
        }
    }
    else if (mode == MODE_MOVE)
    {
        lastSelected = selectedItem;

        if (selection != selectedItem)
        {
            if (selectedItem != -1)
            {
                objects[selectedItem]->unselect();
                selectedItem = -1;
            }

            if (selection != -1)
            {
                selectedItem = selection;
                objects[selectedItem]->select();
                setSelectMode();
            }
            else
            {
                setSelectMode();
            }
        }
    }
    else if (mode == MODE_CONNECT)
    {
        if (selection != -1)
        {
            if (selectedItem != -1)
                lastSelected = selectedItem;

            selectedItem = selection;

            if (lastSelected != -1)
            { // there is two alredy selected, so, do the linking
                // show Color Dialog
                QColor color = QColorDialog::getColor( Qt::white, this, tr("Select the color for the link"));

                if (color.isValid())
                { // do the connection only if the color is valid
                    pair<int, int> mp = (lastSelected < selectedItem) ?
                                            make_pair(lastSelected, selectedItem) :
                                            make_pair(selectedItem, lastSelected);

                    links[mp] = color;
                }
                // unselect both
                objects[lastSelected]->unselect();
                lastSelected = -1;
                selectedItem = -1;
                // exit connect mode
                setSelectMode();
            }
        }
        else
        {
            if (selectedItem != -1)
            {
                objects[selectedItem]->unselect();
                selectedItem = -1;
            }
            setSelectMode();
        }
    }
    else if (mode == MODE_DISCONNECT)
    {
        if (selection != -1)
        {
            if (selectedItem != -1)
                lastSelected = selectedItem;

            selectedItem = selection;

            if (lastSelected != -1)
            { // there is two alredy selected, so, do the UNlinking
                pair<int, int> mp = (lastSelected < selectedItem) ?
                                        make_pair(lastSelected, selectedItem) :
                                        make_pair(selectedItem, lastSelected);

                // Look for the right link and delete
                links.erase( links.find(mp) );
//                set< pair< pair<int, int>, QColor> >::iterator it = links.begin();
//                for (it; it != links.end(); ++it)
//                {
//                    if ( (*it).first.first == mp.first && (*it).first.second == mp.second )
//                    {
//                        links.erase(it);
//                        break;
//                    }
//                }

                // with the linking done unselect both
                objects[lastSelected]->unselect();
                lastSelected = -1;
                selectedItem = -1;
                // exit disconnect mode
                setSelectMode();
            }
        }
        else{
            if (selectedItem != -1)
            {
                objects[selectedItem]->unselect();
                selectedItem = -1;
            }
            setSelectMode();
        }
    }

    updateGL();
}

void QGrama3D::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void QGrama3D::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if (mode == MODE_MOVE)
        {
            if (selectedItem != -1 && (lastSelected == selectedItem))
            { // move object
                QVector3D center = objects[selectedItem]->getCenter();

                GLint view[4]; // for the viewport
                GLdouble model[16]; // for the modelview matrix
                GLdouble proj[16]; // for the projection matrix
                GLdouble    camx0, camy0, camz0, // coord of camera at z = 0
                            camx1, camy1, camz1, // coord of camera at z = 1
                            x1, y1, z1, // curren pos of mouse
                            lastx, lasty, lastz, winz; // last pos of mouse

                glGetIntegerv(GL_VIEWPORT, view);
                glGetDoublev(GL_MODELVIEW_MATRIX, model);
                glGetDoublev(GL_PROJECTION_MATRIX, proj);

                // to get camera center
                gluUnProject((view[2]-view[0])/2 , (view[3]-view[1])/2,
                    0.0,
                    model, proj, view,
                    &camx0,&camy0,&camz0);

                gluUnProject((view[2]-view[0])/2 , (view[3]-view[1])/2,
                    1.0,
                    model, proj, view,
                    &camx1,&camy1,&camz1);

                // to project the mouse coords
                glReadPixels( event->x(), event->y(), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz );
                gluUnProject( event->x(), event->y(), winz,
                    model, proj, view,
                    &x1,&y1,&z1);

                gluUnProject( lastPos.x(), lastPos.y(), winz,
                    model, proj, view,
                    &lastx,&lasty,&lastz);

                if ( fabs((float) (camx1 - camx0)) < fabs((float)(camz1 - camz0)) )
                { // muevo en x
                    center.setX(center.x() + (x1 - lastx)*VELOCITY);
                }
                else
                { // muevo en z
                    center.setZ(center.z() + (z1 - lastz)*VELOCITY);
                }

                // muevo en Y
                center.setY(center.y() - (y1 - lasty)*VELOCITY);

                objects[selectedItem]->setCenter(center);
            }
            else
            { // exit move mode and enter select mode
                mode =  MODE_SELECT;
            }
        }
        else if (mode == MODE_SELECT)
        {
            setXRotation(xRot + 8 * dy);
            setYRotation(yRot + 8 * dx);
        }
    }
//    else if (event->buttons() & Qt::RightButton)
//    {
//        if (mode == MODE_SELECT)
//        {
//            setXRotation(xRot + 8 * dy);
//            setZRotation(zRot + 8 * dx);
//        }
//    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        setXTranslation(xTrans + dx*0.6);
        setYTranslation(yTrans + dy*0.6);
    }

    lastPos = event->pos();
    updateGL();
}

void QGrama3D::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? scale += scale*0.1f : scale -= scale*0.1f;
    updateGL();
}

int QGrama3D::selectObject(int x, int y)
{
    GLuint buff[64] = {0};
    GLint hits, view[4];
    int index = 0;
    unsigned int minZ = 0xffffffff;

    glSelectBuffer(64, buff);
    glGetIntegerv(GL_VIEWPORT, view);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluPickMatrix(x, view[3]-y, 1.0, 1.0, view);
        glFrustum(-5, 5, -5, 5, 5.0, 40.0);
        glMatrixMode(GL_MODELVIEW);
        swapBuffers();
        updateGL();
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    hits = glRenderMode(GL_RENDER);
    glMatrixMode(GL_MODELVIEW);

    if (hits == 0) return -1;

    for (int i = 0; i < hits; i++)
    {
        if (buff[i*4+1] < minZ)
        {
            minZ  = buff[i*4+1];
            index = (int) buff[i*4+3];
        }
    }

    return index;
}

void QGrama3D::showContextMenu(const QPoint &point)
{
    if (selectedItem == -1) return;

    // check the position of the click
    QPoint globalPos = this->mapToGlobal(point);
    QMenu _menu;
    QAction * _moveAction = new QAction(tr("&Move"), this);
    QAction * _linkAction = new QAction(tr("&Link"), this);
    QAction * _unlinkAction = new QAction(tr("&Unlink"), this);
    QAction * _deleteAction = new QAction(tr("&Delete"), this);
    QAction * _editLabelAction = new QAction(tr("&Edit Label"), this);

    _unlinkAction->setDisabled(true);

    // check if the selected item is already linked with any other node
    map< pair<int, int>, QColor >::iterator it = links.begin();
    for (it; it != links.end(); ++it)
    {
        if ( it->first.first == selectedItem ||
             it->first.second == selectedItem )
        {
            _unlinkAction->setEnabled(true);
            break;
        }
    }

    // connect actions with slots
    connect(_moveAction,   SIGNAL(triggered()), this, SLOT(setMoveMode()));
    connect(_linkAction,   SIGNAL(triggered()), this, SLOT(setConnectMode()));
    connect(_unlinkAction, SIGNAL(triggered()), this, SLOT(setDisconnectMode()));
    connect(_deleteAction, SIGNAL(triggered()), this, SLOT(deleteNode()));
    connect(_editLabelAction, SIGNAL(triggered()), this, SLOT(showEditLabel()));

    // add all actions to menu
    _menu.addAction(_moveAction);
    _menu.addAction(_linkAction);
    _menu.addAction(_unlinkAction);
    _menu.addAction(_editLabelAction);
    _menu.addSeparator();
    _menu.addAction(_deleteAction);

    // show the menu
    if (!_menu.exec(globalPos)) setSelectMode();
    updateGL();
}

void QGrama3D::setMoveMode()
{
    if (selectedItem == -1) return;
    mode = MODE_MOVE;
}

void QGrama3D::setConnectMode()
{
    if (selectedItem == -1) return;
    mode = MODE_CONNECT;
}

void QGrama3D::setSelectMode()
{
    mode = MODE_SELECT;
}

void QGrama3D::setDisconnectMode()
{
    if (selectedItem == -1) return;
    mode = MODE_DISCONNECT;
}

void QGrama3D::deleteNode()
{
    if (selectedItem == -1) return;

    // first delete all links to/from this node
    map< pair<int, int>, QColor >::iterator it;
    for (it = links.begin(); it != links.end(); ++it)
    {
        if ( it->first.first == selectedItem ||
             it->first.second == selectedItem )
        {
            links.erase(it);
        }
    }

    deleted[selectedItem] = true;
    selectedItem = -1;
}

void QGrama3D::changeLinksVisibility()
{
    linksVisible = !linksVisible;
    updateGL();
}

void QGrama3D::changeLabelsVisibility()
{
    labelsVisible = !labelsVisible;
    updateGL();
}

bool QGrama3D::saveInFile(const QString &filename)
{
    if (!filename.isEmpty())
        fileLoaded = filename;

    if (fileLoaded.isEmpty())
    {
        fileLoaded = QDir::toNativeSeparators(QDir::homePath()) + "/default.xml";
    }

    QFile file(fileLoaded);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return false;
    }

    QDomDocument document;
    if( !document.setContent( getXML(), false) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        file.close();
        return false;
    }

    QTextStream stream( &file );
    stream << document.toString();

    file.close();
    return true;
}

bool QGrama3D::loadFromFile(const QString &filename)
{
    if (filename.isEmpty()) return false;

    QFile inFile(filename);
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return false;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return false;
    }

    inFile.close();
    fileLoaded = filename; // for future saving

    // clear all data containers
    links.clear();
    objects.clear();
    deleted.clear();

    QDomElement _root = document.documentElement();
    // Check if it is a QGrama3D
    if (_root.tagName() != "QGrama3D")  return false;

    QDomNode child = _root.firstChild();

    // *** MODELS ***
    if (child.toElement().tagName() != "models")
    {
        qDebug("File bad formatted - No models?");
        return false;
    }

    QVector<Model3D *> models;
    if (!child.hasChildNodes())
    {
        return true;
    }

    QDomNode _model = child.firstChild();
    while (!_model.isNull())
    {
        if (_model.toElement().tagName() != "model") continue;
        Model3D * tmp_model = new Model3D();

        // Read the Base64 text
        QByteArray arr = QByteArray::fromBase64(QByteArray(_model.toElement().text().toStdString().c_str()));
        QDataStream in (&arr, QIODevice::ReadOnly);
        QString fname; in >> fname;
        int size; in >> size;

        // Read the points
        QVector<QVector3D> points(size);
        for (int i=0; i<size; i+=1)
        {
            double x, y, z;
            in >> x >> y >> z;
            points[i] = QVector3D(x, y, z);
        }

        // Read the normals
        in >> size;
        QVector<QVector3D> normals(size);
        for (int i=0; i<size; i+=1)
        {
            double x, y, z;
            in >> x >> y >> z;
            normals[i] = QVector3D(x, y, z);
        }

        // Read the edge indices
        in >> size;
        QVector<int> edges(size);
        for (int i=0; i<size; i+=1)
            in >> edges[i];

        // Read the edge indices
        in >> size;
        QVector<int> pointIndices(size);
        for (int i=0; i<size; i+=1)
            in >> pointIndices[i];

        tmp_model->setFilename(fname);
        tmp_model->setPoints(points);
        tmp_model->setNormals(normals);
        tmp_model->setEdgeIndices(edges);
        tmp_model->setPointIndices(pointIndices);

        models.push_back(tmp_model);
        _model = _model.nextSibling();
    }
    child = child.nextSibling();

    // *** OBJECTS ***
    if (child.toElement().tagName() != "objects")
    {
        qDebug("File bad formatted - No objects?");
        return false;
    }


    int _nobjects = child.toElement().attribute("quantity").toInt();
    objects = vector<Object3D *>(_nobjects);
    deleted = vector<bool>(_nobjects, false);

    if (!child.hasChildNodes())
    {
        return true;
    }

    QDomNode _obj = child.firstChild();
    for (int i=0; i<_nobjects; i+=1)
    {
        if (_obj.toElement().tagName() != "object") continue;

        int id = _obj.toElement().attribute("id").toInt();
        bool model = (_obj.toElement().attribute("predefined") == "0");
        if (model) objects[id] = new Model3D();
        else objects[id] = new Cube();

        QDomNode _innerObj = _obj.firstChild();
        while (!_innerObj.isNull())
        {
            if (_innerObj.toElement().tagName() == "center")
            {
                double x,y,z;
                x = _innerObj.toElement().attribute("x").toDouble();
                y = _innerObj.toElement().attribute("y").toDouble();
                z = _innerObj.toElement().attribute("z").toDouble();
                objects[id]->setCenter(QVector3D(x, y, z));
            }
            else if (_innerObj.toElement().tagName() == "color")
            {
                int r,g,b;
                r = _innerObj.toElement().attribute("r").toInt();
                g = _innerObj.toElement().attribute("g").toInt();
                b = _innerObj.toElement().attribute("b").toInt();
                objects[id]->setColor(QColor(r, g, b));
            }
            else if (_innerObj.toElement().tagName() == "length")
            {
                double x,y,z;
                x = _innerObj.toElement().attribute("x").toDouble();
                y = _innerObj.toElement().attribute("y").toDouble();
                z = _innerObj.toElement().attribute("z").toDouble();

                objects[id]->setLength(QVector3D(x, y, z));
            }
            else if (_innerObj.toElement().tagName() == "label")
            {
                objects[id]->setLabel(_innerObj.toElement().text());
            }
            else if (_innerObj.toElement().tagName() == "model")
            {
                int index = _innerObj.toElement().text().toInt();
                dynamic_cast<Model3D *> (objects[i])->setFilename( models[index]->getFilename() );
                dynamic_cast<Model3D *> (objects[i])->setPoints( models[index]->getPoints() );
                dynamic_cast<Model3D *> (objects[i])->setNormals( models[index]->getNormals() );
                dynamic_cast<Model3D *> (objects[i])->setEdgeIndices( models[index]->getEdgeIndices() );
                dynamic_cast<Model3D *> (objects[i])->setPointIndices( models[index]->getPointIndices() );
            }

            _innerObj = _innerObj.nextSibling();
        }

        _obj = _obj.nextSibling();
    }

    // *** LINKS ***
    child = child.nextSibling();
    if (child.toElement().tagName() != "links")
    {
        qDebug("File bad formatted - No links?");
        return false;
    }

    if (!child.hasChildNodes())
    {
        return true;
    }

    QDomNode _link = child.firstChild();
    while (!_link.isNull())
    {
        if (_link.toElement().tagName() == "link")
        {
            int id1, id2, red, green, blue;
            id1 = _link.toElement().attribute("id1").toInt();
            id2 = _link.toElement().attribute("id2").toInt();
            red = _link.toElement().attribute("r").toInt();
            green = _link.toElement().attribute("g").toInt();
            blue = _link.toElement().attribute("b").toInt();

            links[make_pair(id1, id2)] = QColor(red, green, blue);
        }

        _link = _link.nextSibling();
    }

    return true;
}

bool QGrama3D::isEmpty()
{
    return (objects.size() == 0);
}

void QGrama3D::updateObjects()
{
    for (int i=(deleted.size()-1); i >=0; i-=1)
    {
        if (deleted[i])
        { // actualizo desde i hasta end en links
            map< pair<int, int>, QColor >::iterator it = links.begin();
            for (it; it != links.end(); ++it)
            {
                pair<int, int> mp = it->first;
                QColor color = it->second;
                if (mp.first > i && mp.first < deleted.size())
                    mp.first -= 1;

                if (mp.second > i && mp.second < deleted.size())
                    mp.second -= 1;

                links.erase(it);
                links[mp] = color;
            }

            objects.erase(objects.begin() + i);
        }
    }

    deleted = vector<bool>(objects.size(), false);
}

QString QGrama3D::getXML()
{
    updateObjects();

    QString exportedXML;
    exportedXML = "<?xml version=\"1.0\" encoding='UTF-8'?>";
    exportedXML.append("<QGrama3D version=\"1.0\">");

    //  *** MODELS ***
    QVector<QString> files;
    int index = 0;
    exportedXML.append("<models>");
    for (int i=0; i<objects.size(); i+=1)
    {
        if (dynamic_cast<Model3D *> (objects[i]) != 0)
        { // is a model
            Model3D * obj = dynamic_cast<Model3D *> (objects[i]);

            if (!files.contains(obj->getFilename()))
            {
                files << obj->getFilename();
                exportedXML.append(QString("<model id=\"%1\">").arg(QString().setNum( index++ )));
                QByteArray arr;
                QDataStream out(&arr, QIODevice::WriteOnly);
                // First of all -> the filename
                out << obj->getFilename();
                // first the points
                QVector<QVector3D> points = obj->getPoints();
                out << points.size();
                for (int t=0; t<points.size(); t+=1)
                    out << points[t].x() << points[t].y() << points[t].z();
                // then the normals
                QVector<QVector3D> normals = obj->getNormals();
                out << normals.size();
                for (int t=0; t<normals.size(); t+=1)
                    out << normals[t].x() << normals[t].y() << normals[t].z();
                // then the Edge Indices
                QVector<int> edges = obj->getEdgeIndices();
                out << edges.size();
                for (int t=0; t<edges.size(); t+=1)
                    out << edges[t];

                // finally the Point Indices
                QVector<int> pointIndices = obj->getPointIndices();
                out << pointIndices.size();
                for (int t=0; t<pointIndices.size(); t+=1)
                    out << pointIndices[t];

                exportedXML.append(arr.toBase64());
                exportedXML.append(QString("</model>"));
            }
        }
    }
    exportedXML.append("</models>");

    //  *** OBJECTS ***
    exportedXML.append(QString("<objects quantity=\"%1\">")
            .arg(QString().setNum(objects.size())));
    for (int i=0; i<objects.size(); i+=1)
    {
        bool cube = (dynamic_cast<Cube *> (objects[i]) != 0);

        exportedXML.append(QString("<object predefined=\"%1\" id=\"%2\">")
                .arg(QString().setNum( cube ))
                .arg(QString().setNum( i )));
        exportedXML.append(QString("<center x=\"%1\" y=\"%2\" z=\"%3\"></center>")
                .arg(QString().setNum(objects[i]->getCenter().x()))
                .arg(QString().setNum(objects[i]->getCenter().y()))
                .arg(QString().setNum(objects[i]->getCenter().z())));
        exportedXML.append(QString("<color r=\"%1\" g=\"%2\" b=\"%3\"></color>")
                .arg(QString().setNum(objects[i]->getColor().red()))
                .arg(QString().setNum(objects[i]->getColor().green()))
                .arg(QString().setNum(objects[i]->getColor().blue())));
        QVector3D len = objects[i]->getLength();
        exportedXML.append(QString("<length x=\"%1\" y=\"%2\" z=\"%3\"></length>")
                .arg(QString().setNum(len.x()))
                .arg(QString().setNum(len.y()))
                .arg(QString().setNum(len.z())));
        exportedXML.append(QString("<label>%1</label>")
                .arg(objects[i]->getLabel()));

        if (!cube)
        {
            int index = files.toList().indexOf(dynamic_cast<Model3D *> (objects[i])->getFilename());
            exportedXML.append(QString("<model>%1</model>")
                    .arg(QString().setNum(index)));
        }
        exportedXML.append("</object>");
    }
    exportedXML.append("</objects>");

    //  *** LINKS ***
    exportedXML.append(QString("<links quantity=\"%1\">")
                       .arg(QString().setNum(links.size())));

    map< pair<int, int>, QColor >::iterator it = links.begin();
    for (it; it != links.end(); ++it)
    {
        exportedXML.append(QString("<link id1=\"%1\" id2=\"%2\" r=\"%3\" g=\"%4\" b=\"%5\"></link>")
                .arg(QString().setNum( it->first.first ))
                .arg(QString().setNum( it->first.second ))
                .arg(QString().setNum( it->second.red() ))
                .arg(QString().setNum( it->second.green() ))
                .arg(QString().setNum( it->second.blue()) ));
    }
    exportedXML.append("</links>");
    exportedXML.append("</QGrama3D>");

    return exportedXML;
}

void QGrama3D::setFileLoaded(const QString &filename)
{
    fileLoaded = filename;
}

QString QGrama3D::getFileLoaded() const
{
    return fileLoaded;
}

void QGrama3D::addNode(Object3D *obj)
{
    objects.push_back(obj);
    deleted.push_back(false);
    updateGL();
}

void QGrama3D::setLabelsColor(QColor _newColor)
{
    labelsColor = _newColor;
}

void QGrama3D::setBackgroundColor(QColor _newColor)
{
    background = _newColor;
    qglClearColor(background);
}

void QGrama3D::setSelectionColor(QColor _newColor)
{
    selectionColor = _newColor;
}

void QGrama3D::setAxisColor(QColor _newColor)
{
    axisColor = _newColor;
}

void QGrama3D::showEditLabel()
{
    QString _newLabel = QInputDialog::getText(this,
                                              tr("Edit Node label"),
                                              tr("Label"),
                                              QLineEdit::Normal,
                                              objects[selectedItem]->getLabel());

    // I don't give a ... if it's more than 16 chars just cut it
    if (_newLabel.size() > 16)
        _newLabel.truncate(16);

    objects[selectedItem]->setLabel(_newLabel);
}
