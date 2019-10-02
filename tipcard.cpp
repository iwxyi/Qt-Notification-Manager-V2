#include "tipcard.h"

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c)
    : ThreeDimenButton(parent), key(k), title(t), content(c)
{
    setBgColor(Qt::yellow);

    // 初始化控件
    title_label = new QLabel(title, this);
    content_label = new QLabel(content, this);

    QPixmap* close_pixmap = new QPixmap(":/icons/hide_right");
    QIcon* close_icon = new QIcon(*close_pixmap);
    close_button = new InteractiveButtonBase(*close_icon, this);

    operator1_button = nullptr;
    operator2_button = nullptr;

    // 初始化布局
    QHBoxLayout* margin_hlayout = new QHBoxLayout(this);
    {
        QVBoxLayout* main_vlayout = new QVBoxLayout;
        QHBoxLayout* title_hlayout = new QHBoxLayout;
        {
            title_hlayout->setSpacing(0);
            title_hlayout->addWidget(title_label);
            title_hlayout->addWidget(close_button);
        }
        main_vlayout->setSpacing(0);
        main_vlayout->addLayout(title_hlayout);
        main_vlayout->addWidget(content_label);
        margin_hlayout->addSpacing(aop_w*3);
        margin_hlayout->addLayout(main_vlayout);
        margin_hlayout->addSpacing(aop_w*3);
//        margin_hlayout->setMargin(aop_h); // 避免到外面去
    }
    setLayout(margin_hlayout);

    initCard();
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b)
    : ThreeDimenButton(parent), key(k), title(t), content(c), btn1_title(b)
{

    initCard();
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b1, QString b2)
    : ThreeDimenButton(parent), key(k), title(t), content(c), btn1_title(b1), btn2_title(b2)
{

    initCard();
}

void TipCard::initCard()
{
    setMinimumSize(100, 50);
    my_size = this->size();
    is_closing = false;

    // 布局
    close_button->setFixedSize(32, 32);

    if (parentWidget() != nullptr)
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
    ThreeDimenButton::paintEvent(event);
}

void TipCard::enterEvent(QEvent *event)
{
    ThreeDimenButton::enterEvent(event);

    if (is_closing) return ;

    close_timer->stop();
}

void TipCard::leaveEvent(QEvent *event)
{
    ThreeDimenButton::leaveEvent(event);

    close_timer->start(1000);
}
