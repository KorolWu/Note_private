#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <jeson2object.h>
#include <QVariantHash>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    desktop =  QApplication::desktop()->availableGeometry();
    qDebug()<<"x "<<desktop.width();
    qDebug()<<"y"<<desktop.height();
    PAD_X = desktop.width();
    PAD_Y = desktop.height();
    ui->setupUi(this);
    this->resize(PAD_X,PAD_Y);
    this->setWindowTitle("Intelligent Meeting");
    this->setWindowFlag(Qt::FramelessWindowHint);
    //this->move(700,300);
    metting = nullptr;
    getParameter();
    State_widget = new QScrollArea(this);
    QWidget* widget_containt = new QWidget();
    widget_containt->resize(PAD_X/3,PAD_Y);
    State_widget->setWidget(widget_containt);
    State_widget->setWidgetResizable(true);
    State_widget->resize(PAD_X/5,PAD_Y);
    State_widget->setWindowOpacity(0.5);
    State_widget->setStyleSheet("background-color:rgb(213, 213, 213);border-radius:15px;");//213, 213, 213,153, 153, 153

    Info_widget = new QWidget(this);
    Info_widget->resize(PAD_X/5*4,PAD_Y);
    Info_widget->setStyleSheet("border-image:url(:/image/Image/infobackimage.png);border-radius:15px;");
    Info_widget->move(PAD_X/5,0);
    QLabel *mettName = new QLabel(Info_widget);
    mettName->setText(m_metting_room);
    mettName->setFont(QFont("宋体",38));
    mettName->setStyleSheet("border-image:url();");
    mettName->move(Info_widget->width()/2-80,Info_widget->height()/2-200);
    time_d_label = new QLabel(Info_widget);
    time_d_label->setFont(QFont("微软雅黑",20));
    time_d_label->setStyleSheet("border-image:url();");
    time_d_label->resize(400,50);
    time_d_label->move(Info_widget->width()/2-100,Info_widget->height()/2);
    time_s_label = new QLabel(Info_widget);
    time_s_label->setFont(QFont("微软雅黑",20));
    time_s_label->setStyleSheet("border-image:url();");
    time_s_label->move(Info_widget->width()/2-80,Info_widget->height()/2-80);
    time_s_label->resize(400,50);
//    QPushButton* btn = new QPushButton(Info_widget);
//    btn->move(160,300);
//    btn->setText("Test");
//    connect(btn,&QPushButton::clicked,this,&MainWindow::btn_test);

    vbox = new QVBoxLayout();
    vbox->addStretch();
    State_widget->widget()->setLayout(vbox);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateTimeLabel);
    timer->start(1000);

    mdetail = new MDetail("空闲中","暂无预约","接收预约","08:50-08:51","");
    connect(mdetail,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
    int count = vbox->count();
    count = vbox->count();
    vbox->insertWidget(--count,mdetail);

    connectToServer();
    p_resive_timer = new QTimer(this);
    connect(p_resive_timer,&QTimer::timeout,this,&MainWindow::sendWebsocketMessage);
    p_resive_timer->start(6000);

//    onTextMessageReceived("");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimeLabel()
{
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QStringList list = str.split(" ");
    time_d_label->setText(list[0]);
    time_s_label->setText(list[1]);
    if(is_alive == true && one_flag == false)
    {
        sendWebsocketMessage();
        one_flag = true;
    }
}

void MainWindow::getParameter()
{
    My_Config myconfig ;
    myconfig.Config("/config.ini");
//    qDebug()<<"ip:  "<<myconfig.Get("socket","ip").toString();
//    qDebug()<<"port:  "<<myconfig.Get("socket","port").toInt();
//    qDebug()<<"url:  "<<myconfig.Get("http","url").toString();
//    qDebug()<<"path:  "<<myconfig.Get("metting","room_name").toString();

     m_url = myconfig.Get("http","url").toString();
     m_metting_room = myconfig.Get("metting","room_name").toString();
}

void MainWindow::connectToServer()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::webSocketDisconnect);
    m_webSocket.open(m_url);
}

void MainWindow::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &MainWindow::onTextMessageReceived);
    is_alive = true;
    qDebug()<<"链接成功";
    //sendWebsocketMessage();
}

