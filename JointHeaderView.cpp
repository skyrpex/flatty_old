#include "JointHeaderView.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QDateTime>
#include "JointModel.h"

//static const QBrush MARKER_BRUSH(QColor(250, 160, 170));
//static const QPen MARKER_PEN(QColor(200, 90, 90));
static const QBrush MarkerBrush(QColor(250, 150, 150));
static const QPen MarkerPen(QColor(250, 0, 0));

static const int FrameWidth = 8;
static const int FramesInARow = 5;

JointHeaderView::JointHeaderView(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent),
    m_currentFrame(0)
{
    // Make sure a scrollbar appears
    setResizeMode(ResizeToContents);
    setStretchLastSection(false);
}

int JointHeaderView::currentFrame() const
{
    return m_currentFrame;
}

void JointHeaderView::setCurrentFrame(int frame)
{
    if(m_currentFrame != frame)
    {
        m_currentFrame = frame;
        viewport()->update();
        emit currentFrameChanged(m_currentFrame);
    }
}

void JointHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if(!qobject_cast<JointModel *>(model()) || logicalIndex == JointModel::NameColumn)
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
        return;
    }


    // Draw background
    QStyleOptionHeader option;
    initStyleOption(&option);
    option.rect = rect;
    style()->drawControl(QStyle::CE_HeaderSection, &option, painter);


    // Draw grid
    painter->translate(rect.left(), 0);
    painter->setPen(QPen(Qt::lightGray));
    int frameCount = rect.width()/FrameWidth;
    QVector<QLineF> lines(frameCount+1);
    for(int i = 0; i <= frameCount; ++i)
    {
        int x = i*FrameWidth-1;
        lines[i] = QLineF(x, rect.height()-6, x, rect.height()-2);
    }
    painter->drawLines(lines);


    // Red square (time marker)
    painter->setBrush(MarkerBrush);
    painter->setPen(MarkerPen);
    painter->drawRect(QRect(m_currentFrame*FrameWidth, 0, FrameWidth, rect.height()-2));


    // Draw 1
    painter->setPen(QPen());
    QRect frameRect;
    frameRect.setWidth(FrameWidth*FramesInARow);
    frameRect.setHeight(rect.height());
    painter->drawText(frameRect, Qt::AlignVCenter, QString::number(1));
    for(int i = 5; i <= frameCount; i += 5)
    {
        frameRect.moveLeft(i*FrameWidth);
        painter->drawText(frameRect, Qt::AlignVCenter, QString::number(i));
    }

    painter->translate(-rect.left(), 0);
}

void JointHeaderView::mousePressEvent(QMouseEvent *e)
{
    QHeaderView::mousePressEvent(e);
    if(e->buttons() & Qt::LeftButton)
        updateCurrentFrame(e->pos());
}

void JointHeaderView::mouseMoveEvent(QMouseEvent *e)
{
    QHeaderView::mouseMoveEvent(e);
    if(e->buttons() & Qt::LeftButton)
        updateCurrentFrame(e->pos());
}

void JointHeaderView::updateCurrentFrame(const QPoint &pos)
{
    int logicalIndex = logicalIndexAt(pos);
    if(!qobject_cast<JointModel *>(model()) || logicalIndex == JointModel::NameColumn)
        return;

    int x = pos.x() + offset() - sectionPosition(logicalIndex);
    setCurrentFrame((0.5+x)/FrameWidth);
}
