#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H
#include <QScrollBar>
#include <QMainWindow>
#include "conversationcontroller.h"
#include <QTimer>

namespace Ui {
class ConversationWindow;
}

class ConversationController;
class ConversationWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ConversationWindow(ConversationController* c, QWidget *parent = 0);
    ~ConversationWindow();
    void addTheirMessage(std::string message);
    void addMyMessage(std::string message);
    void setUserAndFriend(std::string name, std::string friends);

//public slots:
  //  void addMessage(std::string message);

private slots:
    void on_sendMessageButton_clicked();
    void update();

//signals:
  //  void messagesChanged(std::string);

private:
    Ui::ConversationWindow *ui;
    std::string friendName;
    std::string username;
    ConversationController* cont;
    std::string inputString;
    bool isVisible;
};

#endif // CONVERSATIONWINDOW_H
