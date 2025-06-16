#include "s13.h"
#include <QtWidgets/QApplication>
#include "UserMessage.h"
#include "ChatSession.h"
#include "ChatWindow.h"

int main(int argc, char *argv[])
{
    {
        QApplication a(argc, argv);

        ChatSession session;

        ChatWindow* cw1 = new ChatWindow("user1", "Alan", session);
        ChatWindow* cw2 = new ChatWindow("user2", "Bob", session);
        ChatWindow* cw3 = new ChatWindow("user3", "Charlie", session);

        cw1->show();
        cw2->show();
        cw3->show();

        a.exec();
    }
    return 0;
}
