#include "JointTreeView.h"
#include "JointModel.h"
#include "Joint.h"

JointTreeView::JointTreeView(QWidget *parent) :
    QTreeView(parent)
{
}

void JointTreeView::setModel(QAbstractItemModel *model)
{
    m_model = qobject_cast<JointModel *>(model);
    Q_ASSERT(m_model || !model);
    QTreeView::setModel(model);
}

void JointTreeView::showAnimColumn(Anim *anim)
{
    if(!m_model)
        return;

    Joint *joint = m_model->rootJoint();
    for(int i = 0; i < joint->anims().count(); ++i)
        hideColumn(JointModel::AnimColumn+i);

    showColumn(JointModel::AnimColumn+joint->anims().keys().indexOf(anim));
}
