#include "MainWindow.h"
#include "JointModel.h"
#include "AnimModel.h"
#include "Anim.h"
#include "JointTreeView.h"
#include "AnimTreeView.h"
#include "widgets/TimeWidget.h"
#include "widgets/AnimWidget.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_model(new JointModel(this))
{
    AnimWidget *a = new AnimWidget(m_model->animModel(), this);
    TimeWidget *t = new TimeWidget(m_model, this);
    connect(a, SIGNAL(currentChanged(QModelIndex,QModelIndex)), t, SLOT(onCurrentAnimChanged(QModelIndex,QModelIndex)));

    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(t);
    layout->addWidget(a);
    setCentralWidget(widget);
}
