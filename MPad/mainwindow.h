#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mdetail.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QVBoxLayout>
#include <mettingfrom.h>
#include <myconfig.h>

#include <QJsonObject>
#include <QJsonDocument>
#include <QtWebSockets/QWebSocket>
#include <QScrollArea>
#include <QApplication>
#include <QDesktopWidget>
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
//    const int PAD_X = 640;
//    const int PAD_Y = 420;
    int PAD_X;
    int PAD_Y;
    //MDetail* mdetail;
    QScrollArea* State_widget;
    QWidget* Info_widget;
    QLabel* time_d_label;
    QLabel* time_s_label;
    QTimer* timer;
    QTimer* p_resive_timer;
    MettingFrom* metting;

    QWebSocket m_webSocket;
    QString m_url;
    QString m_metting_room;
    bool is_alive = false;
    bool one_flag = false;
    //save detail object and start_time
    QMap<uint, MDetail*> m_detail_map;
    QString m_resiveStr = "null";

    //test
    MDetail* mdetail ;
    MDetail* mdetail1 ;
//    MDetail* mdetail2 ;
//    MDetail* mdetail3 ;
//    MDetail* mdetail4 ;
    QRect desktop;
    //test
private:
    void updateTimeLabel();
    void getParameter();
    void connectToServer();
    void onConnected();
    void onTextMessageReceived(QString message);
    void webSocketDisconnect();
    void sendWebsocketMessage();
    void this_show();
    void showMettingFrom(QString appoinment_name,QString metting_name,QDateTime date_time_end);
    QString createJsonStr();
    void btn_test();
    void test_json();
public:
    QVBoxLayout* vbox;
};

#endif // MAINWINDOW_H
