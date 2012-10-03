#include <QApplication>
#include <QTreeView>
#include <QSplitter>
#include "AnimModel.h"
#include "Anim.h"
#include "AnimTreeView.h"
#include "JointModel.h"
#include "Joint.h"
#include "JointTreeView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnimModel *am = new AnimModel;
    JointModel *jm = new JointModel;

    QObject::connect(am, SIGNAL(animInserted(Anim*)), jm, SLOT(onAnimInserted(Anim*)));
    QObject::connect(am, SIGNAL(animRemoved(Anim*)), jm, SLOT(onAnimRemoved(Anim*)));
    QObject::connect(am, SIGNAL(animChanged(Anim*)), jm, SLOT(onAnimChanged(Anim*)));

    Anim *anim = new Anim("Biribit", 60, 30);
    am->addAnim(anim);
    am->addAnim(new Anim("Kaparaw", 50, 20));
    am->insertAnim(1, new Anim("Inasada", 40, 10));
    am->insertAnim(0, new Anim("Ungosni", 30, 0));

    AnimTreeView *av = new AnimTreeView;
    av->setModel(am);
    JointTreeView *jv = new JointTreeView;
    jv->setModel(jm);
//    jv->showAnimColumn(anim);

    jv->connect(av, SIGNAL(currentAnimChanged(Anim*,Anim*)), jv, SLOT(onCurrentAnimChanged(Anim*,Anim*)));

    QSplitter s;
    s.addWidget(av);
    s.addWidget(jv);
    s.show();

    Joint *j = new Joint("Savarage", jm->rootJoint());

//    delete anim;

    return a.exec();
}
