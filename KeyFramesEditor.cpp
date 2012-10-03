#include "KeyFramesEditor.h"
#include "KeyFrames.h"
#include "KeyFrameItem.h"
#include "KeyFrameMime.h"
#include "Anim.h"
#include "Transform.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>
#include <cmath>

static const int FrameWidth = 8;
static const int FrameHeight = 20;

KeyFramesEditor::KeyFramesEditor(QWidget *parent) :
    QGraphicsView(new QGraphicsScene, parent),
    m_keyFrames(NULL),
    m_frameCount(0),
    m_dragItem(new QGraphicsPixmapItem)
{
    setDisabled(true);

    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QPixmap(":/images/background"));
    setFrameStyle(NoFrame);
    setAcceptDrops(true);

    setMinimumHeight(FrameHeight);
    setMaximumHeight(FrameHeight);

    m_dragItem->setPixmap(QPixmap(":/images/keyframe-drag"));
    m_dragItem->setZValue(1);
    m_dragItem->setVisible(false);
    scene()->addItem(m_dragItem);
}

QSize KeyFramesEditor::sizeHint() const
{
    if(m_keyFrames)
        return QSize(FrameWidth*m_frameCount, FrameHeight);

    return QGraphicsView::sizeHint();
}

void KeyFramesEditor::setData(KeyFrameMap *keyFrames, int frameCount)
{
    m_keyFrames = keyFrames;
    m_frameCount = frameCount;

    scene()->removeItem(m_dragItem);
    scene()->clear();
    scene()->addItem(m_dragItem);
    setEnabled(keyFrames);
    if(keyFrames)
    {
        setSceneRect(QRectF(QPointF(), QSizeF(frameCount*FrameWidth, FrameHeight)));
        foreach(int frame, keyFrames->keys())
            scene()->addItem(new KeyFrameItem(frame*FrameWidth));
    }
}

void KeyFramesEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    // Draw the background
    QGraphicsView::drawBackground(painter, rect);

    // Ofsetted frames are darkened
    painter->setCompositionMode(QPainter::CompositionMode_Multiply);
    int left = (m_keyFrames? m_frameCount : 0)*FrameWidth;
    QRectF r(QPointF(left, 0), QPointF(viewport()->width(), viewport()->height()));
    painter->fillRect(r.intersected(rect), palette().base().color().darker(120));

    // Gray out if disabled
    painter->setCompositionMode(QPainter::CompositionMode_Multiply);
    painter->fillRect(sceneRect().intersected(rect), palette().base());

    // Restore composition mode
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void KeyFramesEditor::contextMenuEvent(QContextMenuEvent *event)
{
    int frame = frameAt(event->pos(), false);
    bool frameInRange = frame >= 0 && frame < m_frameCount;
    bool hasKeyFrame = m_keyFrames->contains(frame);
    QMenu menu;

    QAction *createAction = menu.addAction(tr("Create keyframe"));
    createAction->setVisible(frameInRange && !hasKeyFrame);

    QAction *removeAction = menu.addAction(tr("Remove keyframe"));
    removeAction->setVisible(frameInRange && hasKeyFrame);
    removeAction->setDisabled(frame == 0);

    if(menu.isEmpty())
        return;

    QAction *action = menu.exec(event->globalPos());
    if(action == createAction)
    {
        scene()->addItem(new KeyFrameItem(frame*FrameWidth));
        m_keyFrames->insert(frame, new Transform);
    }
    else if(action == removeAction)
    {
        delete itemAt(event->pos());
        delete m_keyFrames->take(frame);
    }
}

void KeyFramesEditor::mousePressEvent(QMouseEvent *event)
{
    if(frameAt(event->pos()) > 0)
        QGraphicsView::mousePressEvent(event);
}

void KeyFramesEditor::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void KeyFramesEditor::dragEnterEvent(QDragEnterEvent *event)
{
    const KeyFrameMime *mime = qobject_cast<const KeyFrameMime *>(event->mimeData());

    m_dragItem->setPos(mapToScene(event->pos()));
    m_dragItem->setVisible(mime);
    event->setAccepted(mime);
}

void KeyFramesEditor::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    m_dragItem->setVisible(false);
}

void KeyFramesEditor::dragMoveEvent(QDragMoveEvent *event)
{
    const KeyFrameMime *mime = qobject_cast<const KeyFrameMime *>(event->mimeData());

    m_dragItem->setPos(keyFramePos(event->pos()));
    event->setAccepted(mime);
}

void KeyFramesEditor::dropEvent(QDropEvent *event)
{
    const KeyFrameMime *mime = qobject_cast<const KeyFrameMime *>(event->mimeData());

    m_dragItem->setVisible(false);
    event->setAccepted(mime);
    if(mime)
    {
        int frameFrom = frameAt(mime->keyFrameItem()->pos());
        int frameTo = frameAt(event->pos());

        if(frameFrom != frameTo)
        {
            // Remove previous keyframe
            if(m_keyFrames->value(frameTo))
            {
                delete m_keyFrames->take(frameTo);

                // Delete our item (it is important to hide the drag item before)
                delete itemAt(event->pos());
            }

            // Move keyframe
            Transform *transform = m_keyFrames->take(frameFrom);
            m_keyFrames->insert(frameTo, transform);

            mime->keyFrameItem()->setPos(keyFramePos(event->pos()));
        }
    }
}

QPointF KeyFramesEditor::keyFramePos(const QPoint &pos, bool bound) const
{
    qreal width = static_cast<qreal>(FrameWidth);
    return QPointF(frameAt(pos, bound)*width, sceneRect().top());
}

int KeyFramesEditor::frameAt(const QPoint &pos, bool bound) const
{
    return frameAt(mapToScene(pos), bound);
}

int KeyFramesEditor::frameAt(const QPointF &scenePos, bool bound) const
{
    qreal x = scenePos.x();
    qreal width = static_cast<qreal>(FrameWidth);
    if(bound)
        x = qBound(sceneRect().left(), x, sceneRect().right()-width);
    x -= std::fmod(x, width);
    return static_cast<int>(x/width);
}
