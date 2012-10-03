#ifndef ANIMWIDGET_H
#define ANIMWIDGET_H

#include <QWidget>

class QTreeView;
class QModelIndex;
class AnimModel;
class Anim;

class AnimWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimWidget(AnimModel *model, QWidget *parent = 0);

signals:
    void currentAnimChanged(int currentRow, int previousRow);

private slots:
    void onCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    QTreeView *m_view;
};

#endif // ANIMWIDGET_H
