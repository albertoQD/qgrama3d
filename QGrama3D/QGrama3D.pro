QT += core gui opengl xml

LIBS += -lGLU -lglut

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGrama3D
TEMPLATE = app

SOURCES += \
    window.cpp \
    qgramadialogs.cpp \
    qgrama3d.cpp \
    object3d.cpp \
    model3d.cpp \
    main.cpp \
    cube.cpp

HEADERS  += \
    window.h \
    ui_newobject.h \
    ui_newmodel.h \
    qgramadialogs.h \
    qgrama3d.h \
    object3d.h \
    model3d.h \
    cube.h

FORMS += \
    newobject.ui \
    newmodel.ui
