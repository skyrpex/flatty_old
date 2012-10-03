#ifndef JOINTTREEVIEW_H
#define JOINTTREEVIEW_H

#include <QTreeView>

class JointModel;
class Anim;

class JointTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit JointTreeView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);

signals:

public slots:
    void showAnimColumn(Anim *anim);
    void onCurrentAnimChanged(Anim *current, Anim *previous);

private slots:
    void onEntered(const QModelIndex &index);

private:
    JointModel *m_model;
    QModelIndex m_openEditorIndex;
};

#endif // JOINTTREEVIEW_H
