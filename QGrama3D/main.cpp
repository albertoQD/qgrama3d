#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "window.h"
#include <GL/glut.h>

using namespace std;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);
    Window window;
    window.resize(window.sizeHint());

    // for centering the window in the desktop
    window.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            window.size(),
            QApplication::desktop()->availableGeometry()
    ));

    window.show();

    return app.exec();
}
