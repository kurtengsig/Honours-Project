#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <QMainWindow>
#include "controller.h"
class controller;
namespace Ui {
class FriendWindow;
}

class FriendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendWindow(controller *c, QWidget *parent = 0);
    ~FriendWindow();

private slots:
    void on_actionLogout_triggered();

private:
    Ui::FriendWindow *ui;
    controller* cont;
};

#endif // FRIENDWINDOW_H
