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

class TipWidget;

class TipCard : public QWidget
{
    Q_OBJECT
    friend class TipWidget;
public:
    TipCard(QWidget *parent, QString k, QString t, QString c);
    TipCard(QWidget *parent, QString k, QString t, QString c, QString b);
    TipCard(QWidget *parent, QString k, QString t, QString c, QString b1, QString b2);

    void showAnimation(QPoint aim_point);
    void downAnimation(QPoint aim_point, int delay);
    void upAnimation(QPoint aim_point, int delay);
    void closeAnimation(QPoint aim_point);

    QSize getSize();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void initCard();

signals:
    void signalClosed(TipCard* card);
    void signalButton1Clicked(QString key);
    void signalButton2Clicked(QString key);

public slots:

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
    QPushButton* settings_button;
    QPushButton* close_button;
    QTimer* close_timer;

    QPropertyAnimation* animation;
    QSize my_size; // 自己固定的大小，以后都不能变！（直到删除）
};

#endif // TIPBOXCARD_H
