#ifndef MDETAIL_H
#define MDETAIL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDockWidget>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
class MDetail : public QWidget
{
    Q_OBJECT
public:
    explicit MDetail(QString name,QString mettName,QString mettState,QString mettTime,QWidget *parent = 0);

signals:

public slots:
private:
    QWidget* m_dockwidget;
    QString appoinment_name;
    QString metting_name;
    QString metting_state;
    QString metting_time;
    QLabel* state_label;
    void check_status();
    QTimer* timer;
    bool star_signal = true;
   // bool end_signal = true;
signals:
    void start_signal(QString appoinment_name,QString metting_name,QDateTime date_time_end);
};

#endif // MDETAIL_H
