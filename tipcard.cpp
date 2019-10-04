#include "tipcard.h"

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c)
    : ThreeDimenButton(parent), key(k), title(t), content(c)
{
    setBgColor(Qt::yellow);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 初始化控件
    title_label = new QLabel(title, this);
    content_label = new QLabel(content, this);
    close_button = new InteractiveButtonBase(QIcon(":/icons/hide_right"), this);
    operator1_button = nullptr;
    operator2_button = nullptr;

    // 初始化布局
    QHBoxLayout* margin_hlayout = new QHBoxLayout(this);
    {
        margin_hlayout->setSpacing(0);
        QVBoxLayout* main_vlayout = new QVBoxLayout;
        {
            main_vlayout->setSpacing(0);

            // 添加标题
            QHBoxLayout* title_hlayout = new QHBoxLayout;
            {
                title_hlayout->setSpacing(0);

                title_hlayout->addWidget(title_label);
                title_hlayout->addWidget(close_button);
            }
            // 添加内容
            main_vlayout->addSpacing(aop_h*2);
            main_vlayout->addLayout(title_hlayout);
            main_vlayout->addWidget(content_label);
            // 添加按钮
            btn_layout = new QHBoxLayout;
            main_vlayout->addLayout(btn_layout);
            main_vlayout->addSpacing(aop_h*2);
        }
        margin_hlayout->addSpacing(aop_w*2);
        margin_hlayout->addLayout(main_vlayout);
        margin_hlayout->addSpacing(aop_w*2);
    }
    setLayout(margin_hlayout);

    initCard();
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b)
    : TipCard(parent, k, t, c)
{
    // 添加一个按钮
    btn_layout->addWidget(operator1_button = new InteractiveButtonBase(btn1_title = b, this));

    this->setFixedSize(width(), height() + operator1_button->height());
}

TipCard::TipCard(QWidget *parent, QString k, QString t, QString c, QString b1, QString b2)
    : TipCard(parent, k, t, c, b1)
{
    // 添加两个按钮
    btn_layout->addWidget(operator2_button = new InteractiveButtonBase(btn2_title = b2, this));
}

void TipCard::initCard()
{
    is_closing = false;
    has_leaved = false;

    // 事件
    connect(close_button, SIGNAL(clicked(bool)), this, SLOT(slotClosed()));

    // 定时器
    close_timer = new QTimer(this);
    close_timer->setSingleShot(true);
    connect(close_timer, SIGNAL(timeout()), this, SLOT(slotClosed()));

    // 高度
    title_label->setStyleSheet("background-color: red;");
    content_label->setStyleSheet("background-color:green;");
    title_label->setFixedHeight(getWidgetHeight(title_label));
    content_label->setFixedHeight(getWidgetHeight(content_label));
    int height = title_label->height() + content_label->height() + aop_h*4 + TIP_CARD_CONTENT_MARGIN*2;
    if (operator1_button != nullptr)
        height += operator1_button->height();
    setMinimumSize(100, max(50, height));

    // 布局
    close_button->setFixedSize(title_label->height(), title_label->height());

    if (parentWidget() != nullptr)
        setFixedWidth(parentWidget()->width());
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
    return this->size();
}

void TipCard::startWaitingLeave()
{
    close_timer->start(has_leaved ? 1000 : 5000);
}

void TipCard::pauseWaitingLeave()
{
    close_timer->stop();
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

    has_leaved = true;
}

template<typename T>
int TipCard::getWidgetHeight(T *w)
{
    QStringList strs = w->text().split("\n"); // 分成多行
    int w_width = w->width();                 // 控件宽度（用以拆分长字符串为多行）
    int height = 0;
    QFontMetrics fm = w->fontMetrics();
    double mPixelPerCentimer = 1.0;
    int linesCount = 0;                       // 放在控件上的文字总行数（非换行数）
    foreach (QString str, strs)
    {
        double tempWidth = fm.horizontalAdvance(str) / mPixelPerCentimer; // 字数转行数
        linesCount += (tempWidth+w_width-1) / w_width;
    }
    height = fm.lineSpacing() * linesCount; // 总高度 = 单行高度 × 行数
    return height;
}
