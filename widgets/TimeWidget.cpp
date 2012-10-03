#include "TimeWidget.h"
#include "JointModel.h"
#include "AnimModel.h"
#include "Joint.h"
#include "JointDelegate.h"
#include "JointHeaderView.h"
#include <QTreeView>
#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>

TimeWidget::TimeWidget(JointModel *model, QWidget *parent) :
    QWidget(parent),
    m_model(model),
    m_delegate(new JointDelegate),
    m_header(new JointHeaderView),
    m_nameView(new QTreeView),
    m_animView(new QTreeView),
    m_currentAnim(0)
{
    m_nameView->setModel(m_model);
    m_nameView->setItemDelegate(m_delegate);
    m_nameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_nameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_animView->setModel(m_model);
    m_animView->setItemDelegate(m_delegate);
    m_animView->setHeader(m_header);
    m_animView->header()->setResizeMode(QHeaderView::ResizeToContents);
    m_animView->header()->setStretchLastSection(false);
    m_animView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_animView->setAutoScroll(false);
    m_animView->setMouseTracking(true);
    m_animView->hideColumn(0);

    connect(m_nameView, SIGNAL(expanded(QModelIndex)), m_animView, SLOT(expand(QModelIndex)));
    connect(m_animView, SIGNAL(expanded(QModelIndex)), m_nameView, SLOT(expand(QModelIndex)));
    connect(m_nameView, SIGNAL(collapsed(QModelIndex)), m_animView, SLOT(collapse(QModelIndex)));
    connect(m_animView, SIGNAL(collapsed(QModelIndex)), m_nameView, SLOT(collapse(QModelIndex)));
    connect(m_nameView->verticalScrollBar(), SIGNAL(valueChanged(int)), m_animView->verticalScrollBar(), SLOT(setValue(int)));
    connect(m_animView->verticalScrollBar(), SIGNAL(valueChanged(int)), m_nameView->verticalScrollBar(), SLOT(setValue(int)));

    connect(m_animView, SIGNAL(entered(QModelIndex)), SLOT(onEntered(QModelIndex)));
    connect(m_delegate, SIGNAL(currentFrameChanged(int)), m_header, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), m_delegate, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), m_animView->viewport(), SLOT(update()));

    connect(m_model, SIGNAL(columnsInserted(QModelIndex, int, int)), SLOT(onAnimsInserted()));

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(m_nameView);
    splitter->addWidget(m_animView);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
}

void TimeWidget::onCurrentAnimChanged(int current, int previous)
{
    current += JointModel::AnimColumn;
    previous += JointModel::AnimColumn;
    if(previous > 0) m_animView->hideColumn(previous);
    if(current > 0) m_animView->showColumn(current);
    m_currentAnim = current;
}

void TimeWidget::onEntered(const QModelIndex &index)
{
    if(m_openEditorIndex.isValid())
    {
        m_animView->closePersistentEditor(m_openEditorIndex);
        m_openEditorIndex = QModelIndex();
    }

    if(index.column() != JointModel::NameColumn)
    {
        m_animView->openPersistentEditor(index);
        m_openEditorIndex = index;
    }
}

void TimeWidget::onAnimsInserted()
{
    // Hide name column
    m_animView->hideColumn(0);

    // Hide anim columns
    for(int i = 0; i < m_model->animModel()->anims().count(); ++i)
    {
        m_nameView->hideColumn(i+JointModel::AnimColumn);
        m_animView->hideColumn(i+JointModel::AnimColumn);
    }

    // Restore the current anim
    if(m_currentAnim > 0)
        m_animView->showColumn(m_currentAnim);
}
