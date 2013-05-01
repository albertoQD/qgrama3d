#ifndef QGRAMA3D_H
#define QGRAMA3D_H

#include <QGLWidget>
#include "object3d.h"
#include "model3d.h"
#include <vector>
#include <set>
#include <map>

using namespace std;

class QGrama3D : public QGLWidget
{
    Q_OBJECT

public:
    QGrama3D(QWidget *parent = 0);
    ~QGrama3D();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    bool saveInFile(const QString & filename);
    bool loadFromFile(const QString & filename);
    QString getXML();
    QString getFileLoaded() const;
    void setFileLoaded(const QString & filename);
    bool isEmpty();
    void addNode(Object3D * obj);
    void setBackgroundColor(QColor _newColor);
//    void setLinksColor(QColor _newColor);
    void setSelectionColor(QColor _newColor);
    void setAxisColor(QColor _newColor);
    void setLabelsColor(QColor _newColor);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void xTranslated(int amount);
    void yTranslated(int amount);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setXTranslation(int amount);
    void setYTranslation(int amount);
    void showContextMenu(const QPoint &point);
    void setMoveMode();
    void setConnectMode();
    void setSelectMode();
    void setDisconnectMode();
    void deleteNode();
    void changeLinksVisibility();
    void changeLabelsVisibility();
    void showEditLabel();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *);
    int  selectObject(int x, int y);
    void drawLinks();
    void updateObjects();

private:
    int xRot;
    int yRot;
    int zRot;
    int mode;
    int selectedItem;
    int lastSelected;
    float xTrans;
    float yTrans;
    float scale;
    QPoint lastPos;
    QColor background;
//    QColor linksColor;
    QColor selectionColor;
    QColor labelsColor;
    QColor axisColor;
    vector<Object3D *> objects;
    vector<bool> deleted;
    map< pair<int, int>, QColor> links;
//    set< pair<pair<int, int>, QColor> > links;
    bool linksVisible;
    bool labelsVisible;
    QString fileLoaded;
};

#endif // QGRAMA3D_H
