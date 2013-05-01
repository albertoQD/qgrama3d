#include "window.h"
#include <QtGui>
#include <iostream>
#include <QDir>
#include "qgramadialogs.h"

using namespace std;

Window::Window()
{
    glWidget = new QGrama3D;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    setCentralWidget(glWidget);

    setWindowTitle("QGrama3D");
    createMenuBar();

    statusBar()->showMessage(tr("All done ..."));
//    glWidget->loadFromFile("/home/byteater/test.xml");
//    statusBar()->showMessage(tr("Automatically loaded") + glWidget->getFileLoaded());
}

bool Window::saveAs()
{

    QString filename = QFileDialog::getSaveFileName(
            this,
            tr("Save File"),
            QDir::toNativeSeparators(QDir::homePath()),
            tr("XML files (*.xml)") );

    if (filename.isEmpty())
        return false;

    if (filename.mid(filename.size()-4) != ".xml")
        filename += ".xml";

    return save( filename);
}

bool Window::save(QString filename)
{
    if (filename.isEmpty() && glWidget->getFileLoaded().isEmpty())
    {
        return saveAs();
    }

    if (glWidget->saveInFile(filename))
    {
        statusBar()->showMessage(tr("Graph saved into ") + glWidget->getFileLoaded());
        return true;
    }
    else
    {
        statusBar()->showMessage(tr("Graph could not be saved"));
        return false;
    }
}

void Window::newGLWidget()
{
    // ask to save first
    if (!glWidget->isEmpty())
    {
        if ( QMessageBox::question(
                    this,
                    tr("Save file"),
                    tr("Do you want to save the current Graph?"),
                    QMessageBox::Close | QMessageBox::Save,
                    QMessageBox::Save ) == QMessageBox::Save )
        {
            if (!save()) return;
        }
    }

    statusBar()->showMessage(tr("Starting from scratch ..."));
    glWidget = new QGrama3D;
    setCentralWidget(glWidget);
}

void Window::changeBackgroundColor()
{
    QColor _newColor = QColorDialog::getColor(QColor(255,0,0), this, tr("Select the new color for Background"));
    if (_newColor.isValid())
    {
        glWidget->setBackgroundColor(_newColor);
        statusBar()->showMessage(tr("Background color successfully changed"));
    }
}

void Window::changeSelectionColor()
{
    QColor _newColor = QColorDialog::getColor(QColor(255,0,0), this, tr("Select the new color for selection lines"));
    if (_newColor.isValid())
    {
        glWidget->setSelectionColor(_newColor);
        statusBar()->showMessage(tr("Selection lines color successfully changed"));
    }
}

void Window::changeAxisColor()
{
    QColor _newColor = QColorDialog::getColor(QColor(255,0,0), this, tr("Select the new color for axis lines"));
    if (_newColor.isValid())
    {
        glWidget->setAxisColor(_newColor);
        statusBar()->showMessage(tr("Axis lines color successfully changed"));
    }
}

void Window::changeLabelsColor()
{
    QColor _newColor = QColorDialog::getColor(QColor(255,0,0), this, tr("Select the new color for the labels"));
    if (_newColor.isValid())
    {
        glWidget->setLabelsColor(_newColor);
        statusBar()->showMessage(tr("Labels color successfully changed"));
    }
}

void Window::changeLinksVisibility()
{
    glWidget->changeLinksVisibility();
}

void Window::changeLabelsVisibility()
{
    glWidget->changeLabelsVisibility();
}

void Window::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Open QGrama3D File"),
            QDir::toNativeSeparators(QDir::homePath()),
            tr("XML files (*.xml)") );

    if (!filename.isEmpty())
    {
        newGLWidget();
        if(glWidget->loadFromFile(filename))
        {
            statusBar()->showMessage(tr("Graph loaded from ") + glWidget->getFileLoaded());
        }
        else
        {
            statusBar()->showMessage(tr("Graph could not be loaded"));
        }
    }
}

void Window::loadPredefinedObject()
{
    NewObjectDialog * newObject = new NewObjectDialog();
    newObject->setQGramaWidget(glWidget);
    newObject->show();
}

