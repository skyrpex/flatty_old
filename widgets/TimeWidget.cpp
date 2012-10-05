#include "TimeWidget.h"
#include "model/JointModel.h"
#include "model/AnimModel.h"
#include "model/Joint.h"
#include "model/JointDelegate.h"
#include "model/JointHeaderView.h"
#include "model/JointProxyModel.h"
#include <QTreeView>
#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>

TimeWidget::TimeWidget(JointModel *model, QWidget *parent) :
    QWidget(parent),
    m_model(model),
    m_nameProxyModel(new JointProxyModel(m_model, this)),
    m_animProxyModel(new JointProxyModel(m_model, this)),
    m_delegate(new JointDelegate),
    m_header(new JointHeaderView),
    m_nameView(new QTreeView),
    m_animView(new QTreeView),
    m_currentAnim(0)
{
    m_nameView->setModel(m_nameProxyModel);
    m_nameView->setItemDelegate(m_delegate);
    m_nameView->setHeader(new JointHeaderView(this));
    m_nameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_nameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_nameProxyModel->showNames(true);

    m_animView->setModel(m_animProxyModel);
    m_animView->setItemDelegate(m_delegate);
    m_animView->setHeader(m_header);
    m_animView->header()->setResizeMode(QHeaderView::ResizeToContents);
    m_animView->header()->setStretchLastSection(false);
    m_animView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_animView->setAutoScroll(false);
    m_animView->setMouseTracking(true);
    m_animView->setItemsExpandable(false);
    m_animView->setRootIsDecorated(false);

    connect(m_nameView, SIGNAL(expanded(QModelIndex)), m_animView, SLOT(expand(QModelIndex)));
    connect(m_animView, SIGNAL(expanded(QModelIndex)), m_nameView, SLOT(expand(QModelIndex)));
    connect(m_nameView, SIGNAL(collapsed(QModelIndex)), m_animView, SLOT(collapse(QModelIndex)));
    connect(m_animView, SIGNAL(collapsed(QModelIndex)), m_nameView, SLOT(collapse(QModelIndex)));
    connect(m_nameView->verticalScrollBar(), SIGNAL(valueChanged(int)), m_animView->verticalScrollBar(), SLOT(setValue(int)));
    connect(m_animView->verticalScrollBar(), SIGNAL(valueChanged(int)), m_nameView->verticalScrollBar(), SLOT(setValue(int)));

    connect(m_animView, SIGNAL(entered(QModelIndex)), SLOT(openEditor(QModelIndex)));
    connect(m_delegate, SIGNAL(currentFrameChanged(int)), m_header, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), m_delegate, SLOT(setCurrentFrame(int)));
    connect(m_header, SIGNAL(currentFrameChanged(int)), m_animView->viewport(), SLOT(update()));

    connect(m_model->animModel(), SIGNAL(rowsInserted(QModelIndex, int, int)), SLOT(resetEditor()));
    connect(m_model->animModel(), SIGNAL(rowsRemoved(QModelIndex, int, int)), SLOT(resetEditor()));
    connect(m_model->animModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(resetEditor()));

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(m_nameView);
    splitter->addWidget(m_animView);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
}

void TimeWidget::onCurrentAnimChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    m_animProxyModel->showAnim(current.row());
}

void TimeWidget::openEditor(const QModelIndex &index)
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

void TimeWidget::resetEditor()
{
    openEditor(m_animView->currentIndex());
}
