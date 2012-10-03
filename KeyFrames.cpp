#include "KeyFrames.h"
#include "Transform.h"

KeyFrames::KeyFrames(QObject *parent) :
    QObject(parent)
{
    keyFrameMap.insert(0, new Transform);
}
