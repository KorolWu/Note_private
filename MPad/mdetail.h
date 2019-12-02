#ifndef MDETAIL_H
#define MDETAIL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDockWidget>
#include <QTimer>

class MDetail : public QWidget
{
    Q_OBJECT
public:
    explicit MDetail(QString name,QString mettName,QString mettState,QString mettTime,QWidget *parent = 0);
    void init(QString name,QString mettName,QString mettState,QString mettTime);

signals:

public slots:
private:
    QWidget* m_dockwidget;
    QString appoinment_name;
    QString metting_name;
    QString metting_state;
    QString metting_time;
};

#endif // MDETAIL_H
