#ifndef METTINGFROM_H
#define METTINGFROM_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QFont>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>

class MettingFrom : public QWidget
{
    Q_OBJECT
public:
    explicit MettingFrom(QString appoinment_name,QString topic_name,QDateTime end_time,QWidget *parent = 0);

signals:
    void weakup_mainwindow();
public slots:
private:
    const int PAD_X = 640;
    const int PAD_Y = 420;
    QLabel* log_lab;
    QLabel* appoinment_name_lab;
    QLabel* topic_lab;
    QTimer* timer;

    QLabel* time_d_label;
    QLabel* time_s_label;
    QDateTime m_end_time;
    //QTimer* timer;
    uint m_end;
    void weakupMainwindow();
    void update_time();
};

#endif // METTINGFROM_H
