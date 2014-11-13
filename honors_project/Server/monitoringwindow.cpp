#include "monitoringwindow.h"
#include "ui_monitoringwindow.h"

MonitoringWindow::MonitoringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MonitoringWindow)
{
    ui->setupUi(this);
}

MonitoringWindow::~MonitoringWindow()
{
    delete ui;
}
