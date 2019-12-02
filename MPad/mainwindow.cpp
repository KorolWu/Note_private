#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(PAD_X,PAD_Y);
    State_widget = new QWidget(this);
    State_widget->resize(200,PAD_Y);
    State_widget->setWindowOpacity(0.5);
    State_widget->setStyleSheet("background-color:rgb(213, 213, 213);border-radius:15px;");

    Info_widget = new QWidget(this);
    Info_widget->resize(PAD_X-204,PAD_Y);
    Info_widget->setStyleSheet("border-image:url(:/image/Image/infobackimage.png);border-radius:15px;");
    Info_widget->move(204,0);
    QLabel *mettName = new QLabel(Info_widget);
    mettName->setText("光明顶");
    mettName->setFont(QFont("宋体",38));
    mettName->setStyleSheet("border-image:url();");
    mettName->move(150,120);
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

    vbox = new QVBoxLayout(State_widget);
    vbox->setSpacing(70);
    State_widget->setLayout(vbox);

    mdetail = new MDetail("Korol","艾欧尼亚","即将开始","10:00  -  11:00");
    MDetail* mdetail1 = new MDetail("Korol","德玛西亚","即将开始","10:00  -  11:00");

    int count = vbox->count();
    vbox->insertWidget(--count,mdetail1);

    vbox->insertWidget(1,mdetail);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateTimeLabel);
    timer->start(1000);
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
