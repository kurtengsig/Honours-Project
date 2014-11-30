#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H
#include <QDialog>
#include "controller.h"

namespace Ui {
class AddFriendDialog;
}
class controller;
class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(controller* c, QWidget *parent = 0);
    ~AddFriendDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddFriendDialog *ui;
    controller* cont;
};

#endif // ADDFRIENDDIALOG_H
