#ifndef QGRAMADIALOGS_H
#define QGRAMADIALOGS_H

#include "ui_newobject.h"
#include "ui_newmodel.h"
#include "qgrama3d.h"

class NewObjectDialog : public QDialog
{
    Q_OBJECT

public:
    NewObjectDialog(QWidget * parent = 0);
    void setQGramaWidget(QGrama3D * _glWidget);

public slots:
    void showColorDialog();
    void addObject();

private:
    Ui::newObjectDialog ui;
    QGrama3D * glWidget;

};

class NewModelDialog : public QDialog
{
    Q_OBJECT

public:
    NewModelDialog(QWidget * parent = 0);
    void setQGramaWidget(QGrama3D * _glWidget);

public slots:
    void showColorDialog();
    void showOpenFileDialog();
    void addModel();

private:
    Ui::newModelDialog ui;
    QGrama3D * glWidget;

};

#endif // QGRAMADIALOGS_H
