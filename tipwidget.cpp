#include "tipwidget.h"

TipWidget::TipWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(200, 200);

    sum_height = 0;
}

TipCard *TipWidget::createTipCard(QString key, QString title, QString content)
{
    content += QString("%1").arg(cards.size());
    TipCard * card = new TipCard(this, key, title, content);
    cards.append(card);
    card->show(); // TODO: 记得改成动画的形式
    setAddedAnimation();
    connect(card, SIGNAL(signalClosed(TipCard*)), this, SLOT(slotCardClosed(TipCard*)));

    //adjustCardsPosition();
    return card;
}

TipCard *TipWidget::createTipCard(QString key, QString title, QString content, QString btn1)
{
    TipCard * card = new TipCard(this, key, title, content, btn1);
    cards.append(card);
    card->show(); // TODO: 记得改成动画的形式
    setAddedAnimation();
    connect(card, SIGNAL(signalClosed(TipCard*)), this, SLOT(slotCardClosed(TipCard*)));

    //adjustCardsPosition();
    return card;
}

TipCard *TipWidget::createTipCard(QString key, QString title, QString content, QString btn1, QString btn2)
{
    TipCard * card = new TipCard(this, key, title, content, btn1, btn2);
    cards.append(card);
    card->show(); // TODO: 记得改成动画的形式
    setAddedAnimation();
    connect(card, SIGNAL(signalClosed(TipCard*)), this, SLOT(slotCardClosed(TipCard*)));

    //adjustCardsPosition();
    return card;
}

void TipWidget::adjustPosition()
{
    move(parentWidget()->width()-CARD_FIXED_WIDTH-MARGIN_PARENT_RIGHT, parentWidget()->height()-MARGIN_PARENT_BOTTOM-height());
}

void TipWidget::adjustHeight()
{
    int sum_height = 0;
    for (int i = 0; i < cards.size(); i++)
        sum_height += cards.at(i)->getSize().height();
    setFixedHeight(sum_height);
    adjustPosition();
}

void TipWidget::setAddedAnimation()
{
    int size = cards.size();
    int sum_height = 0;

    // 先设置总的高度
    for (int i = 0; i < size; i++)
        sum_height += cards.at(i)->getSize().height() + CARDS_INTERVAL;
    this->setFixedHeight(sum_height);
    adjustPosition();

    sum_height = 0;
    // 除了最后一个，其他都向上面移动一位
    for (int i = 0; i < size-1; i++)
    {
        TipCard* card = cards.at(i);
        QSize size = card->getSize();
        QRect aim_rect(0, sum_height, size.width(), size.height());
        QRect start_rect = card->geometry();
        start_rect.moveTo(start_rect.left(), start_rect.top()+size.height());

        QPropertyAnimation* animation = new QPropertyAnimation(card, "geometry");
        animation->setDuration(300);
        animation->setStartValue(start_rect);
        animation->setEndValue(aim_rect);
        animation->start();

        //qDebug() << "added animation : " << i << " : " << sum_height << "    " << start_rect << ", " << aim_rect;
        sum_height += size.height() + CARDS_INTERVAL;
    }

    // 最后一个从一个小点扩大到整个卡片
    TipCard* card = cards.at(size-1);
    QRect start_rect(geometry().width()-1, geometry().height()-1, 1, 1);
    QRect end_rect(0, sum_height, card->getSize().width(), card->getSize().height());
    QPropertyAnimation* animation = new QPropertyAnimation(card, "geometry");
    animation->setStartValue(start_rect);
    animation->setEndValue(end_rect);
    animation->setDuration(300);
    animation->start();

    //sum_height += card->size().height() + CARD_FIXED_WIDTH;
    //setFixedHeight(sum_height);
}

int TipWidget::getCardHeight(int index)
{
    int size = cards.size();
    if (index >= size)
        index = size-1;
    int sum_height = 0;
    for (int i = 0; i < index; i++)
    {
        sum_height += cards.at(i)->height() + CARDS_INTERVAL;
    }
    return sum_height;
}

void TipWidget::slotCardClosed(TipCard* removed_card)
{
    int index, sum_height = 0;
    QSize removed_size = removed_card->size();
    for (index = 0; index < cards.size(); index++)
    {
        if (cards.at(index) == removed_card)
            break;

        /*TipCard* card = cards.at(index);
        QSize size = card->getSize();
        QRect aim_rect(0, sum_height + removed_size.height(), size.width(), size.height());
        QRect start_rect = card->geometry();

        QPropertyAnimation* animation = new QPropertyAnimation(card, "geometry");
        animation->setDuration(300);
        animation->setStartValue(start_rect);
        animation->setEndValue(aim_rect);
        animation->start();*/

        sum_height += cards.at(index)->getSize().height() + CARDS_INTERVAL;
    }

    // 要删除的卡片，缩小成右边的一个点
    QRect start_rect(removed_card->geometry());
    QRect end_rect(CARD_FIXED_WIDTH-1, removed_card->geometry().top(), 1, 1);
    QPropertyAnimation* animation = new QPropertyAnimation(removed_card, "geometry");
    animation->setStartValue(start_rect);
    animation->setEndValue(end_rect);
    animation->setDuration(3000);
    animation->start();
    connect(animation, &QPropertyAnimation::finished, [=]{
        // delete removed_card;
        cards.removeOne(removed_card);
        removed_card->close();
        adjustHeight();
    });


}

void TipWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path_back;
    path_back.setFillRule(Qt::WindingFill);
    path_back.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(path_back, QBrush(Qt::red));
    return QWidget::paintEvent(event);
}
