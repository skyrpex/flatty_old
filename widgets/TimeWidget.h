#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QWidget>
#include <QModelIndex>

class QTreeView;
class JointModel;
class Anim;
class JointDelegate;
class JointHeaderView;

class TimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeWidget(JointModel *model, QWidget *parent = 0);

public slots:
    void onCurrentAnimChanged(const QModelIndex &current, const QModelIndex &previous);

private slots:
    void openEditor(const QModelIndex &index);
    void resetEditor();
    void updateColumnVisibility();

private:
    JointModel *m_model;
    JointDelegate *m_delegate;
    JointHeaderView *m_header;
    QTreeView *m_nameView;
    QTreeView *m_animView;
    QModelIndex m_openEditorIndex;
    int m_currentAnim;
    Anim *m_anim;
};

#endif // TIMEWIDGET_H
