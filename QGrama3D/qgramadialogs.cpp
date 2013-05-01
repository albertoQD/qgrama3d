#include <QColorDialog>
#include <QFileDialog>
#include <QDir>
#include "model3d.h"
#include "cube.h"
#include "object3d.h"
#include "qgramadialogs.h"


NewObjectDialog::NewObjectDialog(QWidget *parent)
    : QDialog(parent)
    , glWidget(NULL)
{
    ui.setupUi(this);

    // connect signals
    connect(ui.pickColorBtn, SIGNAL(clicked()), this, SLOT(showColorDialog()));
    connect(ui.buttonBox->button(ui.buttonBox->Ok), SIGNAL(clicked()), this, SLOT(addObject()));
    connect(ui.buttonBox->button(ui.buttonBox->Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

void NewObjectDialog::showColorDialog()
{
    QColor _selectedColor = QColorDialog::getColor(QColor(255,0,0), this);
    ui.spinBoxRed->setValue(_selectedColor.red());
    ui.spinBoxGreen->setValue(_selectedColor.green());
    ui.spinBoxBlue->setValue(_selectedColor.blue());
}

void NewObjectDialog::setQGramaWidget(QGrama3D * _glWidget)
{
    glWidget = _glWidget;
}

void NewObjectDialog::addObject()
{
    if (!glWidget) return;

    Object3D * obj = new Cube();
    obj->setCenter(QVector3D(
                       ui.spinBoxX->value(),
                       ui.spinBoxY->value(),
                       ui.spinBoxZ->value()));

    obj->setColor(QColor(
                      ui.spinBoxRed->value(),
                      ui.spinBoxGreen->value(),
                      ui.spinBoxBlue->value()));

    obj->setLength(QVector3D(ui.lengthXSB->value(), ui.lengthYSB->value(), ui.lengthZSB->value()));
    obj->setLabel(ui.objectLabelEL->text());
    glWidget->addNode(obj);
}

NewModelDialog::NewModelDialog(QWidget *parent)
    : QDialog(parent)
    , glWidget(NULL)
{
    ui.setupUi(this);

    // connect signals
    connect(ui.pickColorBtn, SIGNAL(clicked()), this, SLOT(showColorDialog()));
    connect(ui.openFileBtn, SIGNAL(clicked()), this, SLOT(showOpenFileDialog()));
    connect(ui.buttonBox->button(ui.buttonBox->Ok), SIGNAL(clicked()), this, SLOT(addModel()));
    connect(ui.buttonBox->button(ui.buttonBox->Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

void NewModelDialog::showColorDialog()
{
    QColor _selectedColor = QColorDialog::getColor(QColor(255,0,0), this);
    ui.spinBoxRed->setValue(_selectedColor.red());
    ui.spinBoxGreen->setValue(_selectedColor.green());
    ui.spinBoxBlue->setValue(_selectedColor.blue());
}

void NewModelDialog::showOpenFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open 3D Model File"),
            QDir::toNativeSeparators(QDir::homePath()),
            tr("OBJ Files (*.obj);;OFF Files (*.off)") );

    if (!filename.isEmpty())
    {
        ui.filenameLE->setText(filename);
    }
}

void NewModelDialog::setQGramaWidget(QGrama3D * _glWidget)
{
    glWidget = _glWidget;
}

void NewModelDialog::addModel()
{
    if (ui.filenameLE->text().isEmpty())
    { // show error dialog

    }
    else
    { // create new model and add it
        if (!glWidget) return;

        Model3D * _model = new Model3D(ui.filenameLE->text());
        _model->setCenter(QVector3D( ui.spinBoxX->value(), ui.spinBoxY->value(), ui.spinBoxZ->value() ));
        _model->loadModel();
        _model->setColor(QColor(
                          ui.spinBoxRed->value(),
                          ui.spinBoxGreen->value(),
                          ui.spinBoxBlue->value()));
        _model->setLabel(ui.objectLabelEL->text());
        glWidget->addNode(_model);
    }
}
