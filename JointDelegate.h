#ifndef JOINTDELEGATE_H
#define JOINTDELEGATE_H

#include <QStyledItemDelegate>

class AnimData;
class Anim;
class KeyFrames;

class JointDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit JointDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void paintAnim(QPainter *painter, const QStyleOptionViewItem &option, Anim *anim, KeyFrames *keyFrames) const;
};

#endif // JOINTDELEGATE_H
