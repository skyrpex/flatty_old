#include "KeyFrames.h"
#include "Transform.h"

KeyFrames::KeyFrames(QObject *parent) :
    QObject(parent)
{
    data.insert(0, new Transform);
}
