#ifndef TIPBOXCARD_H
#define TIPBOXCARD_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QIcon>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QDebug>

class TipBox;

class TipCard : public QWidget
{
    Q_OBJECT
    friend class TipBox;
public:
    TipCard(QWidget *parent, QString k, QString t, QString c);
    TipCard(QWidget *parent, QString k, QString t, QString c, QString b);
    TipCard(QWidget *parent, QString k, QString t, QString c, QString b1, QString b2);

    QSize getSize();

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

private:
    void initCard();

signals:
    void signalClosed(TipCard* card);
    void signalButton1Clicked(QString key);
    void signalButton2Clicked(QString key);


public slots:
    void slotClosed();

private:
    QString key;
    QString title;
    QString content;
    QString btn1_title, btn2_title;
    QString str1, str2, str3;

    QLabel* title_label;
    QLabel* content_label;
    QPushButton* operator1_button;
    QPushButton* operator2_button;
    QPushButton* close_button;
    QTimer* close_timer;

    QPropertyAnimation* animation;
    QSize my_size; // 自己固定的大小，以后都不能变！（直到删除）

    bool is_closing;
};

#endif // TIPBOXCARD_H
