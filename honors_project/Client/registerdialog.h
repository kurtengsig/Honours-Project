#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include <QDebug>
#include <QDialog>
#include "controller.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(controller *cont, QWidget *parent = 0);
    ~RegisterDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RegisterDialog *ui;
    controller* c;
};

#endif // REGISTERDIALOG_H
