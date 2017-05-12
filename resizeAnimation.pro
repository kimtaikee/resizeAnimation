TEMPLATE = app
TARGET = resizeAnimation
INCLUDEPATH += .

QT += widgets core gui

# Input
HEADERS += widget.h \
    scrollanimationwindow.h \
    changeshapecanvas.h \
    graphicspathobject.h \
    slidetextanimation.h \
    graphicslineobject.h \
    graphicsellipseobject.h \
    layoutwindowsanimation.h \
    colorball.h \
    tagwidget.h \
    flowlayout.h \
    tsttagwidget.h \
    imagecarousel.h \
    bounceindicator.h \
    slidewidgetcontainer.h \
    fadingtoolbutton.h \
    tstflowlayout.h \
    explodeanimation.h \
    tableselectionanimation.h \
    frame.h \
    ledunit.h \
    lednumber.h \
    lednumberanimation.h \
    slidemenuanimation.h \
    shadowwindow.h \
    inputdialog.h \
    eventfilter.h \
    circle.h \
    flyawayanimation.h \
    highlighwindow.h

FORMS += widget.ui \
    scrollanimationwindow.ui \
    changeshapecanvas.ui \
    slidetextanimation.ui \
    layoutwindowsanimation.ui \
    tsttagwidget.ui \
    tstflowlayout.ui \
    explodeanimation.ui \
    tableselectionanimation.ui \
    lednumberanimation.ui \
    inputdialog.ui \
    flyawayanimation.ui

SOURCES += main.cpp widget.cpp \
    scrollanimationwindow.cpp \
    changeshapecanvas.cpp \
    graphicspathobject.cpp \
    slidetextanimation.cpp \
    graphicslineobject.cpp \
    graphicsellipseobject.cpp \
    layoutwindowsanimation.cpp \
    colorball.cpp \
    tagwidget.cpp \
    flowlayout.cpp \
    tsttagwidget.cpp \
    imagecarousel.cpp \
    bounceindicator.cpp \
    slidewidgetcontainer.cpp \
    fadingtoolbutton.cpp \
    tstflowlayout.cpp \
    explodeanimation.cpp \
    tableselectionanimation.cpp \
    frame.cpp \
    ledunit.cpp \
    lednumber.cpp \
    lednumberanimation.cpp \
    slidemenuanimation.cpp \
    shadowwindow.cpp \
    inputdialog.cpp \
    eventfilter.cpp \
    circle.cpp \
    flyawayanimation.cpp \
    highlighwindow.cpp

LIBS += user32.lib gdi32.lib

RESOURCES += \
    images.qrc
