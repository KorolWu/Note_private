#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mdetail.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QVBoxLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MDetail* mdetail;
    QWidget* State_widget;
    QWidget* Info_widget;
    QLabel* time_d_label;
    QLabel* time_s_label;
    QTimer* timer;
    QVBoxLayout* vbox;
    const int PAD_X = 640;
    const int PAD_Y = 420;
    void updateTimeLabel();
};

#endif // MAINWINDOW_H
