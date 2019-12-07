#include "mettingfrom.h"
#include <QDebug>
MettingFrom::MettingFrom(QString appoinment_name, QString topic_name, QDateTime end_time, QWidget *parent) : QWidget(parent)
{
    m_end_time = end_time;
    this->resize(PAD_X,PAD_Y);
    this->move(700,300);
    this->setStyleSheet("background-color:rgb(233, 233, 233);");
    log_lab = new QLabel(this);
    //log_lab->resize(60,30);
    QPixmap pixmap(":/image/Image/log.png");
    pixmap = pixmap.scaled(300,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    log_lab->setPixmap(pixmap);
    log_lab->show();

    QFont font("方正舒体",35);
    appoinment_name_lab = new QLabel(this);
    appoinment_name_lab->resize(300,60);
    appoinment_name_lab->setAlignment(Qt::AlignCenter);
    appoinment_name_lab->setFont(font);
    appoinment_name_lab->setText(appoinment_name);
    appoinment_name_lab->move(180,110);

    topic_lab = new QLabel(this);
    topic_lab->resize(300,60);
    topic_lab->setAlignment(Qt::AlignCenter);
    QFont font_topic("宋体",28);
    topic_lab->setText(topic_name);
    topic_lab->setFont(font_topic);
    topic_lab->move(180,180);

    QLabel* lab = new QLabel(this);
    lab->setText("           会议进行中 ...         ");
    QFont font_lab("黑体",25);
    lab->setAlignment(Qt::AlignCenter);
    lab->setFont(font_lab);
    lab->setStyleSheet("background-color:red;border-radius:25px;color:white;");
    lab->move(170,270);
    time_d_label = new QLabel(this);
    time_d_label->move(480,10);
    time_d_label->setFont(QFont("宋体",18));
    time_d_label->resize(200,50);
    time_s_label = new QLabel(this);
    time_s_label->move(490,50);
    time_s_label->resize(200,50);
    time_s_label->setFont(QFont("宋体",18));

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MettingFrom::update_time);
    timer->start(1000);
    m_end = m_end_time.toTime_t();
    qDebug()<<"new mettingFrom "<<"end time "<<end_time<<"m_end_int"<<m_end<< "now_int"<<QDateTime::currentDateTime().toTime_t();;

}

void MettingFrom::weakupMainwindow()
{


}

void MettingFrom::update_time()
{
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QStringList list = str.split(" ");
    time_d_label->setText(list[0]);
    time_s_label->setText(list[1]);
    uint now = QDateTime::currentDateTime().toTime_t();
    if(now >= m_end)
    {
        weakup_mainwindow();
        //this->hide();
        this->close();
        this->deleteLater();
    }
}
