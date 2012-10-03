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

    JointModel *jm = new JointModel;
    AnimModel *am = jm->animModel();

    Anim *anim = new Anim("Biribit", 1, 30);
    am->addAnim(anim);
    am->addAnim(new Anim("Kaparaw", 2, 20));
    am->insertAnim(1, new Anim("Inasada", 3, 10));
    am->insertAnim(0, new Anim("Ungosni", 40, 0));

    AnimTreeView *av = new AnimTreeView;
    av->setModel(am);
    JointTreeView *jv = new JointTreeView;
    jv->setModel(jm);
//    jv->showAnimColumn(anim);

//    jv->connect(av, SIGNAL(currentAnimChanged(Anim*,Anim*)), jv, SLOT(onCurrentAnimChanged(Anim*,Anim*)));
    jv->connect(av, SIGNAL(currentAnimChanged(Anim*,Anim*)), jv, SLOT(showAnimColumn(Anim*)));

    QSplitter s;
    s.addWidget(av);
    s.addWidget(jv);
    s.show();

    Joint *j = new Joint("Savarage", jm->rootJoint());

//    delete anim;

    return a.exec();
}
