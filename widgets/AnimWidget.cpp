#include "AnimWidget.h"
#include "AnimModel.h"
#include "Anim.h"
#include "dialogs/AnimDialog.h"
#include <QTreeView>
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>
#include <QModelIndex>
#include <QAction>
#include <QToolBar>

AnimWidget::AnimWidget(AnimModel *model, QWidget *parent) :
    QWidget(parent),
    m_model(model),
    m_view(new QTreeView(this))
{
    m_view->setModel(model);

    connect(m_view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), SLOT(onCurrentRowChanged(QModelIndex,QModelIndex)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    {
        QToolBar *t = new QToolBar(this);
        QAction *a = t->addAction("Hi", this, SLOT(createAnim()));
        a->setShortcut(QKeySequence("Ctrl+A"));
        layout->addWidget(t);
    }
    layout->addWidget(m_view);
}

void AnimWidget::createAnim()
{
    AnimDialog d(this);
    if(!d.exec()) return;

    m_model->addAnim(new Anim(d.name(), d.frameCount(), d.fps()));

    // Set the new anim as current index
    m_view->setCurrentIndex(m_model->index(m_model->anims().count()-1, 0, QModelIndex()));
}

void AnimWidget::onCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    emit currentAnimChanged(current.row(), previous.row());
}
