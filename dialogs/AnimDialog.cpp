#include "AnimDialog.h"
#include "ui_AnimDialog.h"

AnimDialog::AnimDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Create Animation"));
}

AnimDialog::AnimDialog(const QString &name, int frameCount, int fps, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimDialog)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->frameCount->setValue(frameCount);
    ui->fps->setValue(fps);

    setWindowTitle(tr("Edit Animation"));
}

AnimDialog::~AnimDialog()
{
    delete ui;
}

QString AnimDialog::name() const
{
    return ui->name->text();
}

int AnimDialog::frameCount() const
{
    return ui->frameCount->value();
}

int AnimDialog::fps() const
{
    return ui->fps->value();
}
