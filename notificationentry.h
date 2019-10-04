#ifndef NOTIFICATIONENTRY_H
#define NOTIFICATIONENTRY_H

#include <QStringList>

struct NotificationEntry
{
public:
    NotificationEntry() : time(5000), click_hide(false)
    {

    }

    enum SuggestButton {
        SB_NONE,
        SB_FIR,
        SB_SEC,
        SB_ALL
    };

    QString key;
    QString title;
    QString content;
    QString desc;
    QString btn1;
    int time;
    bool click_hide;
    QString btn2;
    QString btn3;
    QString cmd1;
    QString cmd2;
    QString cmd3;
    QStringList filters;
    QStringList values;
};

#endif // NOTIFICATIONENTRY_H
