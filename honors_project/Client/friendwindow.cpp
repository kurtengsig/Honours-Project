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

void FriendWindow::on_friendList_itemDoubleClicked(QListWidgetItem *item){
    cont->notifyConversationCreation(item->text().toStdString());
}
void FriendWindow::populateFriendList(std::string* s, int count){
    for(int i=0; i < count; ++i){
        QString q(s[i].c_str());
        ui->friendList->addItem(q);
    }
}

void FriendWindow::on_actionAdd_Friend_triggered(){
    AddFriendDialog* a = new AddFriendDialog(cont);
    a->show();
}

