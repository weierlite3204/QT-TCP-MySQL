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
    
    // 图表相关成员变量
    QCustomPlot *customPlot1; // 第一个图表（空气温度、湿度、氧气）
    QCustomPlot *customPlot2; // 第二个图表（土壤温度、湿度、光照）
    
    // 数据存储
    QVector<double> timeData1; // 第一个图表的时间数据
    QVector<double> tempData;  // 空气温度数据
    QVector<double> humidityData; // 空气湿度数据
    QVector<double> oxygenData; // 氧气浓度数据
    
    QVector<double> timeData2; // 第二个图表的时间数据
    QVector<double> soilTempData; // 土壤温度数据
    QVector<double> soilHumidityData; // 土壤湿度数据
    QVector<double> lightData; // 光照强度数据
    
    const int maxDataPoints = 20; // 最大数据点数量
    
    // 初始化图表函数
    void initCharts();

private slots:
    void do_msgnewConnection(qintptr socket);//有客户端连接到消息服务器
    void showdata(SensorData);//把接收到的数据在ui界面中展示出来
    void portchange();//用户修改主机端口
};
#endif // WIDGET_H
