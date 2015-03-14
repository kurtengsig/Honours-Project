#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(controller *cont, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog){
    ui->setupUi(this);
    c = cont;
}

RegisterDialog::~RegisterDialog(){
    delete ui;
}

void RegisterDialog::on_buttonBox_accepted(){
    c->notifyRegistrationSubmission(ui->usernameInput->text().toStdString().c_str(),ui->passwordInput->text().toStdString().c_str());
}

void RegisterDialog::on_buttonBox_rejected(){
    qDebug() << "Cancelled";
}
