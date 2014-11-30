#include "conversationwindow.h"
#include "ui_conversationwindow.h"

ConversationWindow::ConversationWindow(std::string friendName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConversationWindow)
{
    ui->setupUi(this);
    ui->friendLabel->setText(("Talking to: "+friendName).c_str());
}

ConversationWindow::~ConversationWindow(){
    delete ui;
}
void ConversationWindow::addNewMessage(std::string user, std::string message){
    ui->messageDisplayArea->insertHtml((user+": "+message+"<br>").c_str());
    QScrollBar* qsb = ui->messageDisplayArea->verticalScrollBar();
    qsb->setValue(qsb->maximum());
}

void ConversationWindow::on_sendMessageButton_clicked()
{
    addNewMessage("Kurt", "Hi");
}
