#-------------------------------------------------
#
# Project created by QtCreator 2020-03-12T15:59:25
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageLabelSpirit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        maininterface.cpp \
        widgets/menubutton.cpp \
        widgets/filebutton.cpp \
    common/commonutil.cpp \
    module/importdialog.cpp \
    module/exportdialog.cpp \
    common/fontawesomeicons.cpp \
    custom/annotationdelegate.cpp \
    module/settingdialog.cpp \
    splashwidget.cpp \
    widgets/markgraphicsview.cpp \
    custom/markgraphicspixmapitem.cpp \
    custom/markgraphicsscene.cpp \
    widgets/qtoast.cpp \
    module/reviewdialog.cpp \
    custom/filelistdelegate.cpp \
    module/exportmessagebox.cpp \
    common/exportworker.cpp \
    indexinterface.cpp \
    module/createprojectdialog.cpp \
    widgets/projectpreview.cpp \
    widgets/annotationcombobox.cpp \
    module/progresswidget.cpp \
    module/sizescalewidget.cpp

HEADERS += \
        maininterface.h \
        widgets/menubutton.h \
        widgets/filebutton.h \
     common/commonutil.h \
     module/importdialog.h \
    module/exportdialog.h \
    common/fontawesomeicons.h \
    custom/annotationdelegate.h \
    custom/meta.h \
    module/settingdialog.h \
    splashwidget.h \
    widgets/markgraphicsview.h \
    custom/markgraphicspixmapitem.h \
    custom/markgraphicsscene.h \
    widgets/qtoast.h \
    module/reviewdialog.h \
    custom/filelistdelegate.h \
    module/exportmessagebox.h \
    common/exportworker.h \
    indexinterface.h \
    module/createprojectdialog.h \
    widgets/projectpreview.h \
    widgets/annotationcombobox.h \
    module/progresswidget.h \
    module/sizescalewidget.h



FORMS += \
        maininterface.ui \
     module/importdialog.ui \
    module/exportdialog.ui \
    module/settingdialog.ui \
    splashwidget.ui \
    module/reviewdialog.ui \
    module/exportmessagebox.ui \
    indexinterface.ui \
    module/createprojectdialog.ui \
    widgets/projectpreview.ui \
    module/progresswidget.ui \
    module/sizescalewidget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
