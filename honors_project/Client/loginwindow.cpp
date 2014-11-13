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
