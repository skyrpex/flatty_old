#include "AnimTreeView.h"
#include "AnimModel.h"
#include <QDebug>

AnimTreeView::AnimTreeView(QWidget *parent) :
    QTreeView(parent)
{
}

void AnimTreeView::setModel(QAbstractItemModel *model)
{
    if(m_model)
        m_model->disconnect(this);

    m_model = qobject_cast<AnimModel *>(model);
    Q_ASSERT(m_model || !model);
    QTreeView::setModel(model);

    if(selectionModel())
        connect(selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(onCurrentChanged(QModelIndex,QModelIndex)));
}

void AnimTreeView::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    emit currentAnimChanged(static_cast<Anim *>(current.internalPointer()),
                            static_cast<Anim *>(previous.internalPointer()));
}
