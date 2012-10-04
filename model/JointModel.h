#ifndef SKELETONMODEL_H
#define SKELETONMODEL_H

#include <QAbstractItemModel>

class Joint;
class AnimModel;
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
    ~JointModel();

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
    AnimModel *animModel() const;

private slots:
    void onAnimsInserted(const QModelIndex &parent, int first, int last);
    void onAnimsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onAnimsChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    friend class Joint;

    void emitDataChanged(Joint *joint, int column);

    void beginRemoveJoints(Joint *parent, int row, int count);
    void endRemoveJoints();
    void beginInsertJoints(Joint *parent, int row, int count);
    void endInsertJoints();

    AnimModel *m_animModel;
    Joint *m_root;
};

#endif // SKELETONMODEL_H
