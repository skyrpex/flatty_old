#include "JointTreeView.h"
#include "JointModel.h"
#include "Joint.h"
#include "JointDelegate.h"
#include "JointHeaderView.h"

JointTreeView::JointTreeView(QWidget *parent) :
    QTreeView(parent),
    m_model(NULL),
    m_header(new JointHeaderView),
    m_delegate(new JointDelegate)
{
    setItemDelegate(m_delegate);
    setHeader(m_header);
    setAutoScroll(false);
    setMouseTracking(true);

    connect(this, SIGNAL(entered(QModelIndex)), SLOT(onEntered(QModelIndex)));
    connect(m_delegate, SIGNAL(currentFrameChanged(int)), m_header, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), m_delegate, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), SLOT(onCurrentFrameChanged()));
}

void JointTreeView::setModel(QAbstractItemModel *model)
{
    // Be sure that the models we receive are joint models
    m_model = qobject_cast<JointModel *>(model);
    Q_ASSERT(m_model || !model);
    QTreeView::setModel(model);

    // Hide all columns
    Joint *joint = m_model->rootJoint();
    for(int i = 0; i < joint->animMap().count(); ++i)
        hideColumn(JointModel::AnimColumn+i);
}

void JointTreeView::showAnimColumn(Anim *anim)
{
    if(!m_model) return;

    m_header->setCurrentFrame(0);

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

void JointTreeView::onCurrentFrameChanged()
{
    viewport()->update();
}

void JointTreeView::onEntered(const QModelIndex &index)
{
    if(m_openEditorIndex.isValid())
        {
            closePersistentEditor(m_openEditorIndex);
            m_openEditorIndex = QModelIndex();
        }

        if(index.column() != JointModel::NameColumn)
        {
            openPersistentEditor(index);
            m_openEditorIndex = index;
        }
}
