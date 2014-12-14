#include "conversationwindow.h"
#include "ui_conversationwindow.h"

ConversationWindow::ConversationWindow(ConversationController* c, std::string myName, std::string fName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConversationWindow)
{
    username = myName;
    friendName = fName;
    cont = c;
    ui->setupUi(this);
    ui->friendLabel->setText(("Talking to: "+friendName).c_str());
}

ConversationWindow::~ConversationWindow(){
    delete ui;
}

void ConversationWindow::on_sendMessageButton_clicked(){
    std::string message = ui->inputField->toPlainText().toStdString();
    addMyMessage(message);
    cont->sendMessage("","","",message);
}
void ConversationWindow::addTheirMessage(std::string message){
    ui->messageDisplayArea->insertHtml((friendName+": "+message+"<br>").c_str());
    QScrollBar* qsb = ui->messageDisplayArea->verticalScrollBar();
    qsb->setValue(qsb->maximum());
}

void ConversationWindow::addMyMessage(std::string message){
    ui->messageDisplayArea->insertHtml((username+": "+message+"<br>").c_str());
    QScrollBar* qsb = ui->messageDisplayArea->verticalScrollBar();
    qsb->setValue(qsb->maximum());
}
