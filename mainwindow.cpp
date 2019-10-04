#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tip_widget = new TipBox(this);

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

    tip_widget->adjustPosition();
}

void MainWindow::on_pushButton_clicked()
{
    NotificationEntry noti;
    noti.key = "key";
    noti.title = "title";
    noti.content = "content1\ncontent2\ncontent3";
    tip_widget->createTipCard(noti);
}

void MainWindow::on_pushButton_2_clicked()
{
    NotificationEntry noti;
    noti.key = "key";
    noti.title = "title";
    noti.content = "content1\ncontent2\ncontent3";
    noti.btn1 = "btn1";
    tip_widget->createTipCard(noti);
}

void MainWindow::on_pushButton_3_clicked()
{
    NotificationEntry noti;
    noti.key = "key";
    noti.title = "title";
    noti.content = "content1\ncontent2\ncontent3";
    noti.btn1 = "btn1";
    noti.btn2 = "btn2";
    tip_widget->createTipCard(noti);
}

void MainWindow::on_pushButton_4_clicked()
{
    NotificationEntry noti;
    noti.key = "key";
    noti.title = "title";
    noti.content = "content1\ncontent2\ncontent3";
    noti.btn1 = "btn1";
    noti.btn2 = "btn2";
    noti.btn3 = "btn3";
    tip_widget->createTipCard(noti);
}
