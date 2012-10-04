QT       += core gui

TARGET = flatty
TEMPLATE = app


SOURCES += main.cpp \
    AnimModel.cpp \
    Anim.cpp \
    Joint.cpp \
    JointModel.cpp \
    Transform.cpp \
    JointDelegate.cpp \
    KeyFrames.cpp \
    JointHeaderView.cpp \
    KeyFramesEditor.cpp \
    KeyFrameMime.cpp \
    KeyFrameItem.cpp \
    MainWindow.cpp \
    widgets/TimeWidget.cpp \
    widgets/AnimWidget.cpp \
    dialogs/AnimDialog.cpp

HEADERS  += \
    AnimModel.h \
    Anim.h \
    Joint.h \
    JointModel.h \
    Transform.h \
    JointDelegate.h \
    KeyFrames.h \
    JointHeaderView.h \
    KeyFramesEditor.h \
    KeyFrameMime.h \
    KeyFrameItem.h \
    MainWindow.h \
    widgets/TimeWidget.h \
    widgets/AnimWidget.h \
    dialogs/AnimDialog.h

FORMS    += \
    dialogs/AnimDialog.ui

RESOURCES += \
    images.qrc
