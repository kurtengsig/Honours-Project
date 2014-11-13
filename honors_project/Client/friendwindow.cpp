#include "friendwindow.h"
#include "ui_friendwindow.h"

FriendWindow::FriendWindow(controller *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendWindow)
{
    ui->setupUi(this);
    cont = c;
}

FriendWindow::~FriendWindow(){
    delete ui;
}

void FriendWindow::on_actionLogout_triggered(){
    cont->notifyLogoutRequest();
}
