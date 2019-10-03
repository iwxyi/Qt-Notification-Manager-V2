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

void MainWindow::resizeEvent(QResizeEvent *)
{
    tip_widget->adjustPosition();
}

void MainWindow::on_pushButton_clicked()
{
    tip_widget->createTipCard("key", "title", "content1\ncontent2\ncontent3");
}
