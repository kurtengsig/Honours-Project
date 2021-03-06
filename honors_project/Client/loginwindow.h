#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "loginwindow.h"
#include <QMainWindow>
#include <QDebug>
#include "ui_loginwindow.h"
#include "controller.h"
class controller;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit LoginWindow(controller *c, QWidget *parent = 0);
    ~LoginWindow();
    void setErrorMessage(std::string error);

private slots:
    void on_submitButton_clicked();
    void on_actionRegister_triggered();

    void on_usernameInput_textChanged(const QString &arg1);

    void on_passwordInput_textChanged(const QString &arg1);

    void on_passwordInput_returnPressed();

private:
    Ui::LoginWindow* ui;
    controller* cont;
    std::string getUsername();
    std::string getPassword();
};

#endif // LOGINWINDOW_H
