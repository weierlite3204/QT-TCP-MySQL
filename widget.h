#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QVBoxLayout>
#include "qcustomplot.h"
#include "mytcpserver.h"
#include "msgworker.h"
#include "debugging.h"
#include "sensordata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    unsigned int port=1210;//端口号
    MyTcpServer *msgserver=NULL;//tcp服务
    debugging *deb=NULL;//调试窗口
    
    
    // 初始化图表函数
    void initCharts();

private slots:
    void do_msgnewConnection(qintptr socket);//有客户端连接到消息服务器
    void showdata(SensorData);//把接收到的数据在ui界面中展示出来
};
#endif // WIDGET_H
