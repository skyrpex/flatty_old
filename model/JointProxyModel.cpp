#include "JointProxyModel.h"
#include "JointModel.h"

JointProxyModel::JointProxyModel(JointModel *model, QObject *parent) :
    QSortFilterProxyModel(parent),
    m_showNames(false),
    m_anim(-1)
{
    setSourceModel(model);
}

void JointProxyModel::showNames(bool show)
{
    m_showNames = show;
    invalidateFilter();
}

void JointProxyModel::showAnim(int id)
{
    m_anim = id;
    invalidateFilter();
}

bool JointProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    if(source_column == JointModel::NameColumn) return m_showNames;

    return (m_anim != -1 && source_column == JointModel::AnimColumn+m_anim);
}
