#ifndef JOINT_H
#define JOINT_H

#include <QList>
#include <QMap>
#include <QString>
#include <QTreeWidgetItem>
#include "Anim.h"

class JointModel;
class Anim;

class Joint
{
public:
    explicit Joint(Joint *parent = 0);
    explicit Joint(const QString &name, Joint *parent = 0);
    ~Joint();

    Joint *clone() const;

    Joint *parent() const;
    Joint *child(int i) const;
    QList<Joint *> children() const;

    void addChild(Joint *child);
    void insertChild(int index, Joint *child);
    void removeChild(Joint *child);
    Joint *takeChild(int i);

    void addChildren(const QList<Joint*> &children);
    void insertChildren(int index, const QList<Joint*> &children);
    QList<Joint*> takeChildren();

    QString name() const;
    void setName(const QString &name);

    AnimMap animMap() const;

private:
    friend class JointModel;
    void syncAnims(Joint *joint);

    JointModel *m_model;

    Joint *m_parent;
    QList<Joint*> m_children;

    QString m_name;
    AnimMap m_anims;
};

#endif // JOINT_H
