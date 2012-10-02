#include <QApplication>
#include <QTreeView>
#include <QSplitter>
#include "AnimModel.h"
#include "Anim.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnimModel *model = new AnimModel;

    QTreeView *v = new QTreeView;
    v->setModel(model);
    QSplitter s;
    s.addWidget(v);
    s.show();

    model->addAnim(new Anim("Biribit", 60, 30));
    model->addAnim(new Anim("Kaparaw", 50, 20));
    model->insertAnim(1, new Anim("Inasada", 40, 10));

    Anim *anim = new Anim("Ungosni", 30, 0);
    model->addAnim(anim);
//    delete anim;

    anim->setFrameCount(99);

    return a.exec();
}
