#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QtGlobal>

class Transform
{
public:
    Transform();
    Transform(qreal rotation, qreal length);
    Transform(const Transform &other);

    void operator =(const Transform &b);

    qreal rotation;
    qreal length;
};

inline Transform operator+(const Transform &a, const Transform &b)
{
    return Transform(a.rotation+b.rotation, a.length);
}

#endif // TRANSFORM_H
