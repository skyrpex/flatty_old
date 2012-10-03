QT       += core gui

TARGET = flatty
TEMPLATE = app


SOURCES += main.cpp \
    AnimModel.cpp \
    Anim.cpp \
    Joint.cpp \
    JointModel.cpp \
    JointTreeView.cpp \
    AnimTreeView.cpp \
    Transform.cpp \
    JointDelegate.cpp \
    KeyFrames.cpp \
    JointHeaderView.cpp \
    KeyFramesEditor.cpp \
    KeyFrameMime.cpp \
    KeyFrameItem.cpp

HEADERS  += \
    AnimModel.h \
    Anim.h \
    Joint.h \
    JointModel.h \
    JointTreeView.h \
    AnimTreeView.h \
    Transform.h \
    JointDelegate.h \
    KeyFrames.h \
    JointHeaderView.h \
    KeyFramesEditor.h \
    KeyFrameMime.h \
    KeyFrameItem.h

FORMS    +=

RESOURCES += \
    images.qrc