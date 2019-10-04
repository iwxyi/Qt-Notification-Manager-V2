#include "tipwidget.h"

TipBox::TipBox(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(200, 200);

    sum_height = MARGIN_PARENT_BOTTOM;
    hovering = false;
}

TipCard *TipBox::createTipCard(QString key, QString title, QString content)
{
    content += QString("%1").arg(cards.size());
    TipCard * card = new TipCard(this, key, title, content);
    addCard(card);
    return card;
}

TipCard *TipBox::createTipCard(QString key, QString title, QString content, QString btn1)
{
    TipCard * card = new TipCard(this, key, title, content, btn1);
    addCard(card);
    return card;
}

TipCard *TipBox::createTipCard(QString key, QString title, QString content, QString btn1, QString btn2)
{
    TipCard * card = new TipCard(this, key, title, content, btn1, btn2);
    addCard(card);
    return card;
}

void TipBox::adjustPosition()
{
    move(parentWidget()->width()-CARD_FIXED_WIDTH-MARGIN_PARENT_RIGHT, parentWidget()->height()-MARGIN_PARENT_BOTTOM-height());
}

void TipBox::addCard(TipCard* card)
{
    cards.append(card);
    connect(card, SIGNAL(signalClosed(TipCard*)), this, SLOT(slotCardClosed(TipCard*)));
    card->show();

    // 通知卡片显示的高度
    QSize size = card->getSize();
    sum_height += size.height() + MARGIN_PARENT_BOTTOM;
    QRect box_aim(parentWidget()->width()-CARD_FIXED_WIDTH-MARGIN_PARENT_RIGHT,
                  parentWidget()->height()-sum_height-MARGIN_PARENT_BOTTOM,
                  CARD_FIXED_WIDTH,
                  sum_height);
    QPropertyAnimation* box_ani = new QPropertyAnimation(this, "geometry");
    box_ani->setStartValue(geometry());
    box_ani->setEndValue(box_aim);
    box_ani->setDuration(300);
    box_ani->start();

    // 最后一个从一个小点扩大到整个卡片
    QRect start_rect(geometry().width()-1, geometry().height()-1, 1, 1);
    QRect end_rect(0, sum_height-size.height()-MARGIN_PARENT_BOTTOM-CARDS_INTERVAL, card->getSize().width(), card->getSize().height());
    QPropertyAnimation* card_ani = new QPropertyAnimation(card, "geometry");
    card_ani->setStartValue(start_rect);
    card_ani->setEndValue(end_rect);
    card_ani->setDuration(300);
    card_ani->start();

    // 判断位置，如果鼠标不在这上面，则开启定时消失
    if (!hovering)
    {
        card->startWaitingLeave();
    }
}

void TipBox::slotCardClosed(TipCard* removed_card)
{
    int index, temp_height = 0;
    QSize removed_size = removed_card->size();

    // 整体高度变化
    sum_height -= removed_size.height() + CARDS_INTERVAL;
    QRect box_aim(parentWidget()->width()-CARD_FIXED_WIDTH-MARGIN_PARENT_RIGHT,
                  parentWidget()->height()-sum_height-MARGIN_PARENT_BOTTOM,
                  CARD_FIXED_WIDTH,
                  sum_height);
    QPropertyAnimation* box_ani = new QPropertyAnimation(this, "geometry");
    box_ani->setStartValue(geometry());
    box_ani->setEndValue(box_aim);
    box_ani->setDuration(300);
    box_ani->start();

    // 下面的每个卡片上移
    for (index = 0; index < cards.size(); index++)
    {
        if (cards.at(index) == removed_card)
            continue ;
        TipCard* card = cards.at(index);
        QRect end_rect(0, temp_height, CARD_FIXED_WIDTH, card->getSize().height());

        QPropertyAnimation* card_ani = new QPropertyAnimation(card, "geometry");
        card_ani->setStartValue(card->geometry());
        card_ani->setEndValue(end_rect);
        card_ani->setDuration(300);
        card_ani->start();

        temp_height += card->getSize().height() + CARDS_INTERVAL;
    }

    // 要删除的卡片，缩小成右边的一个点
    QRect start_rect(removed_card->geometry());
    QRect end_rect(CARD_FIXED_WIDTH-1, removed_card->geometry().top(), 1, 1);
    QPropertyAnimation* animation = new QPropertyAnimation(removed_card, "geometry");
    animation->setStartValue(start_rect);
    animation->setEndValue(end_rect);
    animation->setDuration(300);
    animation->start();
    connect(animation, &QPropertyAnimation::finished, [=]{
         delete removed_card;
//        removed_card->close();
        //adjustHeight();
    });
    cards.removeOne(removed_card);
}

void TipBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path_back;
    path_back.setFillRule(Qt::WindingFill);
    path_back.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(path_back, QBrush(Qt::blue));
    return QWidget::paintEvent(event);
}

void TipBox::enterEvent(QEvent *event)
{
    hovering = true;
    foreach (TipCard* card, cards) {
        card->pauseWaitingLeave();
    }
    return QWidget::enterEvent(event);
}

void TipBox::leaveEvent(QEvent *event)
{
    hovering = false;
    foreach (TipCard* card, cards) {
        card->startWaitingLeave();
    }
    return QWidget::leaveEvent(event);
}
