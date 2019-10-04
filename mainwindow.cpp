#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tip_box = new TipBox(this);
    connect(tip_box, &TipBox::signalCardClicked, [=](NotificationEntry* n){
        qDebug() << n->toString();
    });
    connect(tip_box, &TipBox::signalBtnClicked, [=](NotificationEntry* n){
        qDebug() << n->toString();
    });

    QScreen* screen = QApplication::screenAt(QCursor::pos());
    QRect rect = screen->availableGeometry();
    move(rect.center()-QPoint(width()/2,height()/2));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    tip_box->adjustPosition();
}

void MainWindow::on_pushButton_clicked()
{
    NotificationEntry* noti = new NotificationEntry("key", "title", "这是一个通知通知通知通知通知通知通知通知通知通知通知通知");
    tip_box->createTipCard(noti);
}

void MainWindow::on_pushButton_2_clicked()
{
    NotificationEntry* noti = new NotificationEntry("key", "title", "content1\ncontent2\ncontent3");
    noti->btn1 = "btn1";
    tip_box->createTipCard(noti);
}

void MainWindow::on_pushButton_3_clicked()
{
    NotificationEntry* noti = new NotificationEntry("key", "title", "content1");
    noti->setBtn(1, "btn1", "cmd1");
    noti->setBtn(2, "btn2", "cmd2");
    tip_box->createTipCard(noti);

    connect(noti, &NotificationEntry::signalCardClicked, [=]{
        qDebug() << "通知被点击";
    });
    connect(noti, &NotificationEntry::signalBtnClicked, [=](int x){
        qDebug() << "按钮被点击" << x;
    });
}

void MainWindow::on_pushButton_4_clicked()
{
    NotificationEntry* noti = new NotificationEntry("key", "title", "content1");
    noti->btn1 = "btn1";
    noti->btn2 = "btn2";
    noti->btn3 = "btn3";
    tip_box->createTipCard(noti);
}
