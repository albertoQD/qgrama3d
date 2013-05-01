#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMenu>
//#include "glwidget.h"
#include "qgrama3d.h"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();

public slots:
    void newGLWidget();
    bool saveAs();
    bool save(QString filename = "");
    void loadFile();
    void loadPredefinedObject();
    void load3DModel();
    void changeLinksVisibility();
    void changeLabelsVisibility();
    void changeBackgroundColor();
//    void changeLinksColor();
    void changeSelectionColor();
    void changeAxisColor();
    void changeLabelsColor();
    void showAbout();

protected:
    void createMenuBar();

private:
    QGrama3D * glWidget;
    QMenu * fileMenu;
    QMenu * graphMenu;
    QMenu * viewMenu;
    QMenu * optionsMenu;
    QMenu * helpMenu;
};

#endif // WINDOW_H
