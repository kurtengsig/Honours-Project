#include "conversationwindow.h"
#include "ui_conversationwindow.h"

ConversationWindow::ConversationWindow(ConversationController* c,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConversationWindow)
{
    isVisible = false;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    inputString = "";
    cont = c;
    ui->setupUi(this);
}

ConversationWindow::~ConversationWindow(){
    qDebug() << "deleting window";
    delete ui;
}

void ConversationWindow::on_sendMessageButton_clicked(){
    std::string message = ui->inputField->toPlainText().toStdString();
    std::string cleanMessage = cont->sanitize(message);
    ui->inputField->setText("");
    addMyMessage(cleanMessage);
    cont->sendMessage(cleanMessage);
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
void ConversationWindow::setUserAndFriend(std::string name, std::string friends){
    username = name;
    friendName = friends;
    //ui->friendLabel->setText(("Talking to: "+friendName).c_str());
}
void ConversationWindow::update(){
    //if(!isVisible){
    //    isVisible = true;
    //    this->show();
    //}
    while(cont->hasMessage()){
        addTheirMessage(cont->getMessage());
    }
}
void ConversationWindow::closeEvent(QCloseEvent *){
    cont->notifyClose();
}
