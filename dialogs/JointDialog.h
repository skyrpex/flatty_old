#ifndef JOINTDIALOG_H
#define JOINTDIALOG_H

#include <QDialog>

namespace Ui {
class JointDialog;
}

class JointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JointDialog(const QString &parentName, QWidget *parent = 0);
    JointDialog(const QString &name, const QColor &color, QWidget *parent = 0);
    ~JointDialog();

    QString name() const;
    QColor color() const;

private:
    Ui::JointDialog *ui;
};

#endif // JOINTDIALOG_H
