#include "friendwindow.h"
#include "ui_friendwindow.h"

FriendWindow::FriendWindow(controller *c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendWindow)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    ui->setupUi(this);
    cont = c;
}

FriendWindow::~FriendWindow(){
    delete ui;
}

void FriendWindow::on_actionLogout_triggered(){
    cont->notifyLogoutRequest();
}
void FriendWindow::closeEvent(QCloseEvent *){
     cont->notifyLogoutRequest();
}

void FriendWindow::on_friendList_itemDoubleClicked(QListWidgetItem *item){
    std::string friendName = item->text().toStdString();
    if(friendName.find("*") != std::string::npos){
        friendName.replace(friendName.find("*"), 1, "");
    }
    item->setText(QString(friendName.c_str()));
    cont->notifyConversationCreation(friendName);
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

void FriendWindow::update(){
    std::string output[ui->friendList->count()];
    PendingMessage *messages;
    int numberOfMessages = cont->getPendingMessages(&messages);
    int numberOfFriends = getFriends(output);
    for(int i=0; i<numberOfMessages; i++){
        for(int j=0; j<numberOfFriends; j++){
            if(messages[i].getOrigin() == output[j]){
                newPendingMessageForUser(messages[i].getOrigin());
            }
        }
    }

}
int FriendWindow::getFriends(std::string* output){
    for(int i=0; i<ui->friendList->count(); i++){
        output[i] = ui->friendList->item(i)->text().toStdString();
    }
    return ui->friendList->count();
}
void FriendWindow::newPendingMessageForUser(std::string user){
    for(int i=0; i<ui->friendList->count(); i++){
        if(ui->friendList->item(i)->text().toStdString() == user)
            ui->friendList->item(i)->setText(QString((user+"*").c_str()));
    }
}
