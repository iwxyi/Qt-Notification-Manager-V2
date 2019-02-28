#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tip_widget = new TipBox(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    tip_widget->adjustPosition();
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << ("create card");
    tip_widget->createTipCard("key", "title", "content");
}
