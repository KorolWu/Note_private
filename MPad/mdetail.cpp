#include "mdetail.h"

MDetail::MDetail(QString name,QString mettName,QString mettState,QString mettTime,QWidget *parent) : QWidget(parent)
{
      m_dockwidget = new QWidget(this);
      m_dockwidget->resize(180,80);
      this->appoinment_name = name;
      this->metting_name = mettName;
      this->metting_state = mettState;
      this->metting_time = mettTime;

      //this->setStyleSheet("background-color:rgb(63, 147, 168);color:white;border-radius:15px;");///media/root/F8FE9A09FE99BFF4/back.png
      this->setStyleSheet("border-image:url(:/image/Image/back.png);border-radius:25px;");
      QFont font("微软雅黑",12);

      QHBoxLayout *hbox1 = new QHBoxLayout();
      QLabel* appoinment_label = new QLabel();
      appoinment_label->setFont(font);
      appoinment_label->setText(appoinment_name);
      appoinment_label->setStyleSheet("border-image:url();background-color: transparent;");
      QLabel* state_label = new QLabel();
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
      mettTimeLabel->setText(mettTime);
      mettTimeLabel->setAlignment(Qt::AlignCenter);
      mettTimeLabel->setFont(QFont("宋体",11));
      mettTimeLabel->setStyleSheet("border-image:url();background-color: transparent;");

      hbox3->addWidget(mettTimeLabel);

      QVBoxLayout* vbox = new QVBoxLayout();
      vbox->addLayout(hbox1);
      vbox->addLayout(hbox2);
      vbox->addLayout(hbox3);
      m_dockwidget->setLayout(vbox);

}

void MDetail::init(QString name, QString mettName, QString mettState, QString mettTime)
{
    this->appoinment_name = name;
    this->metting_name = mettName;
    this->metting_state = mettState;
    this->metting_time = mettTime;

    //this->setStyleSheet("background-color:rgb(63, 147, 168);color:white;border-radius:15px;");///media/root/F8FE9A09FE99BFF4/back.png
    this->setStyleSheet("border-image:url(:/image/Image/back.png);border-radius:25px;");
    QFont font("微软雅黑",12);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    QLabel* appoinment_label = new QLabel();
    appoinment_label->setFont(font);
    appoinment_label->setText(appoinment_name);
    appoinment_label->setStyleSheet("border-image:url();background-color: transparent;");
    QLabel* state_label = new QLabel();
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
    mettTimeLabel->setText(mettTime);
    mettTimeLabel->setAlignment(Qt::AlignCenter);
    mettTimeLabel->setFont(QFont("宋体",11));
    mettTimeLabel->setStyleSheet("border-image:url();background-color: transparent;");

    hbox3->addWidget(mettTimeLabel);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    m_dockwidget->setLayout(vbox);
    //vbox->setSpacing(0);
    //this->setStyleSheet("border-image:url(:/image/Image/infobackimage.png);border-radius:25px;");


}
