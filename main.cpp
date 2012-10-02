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

    am->addAnim(new Anim("Biribit", 60, 30));
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


    return a.exec();
}
