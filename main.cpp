#include <QApplication>
#include <QTreeView>
#include <QSplitter>
#include "AnimModel.h"
#include "Anim.h"
#include "JointModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnimModel *am = new AnimModel;
    JointModel *jm = new JointModel;

    QObject::connect(am, SIGNAL(animInserted(Anim*)), jm, SLOT(addAnim(Anim*)));
    QObject::connect(am, SIGNAL(animRemoved(Anim*)), jm, SLOT(removeAnim(Anim*)));
    QObject::connect(am, SIGNAL(animChanged(Anim*)), jm, SLOT(onAnimChanged(Anim*)));

    Anim *anim = new Anim("Biribit", 60, 30);
    am->addAnim(anim);
    am->addAnim(new Anim("Kaparaw", 50, 20));
    am->insertAnim(1, new Anim("Inasada", 40, 10));
    am->insertAnim(0, new Anim("Ungosni", 30, 0));

    QTreeView *av = new QTreeView;
    av->setModel(am);
    QTreeView *jv = new QTreeView;
    jv->setModel(jm);
    QSplitter s;
    s.addWidget(av);
    s.addWidget(jv);
    s.show();

    delete anim;

    return a.exec();
}
