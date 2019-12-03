#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MDetail* mdetail = new MDetail("Korol","艾欧尼亚","即将开始","10:00  -  11:00");
    MDetail* mdetail1 = new MDetail("Korol","德玛西亚","即将开始","10:00  -  11:00");

    int count = w.vbox->count();
    qDebug()<<"count"<<count;
    w.vbox->insertWidget(--count,mdetail1);
    count = w.vbox->count();
    w.vbox->insertWidget(--count,mdetail);
     count = w.vbox->count();
//    w.vbox->insertStretch(3,220);
     MDetail* mdetail2 = new MDetail("Korol","德玛西亚","即将开始","10:00  -  11:00");
     w.vbox->insertWidget(--count,mdetail2);

//     MDetail* mdetail3 = new MDetail("Korol","德玛西亚","即将开始","10:00  -  11:00");
//     w.vbox->insertWidget(--count,mdetail3);
//     MDetail* mdetail4 = new MDetail("Korol","德玛西亚","即将开始","10:00  -  11:00");
//     w.vbox->insertWidget(--count,mdetail4);


//    MettingFrom metting("董事长办公室","智能工厂方案");
//    metting.show();
    return a.exec();
}
