#ifndef JOINTPROXYMODEL_H
#define JOINTPROXYMODEL_H

#include <QSortFilterProxyModel>

class JointModel;

class JointProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit JointProxyModel(JointModel *model, QObject *parent = 0);
    
    void showNames(bool show);
    void showAnim(int id);

protected:
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;

private:
    bool m_showNames;
    int m_anim;
};

#endif // JOINTPROXYMODEL_H
