#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <jeson2object.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(PAD_X,PAD_Y);
    this->move(700,300);
    getParameter();
    State_widget = new QScrollArea(this);
    QWidget* widget_containt = new QWidget();
    widget_containt->resize(160,PAD_Y);
    State_widget->setWidget(widget_containt);
    State_widget->setWidgetResizable(true);
    State_widget->resize(200,PAD_Y);
    State_widget->setWindowOpacity(0.5);
    State_widget->setStyleSheet("background-color:rgb(213, 213, 213);border-radius:15px;");//213, 213, 213,153, 153, 153

    Info_widget = new QWidget(this);
    Info_widget->resize(PAD_X-204,PAD_Y);
    Info_widget->setStyleSheet("border-image:url(:/image/Image/infobackimage.png);border-radius:15px;");
    Info_widget->move(204,0);
    QLabel *mettName = new QLabel(Info_widget);
    mettName->setText(m_metting_room);
    mettName->setFont(QFont("宋体",38));
    mettName->setStyleSheet("border-image:url();");
    mettName->move(160,120);
    time_d_label = new QLabel(Info_widget);
    time_d_label->setFont(QFont("微软雅黑",20));
    time_d_label->setStyleSheet("border-image:url();");
    time_d_label->resize(200,50);
    time_d_label->move(150,200);
    time_s_label = new QLabel(Info_widget);
    time_s_label->setFont(QFont("微软雅黑",20));
    time_s_label->setStyleSheet("border-image:url();");
    time_s_label->move(160,240);
    time_s_label->resize(200,50);
    QPushButton* btn = new QPushButton(Info_widget);
    btn->move(160,300);
    btn->setText("Test");
    connect(btn,&QPushButton::clicked,this,&MainWindow::btn_test);

    vbox = new QVBoxLayout();
    vbox->addStretch();
    State_widget->widget()->setLayout(vbox);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateTimeLabel);
    timer->start(1000);


    mdetail = new MDetail("Korol","艾欧尼亚","即将开始","08:50-08:51");
    connect(mdetail,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
//    mdetail1 = new MDetail("Korol","德玛西亚","即将开始","09:07-09:08");
//    connect(mdetail1,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
    int count = vbox->count();
    qDebug()<<"count"<<count;
    //vbox->insertWidget(--count,mdetail1);
    count = vbox->count();
    vbox->insertWidget(--count,mdetail);
     count = vbox->count();
//     mdetail2 = new MDetail("Korol","比尔吉沃特","即将开始","09:09-09:10");
//     connect(mdetail2,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
//     vbox->insertWidget(--count,mdetail2);

     mdetail3 = new MDetail("Korol","黑色玫瑰","即将开始","16:00-16:11");
     connect(mdetail3,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
     vbox->insertWidget(--count,mdetail3);
     mdetail4 = new MDetail("Korol","教育专区","即将开始","16:19-16:21");
     connect(mdetail4,&MDetail::start_signal,this,&MainWindow::showMettingFrom);
     vbox->insertWidget(--count,mdetail4);

    connectToServer();

    //json
    test_json();
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
}

void MainWindow::getParameter()
{
    My_Config myconfig ;
    myconfig.Config("/root/2019/git_note/Note_private/config.ini");
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
}

void MainWindow::onTextMessageReceived(QString message)
{
    //clear vbox widget
    QLayoutItem *child;
    qDebug()<<vbox<<"vboxLayout";
    while((child = vbox->takeAt(0)) != 0)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
            delete child;
        }
        qDebug()<<child;

    }

    // delete vbox;
//    QList<QWidget*> widget_list = vbox->findChildren<QWidget*>();
//      qDebug()<<"vbox Count"<<vbox->count();
//    foreach (QWidget* w, widget_list) {
//        delete w;
//    }

    //1 new medetail object
    QString start_str = "";
    QDateTime start_time =  QDateTime::fromString(start_str, "yyyy-MM-dd hh:mm:ss");
    uint start_int = start_time.toTime_t();
    MDetail* detail = new MDetail(""," 空闲中 ","","");
    m_detail_map.insert(start_int,detail);

    //make detailMap key bluesocer
    QVector<uint> key_vec;
    for(auto it = m_detail_map.begin();it != m_detail_map.end();it++)
    {
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

//    qDebug()<<message;
     /**
    **/
}

void MainWindow::webSocketDisconnect()
{
    is_alive = false;
}

void MainWindow::sendWebsocketMessage()
{
    m_webSocket.sendTextMessage(m_metting_room);
}

void MainWindow::this_show()
{
    this->show();
}

void MainWindow::showMettingFrom(QString appoinment_name, QString metting_name, QDateTime date_time_end)
{
    MettingFrom* metting = new MettingFrom(appoinment_name,metting_name,date_time_end);
    connect(metting,&MettingFrom::weakup_mainwindow,this,&MainWindow::this_show);
    this->hide();
    metting->show();

}

void MainWindow::btn_test()
{
    onTextMessageReceived("---");
}

void MainWindow::test_json()
{
    Jeson2Object j;
    //QString str =""

    j.parseJsonFile("{ \"sites\": [ { \"name\":\"cainiao\" , \"url\":\"www.runoob.com\" }, {\"name\":\"google\" , \"url\":\"www.google.com \"}]}");
}
