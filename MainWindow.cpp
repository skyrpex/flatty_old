#include "MainWindow.h"
#include "JointModel.h"
#include "AnimModel.h"
#include "Anim.h"
#include "JointTreeView.h"
#include "AnimTreeView.h"
#include "widgets/TimeWidget.h"
#include "widgets/AnimWidget.h"
#include <QHBoxLayout>
#include <QSplitter>
#include <QScrollBar>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_model(new JointModel(this))
{
    AnimWidget *a = new AnimWidget(m_model->animModel(), this);
    TimeWidget *t = new TimeWidget(m_model, this);
//    connect(a, SIGNAL(currentAnimChanged(Anim*,Anim*)), t, SLOT(onCurrentAnimChanged(Anim*,Anim*)));
//    connect(a, SIGNAL(currentAnimChanged(Anim*,Anim*)), t, SLOT(onAnimSelected(Anim*)));
//    connect(a, SIGNAL(animSelected(Anim*)), t, SLOT(onAnimSelected(Anim*)));
    connect(a, SIGNAL(currentAnimChanged(int,int)), t, SLOT(onCurrentAnimChanged(int,int)));

    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(t);
    layout->addWidget(a);
    setCentralWidget(widget);

    QPushButton *b = new QPushButton;
    b->show();

    connect(b, SIGNAL(pressed()), SLOT(createAnim()));

//    m_model->animModel()->addAnim(new Anim("Idle", 20, 25));
//    m_model->animModel()->addAnim(new Anim("Run", 60, 25));

//    AnimTreeView *av = new AnimTreeView;
//    av->setModel(m_model->animModel());
//    av->show();

//    // Keyframe editor
//    JointTreeView *jv1 = new JointTreeView(this);
//    jv1->setModel(m_model);
//    jv1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    jv1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    JointTreeView *jv2 = new JointTreeView(this);
//    jv2->setModel(m_model);
//    jv2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    jv2->hideColumn(0);

//    connect(av, SIGNAL(currentAnimChanged(Anim*,Anim*)), jv2, SLOT(onCurrentAnimChanged(Anim*,Anim*)));
//    connect(jv1, SIGNAL(expanded(QModelIndex)), jv2, SLOT(expand(QModelIndex)));
//    connect(jv2, SIGNAL(expanded(QModelIndex)), jv1, SLOT(expand(QModelIndex)));
//    connect(jv1, SIGNAL(collapsed(QModelIndex)), jv2, SLOT(collapse(QModelIndex)));
//    connect(jv2, SIGNAL(collapsed(QModelIndex)), jv1, SLOT(collapse(QModelIndex)));
//    connect(jv1->verticalScrollBar(), SIGNAL(valueChanged(int)), jv2->verticalScrollBar(), SLOT(setValue(int)));
//    connect(jv2->verticalScrollBar(), SIGNAL(valueChanged(int)), jv1->verticalScrollBar(), SLOT(setValue(int)));


////    QWidget *widget = new QWidget(this);
////    QHBoxLayout *layout = new QHBoxLayout(widget);
//    QSplitter *splitter = new QSplitter;
////    layout->addWidget(splitter);
////    setCentralWidget(splitter);

//    splitter->addWidget(jv1);
//    splitter->addWidget(jv2);

    //    splitter->show();
}

void MainWindow::createAnim()
{
    static int i = 0;
    m_model->animModel()->addAnim(new Anim(QString::number(++i), i*5, i*12));
}
