#ifndef JOINTTREEVIEW_H
#define JOINTTREEVIEW_H

#include <QTreeView>

class JointModel;
class Anim;
class JointHeaderView;
class JointDelegate;

class JointTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit JointTreeView(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);

public slots:
    void showAnimColumn(Anim *anim);
    void onCurrentAnimChanged(Anim *current, Anim *previous);

private slots:
    void onEntered(const QModelIndex &index);
    void onCurrentFrameChanged();

private:
    JointModel *m_model;
    JointHeaderView *m_header;
    JointDelegate *m_delegate;
    QModelIndex m_openEditorIndex;
};

#endif // JOINTTREEVIEW_H
