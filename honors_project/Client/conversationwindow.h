#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H
#include <QScrollBar>
#include <QMainWindow>

namespace Ui {
class ConversationWindow;
}

class ConversationWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ConversationWindow(std::string friendName, QWidget *parent = 0);
    ~ConversationWindow();
    void addNewMessage(std::string user, std::string message);

private slots:
    void on_sendMessageButton_clicked();

private:
    Ui::ConversationWindow *ui;
};

#endif // CONVERSATIONWINDOW_H
