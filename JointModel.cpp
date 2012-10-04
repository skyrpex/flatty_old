#include "JointModel.h"
#include "Joint.h"
#include "Anim.h"
#include "AnimModel.h"
#include "Transform.h"
#include "KeyFrames.h"
#include <QSize>
#include <QVariant>
#include <QDebug>
#include <QStack>

static const char *RootText = "Root";
static const char *NameColumnText = "Name";
static const char *AnimColumnText = "Animation";

JointModel::JointModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_animModel(new AnimModel(this)),
    m_root(new Joint(tr(RootText)))
{
    m_root->m_model = this;
    connect(m_animModel, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(onAnimsInserted(QModelIndex,int,int)));
    connect(m_animModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)), SLOT(onAnimsAboutToBeRemoved(QModelIndex,int,int)));
    connect(m_animModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(onAnimsChanged(QModelIndex,QModelIndex)));
}

JointModel::~JointModel()
{
    beginRemoveRows(QModelIndex(), 0, 0);
    delete m_root;
    m_root = NULL;
    endRemoveRows();
}

bool inRange(int min, int val, int max)
{
    return ( min <= val && val <= max );
}

QVariant JointModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    Joint *joint = static_cast<Joint*>(index.internalPointer());
    switch(index.column())
    {
    case NameColumn:
        if(role == Qt::DisplayRole || role == Qt::EditRole)
            return joint->name();
        break;

    default:
    {
        int animID = index.column() - AnimColumn;
        Anim *anim = m_animModel->anims().at(animID);
        if(inRange(0, animID, joint->m_anims.count()))
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
                return QVariant::fromValue(joint->m_anims.value(anim));
            else if(role == AnimRole)
                return QVariant::fromValue(anim);
        }
    }
        break;
    }

    return QVariant();
}

Qt::ItemFlags JointModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    if(index.column() == NameColumn && static_cast<Joint*>(index.internalPointer()) == m_root)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant JointModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    if(section == NameColumn)
        return tr(NameColumnText);
    else
    {
        int animID = section - AnimColumn;
        if(inRange(0, animID, m_animModel->anims().count()))
        {
            return QString("%1 %2").arg(m_animModel->anims().at(animID)->name()).arg(animID);
        }
    }
    return QVariant();
}

QModelIndex JointModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column, m_root);

    Joint *parentJoint = static_cast<Joint*>(parent.internalPointer());
    Joint *childJoint = parentJoint->children().value(row, NULL);

    if(childJoint)
        return createIndex(row, column, childJoint);

     return QModelIndex();
}

QModelIndex JointModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Joint *childJoint = static_cast<Joint*>(index.internalPointer());
    Joint *parentJoint = childJoint->parent();

    if (!parentJoint)
        return QModelIndex();

    return createIndex(parentJoint->children().indexOf(childJoint), 0, parentJoint);
}

int JointModel::rowCount(const QModelIndex &parent) const
{
//    if(parent.column() > 0)
//        return 0;

    if(!parent.isValid())
        return 1;

    Joint *parentJoint = static_cast<Joint*>(parent.internalPointer());
    return parentJoint->children().count();
}

int JointModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1+m_root->m_anims.count();
}

bool JointModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != Qt::EditRole) return false;

    Joint *joint = static_cast<Joint*>(index.internalPointer());
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == NameColumn)
        {
            joint->setName(value.toString());
            return true;
        }
    }
    return false;
}

Joint *JointModel::rootJoint() const
{
    return m_root;
}

QModelIndex JointModel::indexOf(Joint *joint, int column) const
{
    // Invalid model or joint
    if(!joint)
        return QModelIndex();

    // Root joint
    if(joint == m_root)
        return index(0, column);

    // Get the child indexes
    QList<int> childIndexes;
    Joint *currentJoint = joint;
    while(currentJoint)
    {
        if(currentJoint->parent())
        {
            int row = currentJoint->parent()->children().indexOf(currentJoint);
            if(row < 0)
                return QModelIndex();

            childIndexes << row;
        }
        else
            childIndexes << 0;

        currentJoint = currentJoint->parent();
    }

    // Build the index
    QModelIndex index;
    for(int i = childIndexes.count() - 1; i >= 0 ; --i)
        index = this->index(childIndexes.at(i), column, index);
    return index;
}

AnimModel *JointModel::animModel() const
{
    return m_animModel;
}

void JointModel::onAnimsInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    beginInsertColumns(QModelIndex(), JointModel::AnimColumn+first, JointModel::AnimColumn+last);
    QStack<Joint *> stack;
    stack.push(m_root);
    while(!stack.isEmpty())
    {
        Joint *joint = stack.pop();
        for(int i = first; i <= last; ++i)
        {
            Anim *anim = m_animModel->anims().at(i);
            joint->m_anims.insert(anim, new KeyFrames);
        }

        foreach(Joint *child, joint->children())
            stack.push(child);
    }
    endInsertColumns();
}

void JointModel::onAnimsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    beginRemoveColumns(QModelIndex(), JointModel::AnimColumn+first, JointModel::AnimColumn+last);
    QStack<Joint *> stack;
    stack.push(m_root);
    while(!stack.isEmpty())
    {
        Joint *joint = stack.pop();
        for(int i = first; i <= last; ++i)
            delete joint->m_anims.take(m_animModel->anims().at(i));

        foreach(Joint *child, joint->children())
            stack.push(child);
    }
    endRemoveColumns();
}

void JointModel::onAnimsChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    emit dataChanged(index(0, AnimColumn+topLeft.row()),
                     index(0, AnimColumn+bottomRight.row()));
}

void JointModel::emitDataChanged(Joint *joint, int column)
{
    QModelIndex index = indexOf(joint, column);
    emit dataChanged(index, index);
}

void JointModel::beginRemoveJoints(Joint *parent, int row, int count)
{
    Q_ASSERT(row >= 0);
    Q_ASSERT(count > 0);

    beginRemoveRows(indexOf(parent, 0), row, row + count - 1);
}

void JointModel::endRemoveJoints()
{
    endRemoveRows();
}

void JointModel::beginInsertJoints(Joint *parent, int row, int count)
{
    beginInsertRows(indexOf(parent, 0), row, row + count - 1);
}

void JointModel::endInsertJoints()
{
    endInsertRows();
}
