#include "mdetail.h"

MDetail::MDetail(QString name, QString mettName, QString mettState, QString mettTime_s, QString mettTime_e, QWidget *parent) : QWidget(parent)
{
      m_dockwidget = new QWidget(this);
      m_dockwidget->resize(180,60);
      this->appoinment_name = name;
      this->metting_name = mettName;
      this->metting_state = mettState;
      this->metting_time_s = mettTime_s;
      this->metting_time_e = mettTime_e;
      this->resize(180,60);

      m_dockwidget->setStyleSheet("border-image:url(:/image/Image/back.png);border-radius:15px;");
      QFont font("微软雅黑",12);

      QHBoxLayout *hbox1 = new QHBoxLayout();
      QLabel* appoinment_label = new QLabel();
      appoinment_label->setFont(font);
      appoinment_label->setText(appoinment_name);
      appoinment_label->setStyleSheet("border-image:url();background-color: transparent;");
      state_label = new QLabel();
      state_label->setAlignment(Qt::AlignCenter);
      state_label->setText(metting_state);
      state_label->setStyleSheet("border-image:url();border-radius:15px;");
      hbox1->setContentsMargins(25,2,0,0);
      hbox1->addWidget(appoinment_label);
      hbox1->addWidget(state_label);

      QHBoxLayout* hbox2 = new QHBoxLayout();
      QLabel* mettNameLabel = new QLabel();


      mettNameLabel->setText(mettName);
      mettNameLabel->setFont(QFont("宋体",10));
      mettNameLabel->setStyleSheet("border-image:url();background-color: transparent;");
      mettNameLabel->setAlignment(Qt::AlignCenter);
      hbox2->addWidget(mettNameLabel);

      QHBoxLayout* hbox3 = new QHBoxLayout();
      QLabel* mettTimeLabel = new QLabel();

      QStringList list_s = metting_time_s.split(" ");
      QStringList list_e = metting_time_e.split(" ");
      if(list_s.size()>1 && list_e.size()>1)
      {
          mettTimeLabel->setText(list_s[1] +"-"+list_e[1]);
      }
      mettTimeLabel->setAlignment(Qt::AlignCenter);
      mettTimeLabel->setFont(QFont("宋体",11));
      mettTimeLabel->setStyleSheet("border-image:url();background-color: transparent;");
      hbox3->addWidget(mettTimeLabel);

      QVBoxLayout* vbox = new QVBoxLayout(m_dockwidget);
      vbox->addLayout(hbox1);
      vbox->addLayout(hbox2);
      vbox->addLayout(hbox3);
      m_dockwidget->setLayout(vbox);
      QHBoxLayout *main_box = new QHBoxLayout(this);
      main_box->addWidget(m_dockwidget);
      this->setLayout(main_box);

      timer = new QTimer(this);
      connect(timer,&QTimer::timeout,this,&MDetail::check_status);
      timer->start(500);

}

void MDetail::check_status()
{
    QDateTime start = QDateTime::fromString(metting_time_s, "yyyy-MM-dd hh:mm:ss");
    QDateTime end = QDateTime::fromString(metting_time_e, "yyyy-MM-dd hh:mm:ss");
    uint stime = start.toTime_t();
    uint etime = end.toTime_t();
    uint ntime = QDateTime::currentDateTime().toTime_t();
    //qDebug()<<"stime"<<start<<"end"<<end<<"now"<<QDateTime::currentDateTime();
    //           qDebug()<<"stime"<<time_s<<"end"<<time_e<<"now"<<QDateTime::currentDateTime();
    //           qDebug()<<"stime"<<stime<<"end"<<etime<<"now"<<ntime;
    //           qDebug()<<metting_name<<ntime - stime;
    if((stime > ntime)||(etime > ntime))
    {
        if((stime - ntime  <= 2)||((stime < ntime)&&(etime>ntime)))//uint befor or going
        {
            state_label->setText("进行中");
            state_label->setStyleSheet("border-image:url();background-color:yellow;color:white;");
            if(star_signal)
            {
                emit start_signal(appoinment_name,metting_name,end);
                star_signal = false;
            }
        }
    }
    if(ntime > etime)
    {
        state_label->setText("已结束");
        state_label->setStyleSheet("border-image:url();background-color:red;color:white;");

    }
    if(ntime < stime )
    {
        if( metting_name == "暂无预约")
            state_label->setText("无预约");
        else
            state_label->setText("已预约");
        state_label->setStyleSheet("border-image:url();background-color:green;color:white;");
    }
}

