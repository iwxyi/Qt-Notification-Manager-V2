#include "tipcard.h"

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c)
    : QWidget(parent), key(k), title(t), content(c)
{
    // 初始化控件
    title_label = new QLabel(title, this);
    content_label = new QLabel(content, this);

    QPixmap* close_pixmap = new QPixmap(":/icons/hide_right");
    QIcon* close_icon = new QIcon(*close_pixmap);
    close_button = new QPushButton(*close_icon, "", this);

    operator1_button = NULL;
    operator2_button = NULL;

    // 初始化布局
    QVBoxLayout* main_vlayout = new QVBoxLayout(this);
    QHBoxLayout* title_hlayout = new QHBoxLayout;
    title_hlayout->addWidget(title_label);
    title_hlayout->addWidget(close_button);
    main_vlayout->addLayout(title_hlayout);
    main_vlayout->addWidget(content_label);
    setLayout(main_vlayout);

    initCard();
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b)
    : QWidget(parent), key(k), title(t), content(c), btn1_title(b)
{

    initCard();
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b1, QString b2)
    : QWidget(parent), key(k), title(t), content(c), btn1_title(b1), btn2_title(b2)
{

    initCard();
}

void TipCard::initCard()
{
    setMinimumSize(10, 50);
    my_size = this->size();
    is_closing = false;

    // 布局
    close_button->setFixedSize(32, 32);

    if (parentWidget() != NULL)
        setFixedWidth(parentWidget()->width());

    // 事件
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(slotClosed()));

    // 定时器
    close_timer = new QTimer(this);
    close_timer->setSingleShot(true);
    connect(close_timer, SIGNAL(timeout()), this, SLOT(slotClosed()));
    close_timer->start(3000);
}

void TipCard::slotClosed()
{
    if (is_closing) return ;
    emit signalClosed(this);
    is_closing = true;
}

/**
 * 一开始就要保存一个固定的大小变量
 */
QSize TipCard::getSize()
{
    return my_size;
}

void TipCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path_back;
    path_back.setFillRule(Qt::WindingFill);
    path_back.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(path_back, QBrush(Qt::yellow));
    return QWidget::paintEvent(event);
}
