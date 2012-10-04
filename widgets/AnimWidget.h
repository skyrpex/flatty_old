#ifndef ANIMWIDGET_H
#define ANIMWIDGET_H

#include <QWidget>

class QTreeView;
class QModelIndex;
class AnimModel;
class Anim;
class QItemSelection;

class AnimWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimWidget(AnimModel *model, QWidget *parent = 0);

public slots:
    void createAnim();
    void editAnim();
    void removeAnim();

signals:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);

private slots:
    void updateActions();

private:
    AnimModel *m_model;
    QTreeView *m_view;
    QAction *m_createAction;
    QAction *m_editAction;
    QAction *m_removeAction;
};

#endif // ANIMWIDGET_H
