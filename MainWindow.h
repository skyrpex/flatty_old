#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class JointModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    JointModel *m_model;
};

#endif // MAINWINDOW_H
