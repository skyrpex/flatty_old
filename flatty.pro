QT       += core gui

TARGET = flatty
TEMPLATE = app


SOURCES += main.cpp \
    model/AnimModel.cpp \
    model/Anim.cpp \
    model/Joint.cpp \
    model/JointModel.cpp \
    model/Transform.cpp \
    model/JointDelegate.cpp \
    model/KeyFrames.cpp \
    model/JointHeaderView.cpp \
    model/KeyFramesEditor.cpp \
    model/KeyFrameMime.cpp \
    model/KeyFrameItem.cpp \
    MainWindow.cpp \
    widgets/TimeWidget.cpp \
    widgets/AnimWidget.cpp \
    dialogs/AnimDialog.cpp \
    Application.cpp

HEADERS  += \
    model/AnimModel.h \
    model/Anim.h \
    model/Joint.h \
    model/JointModel.h \
    model/Transform.h \
    model/JointDelegate.h \
    model/KeyFrames.h \
    model/JointHeaderView.h \
    model/KeyFramesEditor.h \
    model/KeyFrameMime.h \
    model/KeyFrameItem.h \
    MainWindow.h \
    widgets/TimeWidget.h \
    widgets/AnimWidget.h \
    dialogs/AnimDialog.h \
    Application.h \
    Constants.h

FORMS    += \
    dialogs/AnimDialog.ui

RESOURCES += \
    model/images/images.qrc
