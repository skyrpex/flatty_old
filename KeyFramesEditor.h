#ifndef KEYFRAMESEDITOR_H
#define KEYFRAMESEDITOR_H

#include <QGraphicsView>
#include "KeyFrames.h"

class QGraphicsPixmapItem;

class KeyFramesEditor : public QGraphicsView
{
    Q_OBJECT
public:
    explicit KeyFramesEditor(QWidget *parent = 0);

    QSize sizeHint() const;

    void setData(KeyFrameMap *keyFrames, int frameCount);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QPointF keyFramePos(const QPoint &pos, bool bound = true) const;
    int frameAt(const QPoint &pos, bool bound = true) const;
    int frameAt(const QPointF &scenePos, bool bound = true) const;

    KeyFrameMap *m_keyFrames;
    int m_frameCount;
    QGraphicsPixmapItem *m_dragItem;
};

#endif // KEYFRAMESEDITOR_H
