// mysql.cpp - MySQL数据库连接与管理界面实现
// 负责管理数据库连接界面和与DatabaseWorker的交互，
// 使用多线程方式处理数据库操作，确保UI界面的响应性。

#include "mysql.h"
#include "ui_mysql.h"
#include "databaseworker.h"
#include <QMessageBox>
#include <QDebug> // Qt消息框类
#include <QList>
#include <QVariantList>
#include <QTableWidgetItem>

Mysql::Mysql(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mysql)
{
    ui->setupUi(this);
    
    // 初始化数据库工作线程
    initDatabaseThread();
    
    // 连接信号和槽
    connect(dbWorker, &DatabaseWorker::connectionStatusChanged, this, &Mysql::on_connectionStatusChanged);
    connect(this, &Mysql::connectToDatabaseSignal, dbWorker, &DatabaseWorker::connectToDatabase);
    connect(dbWorker, &DatabaseWorker::queryResultsReady, this, &Mysql::on_queryResultsReady);
    
    // 应用启动时默认尝试连接数据库
    connectToDatabase();
}

// Mysql析构函数 - 清理资源
Mysql::~Mysql()
{
    // 清理数据库线程资源
    if (dbThread) {
        // 断开信号连接
        dbThread->disconnect(dbWorker);
        
        // 请求线程退出并等待
        dbThread->quit();
        dbThread->wait(3000); // 最多等待3秒
        
        // 释放线程对象
        delete dbThread;
        dbThread = nullptr;
    }
    
    // 确保dbWorker置空
    dbWorker = nullptr;
    
    // 释放UI对象
    delete ui;
}

// 初始化数据库工作线程
void Mysql::initDatabaseThread()
{
    dbThread = new QThread(this);
    dbWorker = new DatabaseWorker();
    
    // 将工作对象移动到工作线程
    dbWorker->moveToThread(dbThread);
    
    // 连接线程完成信号，确保线程结束时清理工作对象
    connect(dbThread, &QThread::finished, dbWorker, &QObject::deleteLater);
    
    // 启动工作线程
    dbThread->start();
}

// 请求数据库连接
void Mysql::connectToDatabase()
{
    emit connectToDatabaseSignal();
}

// 处理数据库连接状态变化
void Mysql::on_connectionStatusChanged(bool connected, const QString &message)
{
    if (ui->status) {
        ui->status->setText(message);
        ui->status->setStyleSheet(connected ? "color: green;" : "color: red;");
    }
}

// 处理查询结果
void Mysql::on_queryResultsReady(bool success, const QList<QVariantList> &results, const QString &message)
{
    qDebug() << "[Mysql] 查询结果: 成功=" << success;
    
    if (!success) {
        ui->status->setText("查询失败: " + message);
        return;
    }
    
    // 清空表格
    ui->datetable->clear();
    ui->datetable->setRowCount(0);
    ui->datetable->setColumnCount(8);
    
    // 设置表头
    QStringList headers;
    headers << "ID" << "采集时间" << "空气温度" << "空气湿度" 
            << "氧气含量" << "土壤温度" << "土壤湿度" << "光照强度";
    ui->datetable->setHorizontalHeaderLabels(headers);
    
    // 填充数据到表格
    for (int row = 0; row < results.size(); ++row) {
        ui->datetable->insertRow(row);
        const QVariantList &rowData = results.at(row);
        
        for (int col = 0; col < qMin(rowData.size(), 8); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col).toString());
            ui->datetable->setItem(row, col, item);
        }
    }
    
    // 调整列宽
    ui->datetable->resizeColumnsToContents();
    
    ui->status->setText(QString("已显示 %1 条数据").arg(results.size()));
}

// 处理窗口关闭事件 - 将窗口隐藏而不是真正关闭
void Mysql::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

// 公共方法：断开数据库连接
void Mysql::disconnectDatabase()
{
    if (dbWorker && dbThread && dbThread->isRunning()) {
        QMetaObject::invokeMethod(dbWorker, "disconnectFromDatabase", Qt::BlockingQueuedConnection);
    }
}

// 公共方法：存储温室环境数据到数据库
void Mysql::storeDataToDatabase(double airTemp, double airHumidity, double oxygenContent, double soilTemp, double soilHumidity, double lightIntensity)
{
    if (dbWorker && dbThread && dbThread->isRunning()) {
        // 使用BlockingQueuedConnection确保线程安全和操作完成
        bool success = QMetaObject::invokeMethod(dbWorker, "storeGreenhouseData", 
                                 Qt::BlockingQueuedConnection,
                                 Q_ARG(double, airTemp),
                                 Q_ARG(double, airHumidity),
                                 Q_ARG(double, oxygenContent),
                                 Q_ARG(double, soilTemp),
                                 Q_ARG(double, soilHumidity),
                                 Q_ARG(double, lightIntensity));
        
        if (!success) {
            qDebug() << "[Mysql] 调用数据库工作线程失败";
        }
    } else {
        qDebug() << "[Mysql] 数据库工作线程不可用";
    }
}

// 处理退出按钮点击事件
void Mysql::on_exit_clicked()
{
    this->hide();
}

void Mysql::on_showall_clicked()
{
    qDebug() << "[Mysql] showall按钮被点击";
    
    // 使用数据库工作线程查询数据
    if (dbWorker && dbThread && dbThread->isRunning()) {
        qDebug() << "[Mysql] 发送查询信号";
        
        // 使用信号槽机制调用数据库工作线程的查询方法
        QMetaObject::invokeMethod(dbWorker, "queryAllGreenhouseData", Qt::QueuedConnection);
        
        ui->status->setText("正在查询数据...");
    } else {
        qDebug() << "[Mysql] 数据库工作线程不可用";
        ui->status->setText("数据库工作线程不可用");
    }
}
