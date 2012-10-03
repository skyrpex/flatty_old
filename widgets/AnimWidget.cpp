#include "AnimWidget.h"
#include "AnimModel.h"
#include <QTreeView>
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>
#include <QModelIndex>

AnimWidget::AnimWidget(AnimModel *model, QWidget *parent) :
    QWidget(parent),
    m_view(new QTreeView(this))
{
    m_view->setModel(model);

    connect(m_view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex,QModelIndex)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
}

void AnimWidget::onCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    emit currentAnimChanged(current.row(), previous.row());
}
