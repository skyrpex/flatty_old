#ifndef ANIM_H
#define ANIM_H

#include <QString>
#include <QMap>

class AnimModel;
class Transform;
class Anim;

typedef QMap<int, Transform*> KeyFrameMap;
typedef QMap<Anim *, KeyFrameMap*> AnimMap;

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

#endif // ANIM_H
