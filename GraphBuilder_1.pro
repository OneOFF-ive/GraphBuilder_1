QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adjMatrix/adjmatrix.cpp \
    adjTable/adjtable.cpp \
    lineDetail/linedetail.cpp \
    lineItem/lineitem.cpp \
    mainWindow/mainwindow.cpp \
    myGraphicsView/mygraphicsview.cpp \
    main.cpp \
    selectEnd/selectend.cpp \
    vexDrtail/vexdetail.cpp \
    vexItem/vexitem.cpp

HEADERS += \
    adjMatrix/adjmatrix.h \
    adjTable/adjtable.h \
    lineDetail/linedetail.h \
    lineItem/lineitem.h \
    mainWindow/mainwindow.h \
    myGraphicsView/mygraphicsview.h \
    selectEnd/selectend.h \
    vexDrtail/vexdetail.h \
    vexItem/vexitem.h

FORMS += \
    lineDetail/linedetail.ui \
    mainWindow/mainwindow.ui \
    selectEnd/selectend.ui \
    vexDrtail/vexdetail.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
