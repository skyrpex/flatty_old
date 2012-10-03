#ifndef SKELETONMODEL_H
#define SKELETONMODEL_H

#include <QAbstractItemModel>

class Joint;
class Anim;

class JointModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Column
    {
        NameColumn,
        AnimColumn
    };
    enum Role
    {
        AnimRole = Qt::UserRole + 10
    };

    explicit JointModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Joint *rootJoint() const;
    QModelIndex indexOf(Joint *joint, int column) const;

public slots:
    void onAnimInserted(Anim *anim);
    void onAnimRemoved(Anim *anim);
    void onAnimChanged(Anim *anim);

private:
    friend class Joint;

    void emitDataChanged(Joint *joint, int column);

    void beginRemoveJoints(Joint *parent, int row, int count);
    void endRemoveJoints();
    void beginInsertJoints(Joint *parent, int row, int count);
    void endInsertJoints();

    Joint *m_root;
};

#endif // SKELETONMODEL_H
