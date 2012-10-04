#ifndef ANIM_H
#define ANIM_H

#include <QString>
#include <QMap>
#include <QMetaType>

class AnimModel;
class Transform;
class Anim;
class KeyFrames;

typedef QMap<Anim *, KeyFrames*> AnimMap;

class Anim
{
public:
    Anim(const QString &name, int frameCount, int fps);
    ~Anim();

    QString name() const;
    void setName(const QString &name);

    int frameCount() const;
    void setFrameCount(int frameCount);

    int fps() const;
    void setFps(int fps);

private:
    friend class AnimModel;

    AnimModel *m_model;
    QString m_name;
    int m_frameCount;
    int m_fps;
};

Q_DECLARE_METATYPE(Anim*)

#endif // ANIM_H
