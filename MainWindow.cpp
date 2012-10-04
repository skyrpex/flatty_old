#include "MainWindow.h"
#include "model/JointModel.h"
#include "model/Joint.h"
#include "model/AnimModel.h"
#include "model/Anim.h"
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

    new Joint("Caca", m_model->rootJoint());
}
