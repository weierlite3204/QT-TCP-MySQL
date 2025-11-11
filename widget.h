#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QVBoxLayout>
#include <QFileDialog>
#include "qcustomplot.h"
#include "mytcpserver.h"
#include "msgworker.h"
#include "debugging.h"
#include "mysql.h"
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
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    unsigned int port=1210;//端口号
    MyTcpServer *msgserver=NULL;//tcp服务
    debugging *deb=NULL;//调试窗口
    Mysql *mysqldb=NULL;//MySQL窗口
    bool light = false;//开关灯
    bool water = false;//浇水

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

    const int maxDataPoints = 300; // 最大数据点数量

    // 初始化图表函数
    void initCharts();
    //界面初始化函数
    void init();
    // 简单的输入验证函数，检查是否为有效数字
    bool isValidNumber(const QString &input);
    // 检查所有报警阈值
    void checkAlarmThresholds(const SensorData &data);

private slots:
    void do_msgnewConnection(qintptr socket);//有客户端连接到消息服务器
    void showdata(SensorData);//把接收到的数据在ui界面中展示出来
    void portchange();//用户修改主机端口
    void on_lightbtn_clicked();//开关灯按钮点击事件
    void on_waterbtn_clicked();//浇水按钮点击事件
    void on_exitbtn_clicked();//系统关闭按钮点击事件
    void on_debugbtn_clicked();//调试按钮点击事件
    void on_mysqlbtn_clicked();//数据库按钮点击事件
    void on_exportbtn_clicked();//把数据导出为xlsx格式
    void onQueryResultsReady(bool success, const QList<QVariantList> &results, const QString &message); // 处理数据库查询结果的槽函数
    
private:
    // 发送命令到下位机并在调试界面显示
    void sendCommand(const QString &command);
    
protected:
    // 重写窗口关闭事件处理函数
    void closeEvent(QCloseEvent *event);
    
signals:
    void senddata(QByteArray data);
};
#endif // WIDGET_H