void Window::load3DModel()
{
    NewModelDialog * newModel = new NewModelDialog();
    newModel->setQGramaWidget(glWidget);
    newModel->show();
}

void Window::createMenuBar()
{
    // File Actions
    QAction * _newAction = new QAction(tr("&New Graph"), this);
    QAction * _loadAction = new QAction(tr("&Load Graph ..."), this);
    QAction * _saveAction = new QAction(tr("&Save Graph"), this);
    QAction * _saveAsAction = new QAction(tr("Save Graph &as ..."), this);
    QAction * _exitAction = new QAction(tr("&Exit"), this);
    // Graph Action
    QAction * _loadObjectAction = new QAction(tr("Load &Predefined object ..."), this);
    QAction * _loadModelAction = new QAction(tr("Load &Model from file ..."), this);
    // View Actions
    QAction * _viewLinksAction = new QAction(tr("&Links lines"), this);
    _viewLinksAction->setCheckable(true);
    _viewLinksAction->setChecked(true);
    QAction * _viewLabelsAction = new QAction(tr("La&bels"), this);
    _viewLabelsAction->setCheckable(true);
    _viewLabelsAction->setChecked(true);
    // Options Actions
//    QAction * _linkColorAction = new QAction(tr("Set &Link lines color ..."), this);
    QAction * _backgroundColorAction = new QAction(tr("Set &Background color ..."), this);
    QAction * _selectionColorAction = new QAction(tr("Set &selection color ..."), this);
    QAction * _axisColorAction = new QAction(tr("Set &axis color ..."), this);
    QAction * _labelColorAction = new QAction(tr("Set Lab&els color ..."), this);
    // Help Actions
    QAction * _aboutAction = new QAction(tr("&About ..."), this);

    // connect actions to slots
    connect(_viewLinksAction, SIGNAL(changed()), this, SLOT(changeLinksVisibility()));
    connect(_viewLabelsAction, SIGNAL(changed()), this, SLOT(changeLabelsVisibility()));

    connect(_newAction, SIGNAL(triggered()), this, SLOT(newGLWidget()));
    connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(_saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(_loadAction, SIGNAL(triggered()), this, SLOT(loadFile()));

    connect(_loadObjectAction, SIGNAL(triggered()), this, SLOT(loadPredefinedObject()));
    connect(_loadModelAction, SIGNAL(triggered()), this, SLOT(load3DModel()));

    connect(_backgroundColorAction, SIGNAL(triggered()), this, SLOT(changeBackgroundColor()));
//    connect(_linkColorAction, SIGNAL(triggered()), this, SLOT(changeLinksColor()));
    connect(_selectionColorAction, SIGNAL(triggered()), this, SLOT(changeSelectionColor()));
    connect(_axisColorAction, SIGNAL(triggered()), this, SLOT(changeAxisColor()));
    connect(_labelColorAction, SIGNAL(triggered()), this, SLOT(changeLabelsColor()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    // MENUS
    // File Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(_newAction);
    fileMenu->addAction(_loadAction);
    fileMenu->addAction(_saveAction);
    fileMenu->addAction(_saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(_exitAction);
    // Graph Menu
    graphMenu = menuBar()->addMenu(tr("&Graph"));
    graphMenu->addAction(_loadObjectAction);
    graphMenu->addAction(_loadModelAction);
    // View Menu
    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(_viewLabelsAction);
    viewMenu->addAction(_viewLinksAction);
    // Options Menu
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(_axisColorAction);
    optionsMenu->addAction(_selectionColorAction);
//    optionsMenu->addAction(_linkColorAction);
    optionsMenu->addAction(_labelColorAction);
    optionsMenu->addAction(_backgroundColorAction);
    // Help Menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(_aboutAction);
}

void Window::showAbout()
{
    QMessageBox::about( this,
                        "About QGrama3D",
                        QString("Created by:\nAlberto QUINTERO DELGADO\n<ajquinterod@gmail.com>"));
}
