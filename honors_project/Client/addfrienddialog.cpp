#include "addfrienddialog.h"
#include "ui_addfrienddialog.h"

AddFriendDialog::AddFriendDialog(controller* c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriendDialog)
{
    ui->setupUi(this);
    cont = c;
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

void AddFriendDialog::on_buttonBox_accepted(){
    cont->notifyAddFriendRequest(std::string (ui->usernameInput->text().toStdString()));
}