void MainWindow::onTextMessageReceived(QString message)
{

    qDebug()<<"收到的数据 "<<message.toLocal8Bit();
    if(message == m_resiveStr)
        return;
     //message = "{\"code\": 0, \"msg\": \"\\u67e5\\u627e\\u5b8c\\u6210\", \"data\": {\"\\u573a\\u666f1\": [{\"OrderNum\": \"191011090412100\", \"WorkerNumber\": \"CWA732\", \"StartTime\": \"2020-02-12 11:12:00\", \"EndTime\": \"2020-02-12 12:14:00\", \"state\": \"delete\", \"topic\": \"\\u667a\\u6167\\u697c\\u5b87\\u9879\\u76ee\"}, {\"OrderNum\": \"191011090412102\", \"WorkerNumber\": \"CWA732\", \"StartTime\": \"2020-02-12 13:12:00\", \"EndTime\": \"2020-02-12 14:14:00\", \"state\": \"delete\", \"topic\": \"\\u667a\\u6167\\u8f66\\u5e93\"}, {\"OrderNum\": \"191011090412103\", \"WorkerNumber\": \"CWA732\", \"StartTime\": \"2020-02-18 13:12:00\", \"EndTime\": \"2020-02-18 14:25:00\", \"state\": \"delete\", \"topic\": \"\\u601d\\u777f\\u8d2f\\u901a\\u9879\\u76ee\"}, {\"OrderNum\": \"191011090412105\", \"WorkerNumber\": \"CWA732\", \"StartTime\": \"2020-02-12 19:12:00\", \"EndTime\": \"2020-02-12 20:14:00\", \"state\": \"delete\", \"topic\": \"\\u6606\\u5c71\\u5de5\\u5382\\u9879\\u76ee\"}]}}";
    for(auto it = m_detail_map.begin();it != m_detail_map.end();it++)
    {
        disconnect(it.value(),&MDetail::start_signal,this,&MainWindow::showMettingFrom);
        it.value()->deleteLater();
        it.value() = nullptr;
    }
    m_detail_map.clear();
     Jeson2Object j(message,m_detail_map);
    //clear vbox widget
    QLayoutItem *child;
    while((child = vbox->takeAt(0)) != 0)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
            delete child;
        }
        qDebug()<<child;

    }
    //1 new medetail object
    if(m_detail_map.size() == 0)
    {
        QString start_str = "";
        QDateTime start_time =  QDateTime::fromString(start_str, "yyyy-MM-dd hh:mm:ss");
        uint start_int = start_time.toTime_t();
        MDetail* detail = new MDetail(""," 空闲中 ","","s","");
        m_detail_map.insert(start_int,detail);
         m_resiveStr = message;
        return;
    }

    //make detailMap key bluesocer
    QVector<uint> key_vec;
    for(auto it = m_detail_map.begin();it != m_detail_map.end();it++)
    {
        connect(it.value(),&MDetail::start_signal,this,&MainWindow::showMettingFrom);
        key_vec.append(it.key());
    }

    for(int i = 0;i < key_vec.size();i++)
    {
        for(int j = 0;j < key_vec.size()-1-i; j++)
        {
            if(key_vec[j]>key_vec[j+1])
            {
                uint temp = key_vec[j];
                key_vec[j] = key_vec[j+1];
                key_vec[j+1] = temp;
            }
        }
    }

    //2 index show
    for(int index =0;index <key_vec.size();index++)
    {
        vbox->addStretch();
        uint key = key_vec[index];
        int dex = vbox->count();
        //qDebug()<<"vbox Count"<<dex<<"path Vbox "<<vbox;
        vbox->insertWidget(--dex,m_detail_map[key]);
    }
    //3 time clear
    m_resiveStr = message;

     /**
    **/
}

void MainWindow::webSocketDisconnect()
{
    is_alive = false;
    qDebug()<<"disconnect form service";
}

void MainWindow::sendWebsocketMessage()
{
    if(is_alive == false)
    {
        connectToServer();
        return;
    }
    if(metting == nullptr)
    {
        QString sendMessage = createJsonStr();
        qDebug()<<"sendmessage->"<<sendMessage;
        m_webSocket.sendTextMessage(sendMessage); //"{\"Office_Reservation_search\":[\"场景1\"]}"
    }
}

void MainWindow::this_show()
{
    this->show();
    metting->close();
    metting->deleteLater();
    metting = nullptr;
}

void MainWindow::showMettingFrom(QString appoinment_name, QString metting_name, QDateTime date_time_end)
{
    metting = new MettingFrom(appoinment_name,metting_name,date_time_end);
    connect(metting,&MettingFrom::weakup_mainwindow,this,&MainWindow::this_show);
    this->hide();
    metting->show();

}

QString MainWindow::createJsonStr()
{
    QVariantHash data;
    QJsonArray array1;
    array1.insert(0,m_metting_room);
    data.insert("Office_Reservation_search",array1);
    QJsonObject rootObj = QJsonObject::fromVariantHash(data);
    QJsonDocument document;
    document.setObject(rootObj);

    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    qDebug()<<json_str;
    return json_str;
}


void MainWindow::btn_test()
{
//    QString str ="{\"code\":0,\"msg\":\"查找完成\",\"data\":{\"terminal1\":[{\"OrderNum\":\"191011090412104\",\"WorkerNumber\":\"CWA666\","
//                 "\"StartTime\":\"2020-02-10 16:50:00\",\"EndTime\":\"2020-02-10 16:51:00\"},{\"OrderNum\":\"191011090412105\",\"WorkerNumber\":\"CWA732\","
//                                                      "\"StartTime\":\"2020-02-10 16:52:00\",\"EndTime\":\"2020-02-10 16:53:00\"},{\"OrderNum\":\"191011090412105\",\"WorkerNumber\":\"CWA02\","
//                 "\"StartTime\":\"2020-02-10 16:48:00\",\"EndTime\":\"2020-02-10 16:49:00\"}]}}";
//    onTextMessageReceived(str);
    sendWebsocketMessage();
}

void MainWindow::test_json()
{

//    QString str ="{\"code\":0,\"msg\":\"查找完成\",\"data\":{\"terminal1\":[{\"OrderNum\":\"191011090412104\",\"WorkerNumber\":\"CWA732\","
//                 "\"StartTime\":\"2019-10-24 11:12:00\",\"EndTime\":\"2019-10-24 11:14:00\"},{\"OrderNum\":\"191011090412105\",\"WorkerNumber\":\"CWA732\","
//                                                      "\"StartTime\":\"2019-10-24 11:19:00\",\"EndTime\":\"2019-10-24 11:14:00\"}]}}";
//    Jeson2Object j(str,m_detail_map);
    qDebug()<<m_detail_map;
}

