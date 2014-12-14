#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H
#include <QScrollBar>
#include <QMainWindow>
#include "conversationcontroller.h"

namespace Ui {
class ConversationWindow;
}

class ConversationController;
class ConversationWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ConversationWindow(ConversationController* c, std::string myName, std::string friendName, QWidget *parent = 0);
    ~ConversationWindow();
    void addTheirMessage(std::string message);
    void addMyMessage(std::string message);

private slots:
    void on_sendMessageButton_clicked();

private:
    Ui::ConversationWindow *ui;
    std::string friendName;
    std::string username;
    ConversationController* cont;
};

#endif // CONVERSATIONWINDOW_H
