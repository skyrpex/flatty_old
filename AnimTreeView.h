#ifndef ANIMTREEVIEW_H
#define ANIMTREEVIEW_H

#include <QTreeView>

class AnimModel;
class Anim;

class AnimTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit AnimTreeView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);

signals:
    void currentAnimChanged(Anim *current, Anim *previous);

private slots:
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    AnimModel *m_model;
};

#endif // ANIMTREEVIEW_H
