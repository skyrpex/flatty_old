#include "JointTreeView.h"
#include "JointModel.h"
#include "Joint.h"
#include "JointDelegate.h"
#include "JointHeaderView.h"

JointTreeView::JointTreeView(QWidget *parent) :
    QTreeView(parent),
    m_model(NULL)
{
    setItemDelegate(new JointDelegate);
    setHeader(new JointHeaderView);
    setAutoScroll(false);
}

void JointTreeView::setModel(QAbstractItemModel *model)
{
    // Be sure that the models we receive are joint models
    m_model = qobject_cast<JointModel *>(model);
    Q_ASSERT(m_model || !model);
    QTreeView::setModel(model);

    // Hide anim columns except for the first one
    Joint *joint = m_model->rootJoint();
    for(int i = 1; i < joint->animMap().count(); ++i)
        hideColumn(JointModel::AnimColumn+i);
}

void JointTreeView::showAnimColumn(Anim *anim)
{
    if(!m_model) return;

    Joint *joint = m_model->rootJoint();
    for(int i = 0; i < joint->animMap().count(); ++i)
        hideColumn(JointModel::AnimColumn+i);

    showColumn(JointModel::AnimColumn+joint->animMap().keys().indexOf(anim));
}

void JointTreeView::onCurrentAnimChanged(Anim *current, Anim *previous)
{
    if(!m_model) return;
    Joint *joint = m_model->rootJoint();
    QList<Anim *> anims = joint->animMap().keys();

    if(previous) hideColumn(JointModel::AnimColumn+anims.indexOf(previous));
    if(current) showColumn(JointModel::AnimColumn+anims.indexOf(current));
}
