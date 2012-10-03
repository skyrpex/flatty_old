#include "JointDelegate.h"
#include "Anim.h"
#include "JointModel.h"
#include "KeyFrames.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>

static const QSize MinimumSizeHint(0, 20);

JointDelegate::JointDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *JointDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if(index.data().canConvert<Anim *>())
//        return new AnimEditor(parent);

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void JointDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().canConvert<Anim *>())
    {
//        Anim *anim = index.data().value<Anim *>();
//        AnimEditor *AnimEditor = qobject_cast<AnimEditor *>(editor);
//        AnimEditor->setAnim(anim);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void JointDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<KeyFrames *>())
        paintAnim(painter, option, index.data(JointModel::AnimRole).value<Anim *>(), index.data().value<KeyFrames *>());
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize JointDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(8, 20) /*= AnimEditor::frameSize()*/;
    if(index.data().canConvert<KeyFrames *>())
    {
        Anim *anim = index.data(JointModel::AnimRole).value<Anim *>();
        if(anim)
            size.rwidth() *= anim->frameCount();
    }

    return QStyledItemDelegate::sizeHint(option, index).expandedTo(size);
}

void JointDelegate::paintAnim(QPainter *painter, const QStyleOptionViewItem &option, Anim *anim, KeyFrames *keyFrames) const
{
    // Draw the background
    painter->save();
    painter->translate(option.rect.topLeft());
    painter->fillRect(QRectF(QPointF(), option.rect.size()), QPixmap(":/images/background"));

    QPixmap pixmap(":/images/keyframe");

    // Draw the keyframes
    if(anim)
    {
        foreach(int frame, keyFrames->keyFrameMap.keys())
        {
            int x = frame*pixmap.size().width();
            QRectF rect(QPointF(x, 0), pixmap.size());
            painter->fillRect(rect, pixmap);
        }
    }
    painter->restore();

    // Disabled & offseted frames
    painter->save();
    painter->setCompositionMode(QPainter::CompositionMode_Multiply);

    // Ofsetted frames are darker
    QBrush brush(option.palette.base().color().darker(120));
    int xOffset = (anim? anim->frameCount() : 0)*pixmap.size().width();
    QRectF rect = option.rect.adjusted(xOffset, 0, 0, 0);
    painter->fillRect(rect, brush);

    // Gray out if disabled
    painter->fillRect(option.rect, option.palette.base());
    painter->restore();
}
