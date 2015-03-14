#include "loginwindow.h"

LoginWindow::LoginWindow(controller *c, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    cont = c;
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
std::string LoginWindow::getUsername(){
    return ui->usernameInput->text().toStdString();
}
std::string LoginWindow::getPassword(){
    return ui->passwordInput->text().toStdString();
}

void LoginWindow::on_submitButton_clicked(){
    cont->notifyLoginSubmission(getUsername(), getPassword());
}
void LoginWindow::setErrorMessage(std::string error){
    ui->errorMessage->setText(QString(error.c_str()));
}
void LoginWindow::on_actionRegister_triggered(){
    cont->notifyRegistrationRequest();
}
void LoginWindow::on_usernameInput_textChanged(const QString &text){
    if(text.length() >20){
        setErrorMessage("Error: Username may only be 20 characters");
        QString newText = text;
        newText.chop(1);
        ui->usernameInput->setText(newText);
    }
    else{
        setErrorMessage("");
    }
}

void LoginWindow::on_passwordInput_textChanged(const QString &text){
    if(text.length() >30){
        QString newText = text;
        newText.chop(1);
        ui->passwordInput->setText(newText);
    }
}

void LoginWindow::on_passwordInput_returnPressed(){
    cont->notifyLoginSubmission(getUsername(), getPassword());
}
