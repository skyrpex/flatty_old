#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AnimDialog;
}

class AnimDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnimDialog(QWidget *parent = 0);
    AnimDialog(const QString &name, int frameCount, int fps, QWidget *parent = 0);
    ~AnimDialog();

    QString name() const;
    int frameCount() const;
    int fps() const;

private:
    Ui::AnimDialog *ui;
};

#endif // ANIMATIONDIALOG_H
