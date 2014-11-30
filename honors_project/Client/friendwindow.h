#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QDebug>
#include <QListWidgetItem>
#include "addfrienddialog.h"
#include "conversationwindow.h"
class controller;
class AddFriendDialog;
namespace Ui {
class FriendWindow;
}

class FriendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendWindow(controller *c, QWidget *parent = 0);
    ~FriendWindow();
    void populateFriendList(std::string*, int count);


private slots:
    void on_actionLogout_triggered();
    void on_friendList_itemDoubleClicked(QListWidgetItem *item);

    void on_actionAdd_Friend_triggered();

private:
    Ui::FriendWindow *ui;
    controller* cont;
};

#endif // FRIENDWINDOW_H
