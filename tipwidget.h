#ifndef TIPBOXWIDGET_H
#define TIPBOXWIDGET_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include "tipcard.h"

#define CARDS_INTERVAL 0
#define MARGIN_PARENT_RIGHT 20
#define MARGIN_PARENT_BOTTOM 10
#define CARD_FIXED_WIDTH 200

class TipBox : public QWidget
{
    Q_OBJECT
public:
    explicit TipBox(QWidget *parent);
    TipCard* createTipCard(QString key, QString title, QString content);
    TipCard* createTipCard(QString key, QString title, QString content, QString btn1);
    TipCard* createTipCard(QString key, QString title, QString content, QString btn1, QString btn2);

    void setBgColor(QColor c);
    void setFontColor(QColor c);
    void setBtnColor(QColor c);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void addCard(TipCard *card);

signals:
    void signalCardClosed(QString key);

public slots:
    void slotCardClosed(TipCard* card);
    void adjustPosition();

private:
    QList<TipCard*> cards;
    int sum_height;
    bool hovering;

    // 保存色彩值
    QColor bg_color;
    QColor font_color;
    QColor btn_color;
};

#endif // TIPBOXWIDGET_H
