#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QScreen>
#include <QDesktopServices>
#include "tipwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    TipBox* tip_widget;
};

#endif // MAINWINDOW_H
