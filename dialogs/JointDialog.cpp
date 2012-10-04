#include "JointDialog.h"
#include "ui_JointDialog.h"
#include <style/qtcolorbutton.h>
#include <Application.h>

JointDialog::JointDialog(const QString &parentName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JointDialog)
{
    ui->setupUi(this);
    ui->name->setText(tr("Child of %1").arg(parentName));
    ui->name->selectAll();
    ui->color->setColor(qApp->color(Application::JointColor));

    setWindowTitle(tr("Create Joint"));
}

JointDialog::JointDialog(const QString &name, const QColor &color, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JointDialog)
{
    ui->setupUi(this);
    ui->name->setText(name);
    ui->name->selectAll();
    ui->color->setColor(color);


    setWindowTitle(tr("Edit Joint"));
}

JointDialog::~JointDialog()
{
    delete ui;
}

QString JointDialog::name() const
{
    return ui->name->text();
}

QColor JointDialog::color() const
{
    return ui->color->color();
}
