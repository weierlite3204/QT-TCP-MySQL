#ifndef MYSQL_H
#define MYSQL_H

#include <QWidget>   // Qt窗口基类
#include <QThread>     // Qt线程类，用于多线程操作
#include <QCloseEvent> // Qt关闭事件类
#include "databaseworker.h" // 数据库工作线程类

namespace Ui {
// Ui命名空间中的Mysql类 - 由Qt的uic工具自动生成，包含UI界面的定义
class Mysql;
}

// Mysql - MySQL数据库连接管理窗口类
// 负责创建用户界面，管理数据库工作线程，处理数据库连接状态显示，
// 以及响应用户交互操作。
class Mysql : public QWidget
{
    Q_OBJECT // Qt元对象系统宏，启用信号槽机制

public:

    explicit Mysql(QWidget *parent = nullptr);
    
    //析构函数负责清理资源，包括数据库线程和UI组件
    ~Mysql();
    
    //重写QWidget的虚函数，处理窗口关闭事件
    void closeEvent(QCloseEvent *event) override;
    
    //断开数据库连接
    // 供主窗口在关闭时调用，确保数据库连接被正确断开
    void disconnectDatabase();
    
    //存储温室环境数据到数据库
    // 供主窗口调用，将传感器数据存储到数据库中
    void storeDataToDatabase(double airTemp, double airHumidity, double oxygenContent, double soilTemp, double soilHumidity, double lightIntensity);

    //检查数据库连接
    bool chackconnect();

    //获取数据库工作对象
    DatabaseWorker* getdataworker();

signals:
    // 连接数据库信号 - 触发数据库工作线程中的连接操作
    void connectToDatabaseSignal();
    // 断开数据库连接信号 - 触发数据库工作线程中的断开操作
    void disconnectFromDatabase();



private:
    Ui::Mysql *ui;
    
    //数据库工作对象，在独立线程中执行数据库操作
    DatabaseWorker *dbWorker;
    
    //执行数据库操作的线程
    QThread *dbThread;
    
    //初始化数据库工作线程
    void initDatabaseThread();
    
    //请求数据库连接
    void connectToDatabase();

private slots:
    // on_connectionStatusChanged - 处理数据库连接状态变化的槽函数
    // connected: 连接是否成功
    // message: 状态描述消息
    void on_connectionStatusChanged(bool connected, const QString &message);
    
    // 处理查询结果
    void on_queryResultsReady(bool success, const QList<QVariantList> &results, const QString &message);
    
    void on_exit_clicked();//处理退出按钮点击事件的槽函数
    void on_showall_clicked();//显示所有数据按钮
    void on_deleteall_clicked();//将表格里面的数据清空
    void on_inquire_clicked();//查询按钮点击事件处理
    void on_nowtime_clicked();//现在时间按钮点击事件处理
    void on_oneday_clicked();//最近一天查询按钮点击事件处理
    void on_threeday_clicked();//最近三天查询按钮点击事件处理
    void on_aweek_clicked();//最近一周查询按钮点击事件处理
    void on_dateinquire_clicked();//值查询按钮点击事件处理
};

#endif // MYSQL_H
