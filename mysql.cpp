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

bool Mysql::chackconnect()
{
    if(dbWorker && dbThread && dbThread->isRunning())
    {
        return true;
    }else
    {
        return false;
    }
}

DatabaseWorker* Mysql::getdataworker()
{
    return dbWorker;
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
            QString displayText;
            
            // 如果是采集时间列（第2列，索引1），格式化时间
            if (col == 1 && rowData.at(col).canConvert<QDateTime>()) {
                QDateTime dateTime = rowData.at(col).toDateTime();
                // 确保使用本地时间并格式化
                displayText = dateTime.toLocalTime().toString("yyyy-MM-dd HH:mm:ss");
            } else {
                displayText = rowData.at(col).toString();
            }
            
            QTableWidgetItem *item = new QTableWidgetItem(displayText);
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
    if (chackconnect()) {
        QMetaObject::invokeMethod(dbWorker, "disconnectFromDatabase", Qt::BlockingQueuedConnection);
    }
}

// 公共方法：存储温室环境数据到数据库
void Mysql::storeDataToDatabase(double airTemp, double airHumidity, double oxygenContent, double soilTemp, double soilHumidity, double lightIntensity)
{
    if (chackconnect()) {
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
//显示所有数据
void Mysql::on_showall_clicked()
{
    qDebug() << "[Mysql] showall按钮被点击";
    
    // 使用数据库工作线程查询数据
    if (chackconnect()) {
        qDebug() << "[Mysql] 发送查询信号";
        
        // 使用信号槽机制调用数据库工作线程的查询方法
        QMetaObject::invokeMethod(dbWorker, "queryAllGreenhouseData", Qt::QueuedConnection);
        
        ui->status->setText("正在查询数据...");
    } else {
        qDebug() << "[Mysql] 数据库工作线程不可用";
        ui->status->setText("数据库工作线程不可用");
    }
}
//清空表格中的数据
void Mysql::on_deleteall_clicked()
{
    qDebug() << "[Mysql] deleteall按钮被点击";
    // 清空表格
    ui->datetable->clear();
    ui->datetable->setRowCount(0);
    ui->datetable->setColumnCount(8);
    
    QStringList headers;
    headers << "ID" << "采集时间" << "空气温度" << "空气湿度" 
            << "氧气含量" << "土壤温度" << "土壤湿度" << "光照强度";
    ui->datetable->setHorizontalHeaderLabels(headers);
    
    ui->status->setText("已清空数据");
}

// 查询按钮点击事件处理
void Mysql::on_inquire_clicked()
{
    qDebug() << "[Mysql] 时间查询按钮被点击";
    
    // 获取开始和结束时间
    QDateTime startTime = ui->dateTimeON->dateTime();
    QDateTime endTime = ui->dateTimeOFF->dateTime();
    
    // 验证时间范围
    if (startTime > endTime) {
        ui->status->setText("错误：开始时间不能晚于结束时间");
        ui->status->setStyleSheet("color: red;");
        return;
    }
    
    // 使用数据库工作线程进行时间范围查询
    if (chackconnect()) {
        ui->status->setText("正在查询数据...");
        
        // 使用信号槽机制调用数据库工作线程的查询方法
        QMetaObject::invokeMethod(dbWorker, "queryGreenhouseDataByTimeRange", 
                                 Qt::QueuedConnection,
                                 Q_ARG(QDateTime, startTime),
                                 Q_ARG(QDateTime, endTime));
    } else {
        ui->status->setText("数据库工作线程不可用");
        ui->status->setStyleSheet("color: red;");
    }
}

// 现在时间按钮点击事件处理
void Mysql::on_nowtime_clicked()
{
    qDebug() << "[Mysql] 现在时间按钮被点击";
    
    // 设置结束时间为当前时间
    ui->dateTimeOFF->setDateTime(QDateTime::currentDateTime());
}

// 最近一天查询按钮点击事件处理
void Mysql::on_oneday_clicked()
{
    qDebug() << "[Mysql] 最近一天按钮被点击";
    
    QDateTime endTime = QDateTime::currentDateTime();
    QDateTime startTime = endTime.addDays(-1);
    
    ui->dateTimeON->setDateTime(startTime);
    ui->dateTimeOFF->setDateTime(endTime);
    
    // 自动触发查询
    on_inquire_clicked();
}

// 最近三天查询按钮点击事件处理
void Mysql::on_threeday_clicked()
{
    qDebug() << "[Mysql] 最近三天按钮被点击";
    
    QDateTime endTime = QDateTime::currentDateTime();
    QDateTime startTime = endTime.addDays(-3);
    
    ui->dateTimeON->setDateTime(startTime);
    ui->dateTimeOFF->setDateTime(endTime);
    
    // 自动触发查询
    on_inquire_clicked();
}

// 最近一周查询按钮点击事件处理
void Mysql::on_aweek_clicked()
{
    qDebug() << "[Mysql] 最近一周按钮被点击";
    
    QDateTime endTime = QDateTime::currentDateTime();
    QDateTime startTime = endTime.addDays(-7);
    
    ui->dateTimeON->setDateTime(startTime);
    ui->dateTimeOFF->setDateTime(endTime);
    
    // 自动触发查询
    on_inquire_clicked();
}

// 值查询按钮点击事件处理
void Mysql::on_dateinquire_clicked()
{
    qDebug() << "[Mysql] 值查询按钮被点击";
    
    // 获取用户选择的属性名称
    QString attributeName = ui->comboBox->currentText();
    
    // 获取最小值和最大值
    QString minValueStr = ui->min->text();
    QString maxValueStr = ui->max->text();
    
    // 验证输入
    bool minOk, maxOk;
    double minValue = minValueStr.toDouble(&minOk);
    double maxValue = maxValueStr.toDouble(&maxOk);
    
    if (!minOk || !maxOk) {
        ui->status->setText("错误：请输入有效的数值");
        ui->status->setStyleSheet("color: red;");
        return;
    }
    
    if (minValue > maxValue) {
        ui->status->setText("错误：最小值不能大于最大值");
        ui->status->setStyleSheet("color: red;");
        return;
    }
    
    // 使用数据库工作线程进行值范围查询
    if (chackconnect()) {
        ui->status->setText(QString("正在查询%1在%2到%3之间的数据...")
                                   .arg(attributeName)
                                   .arg(minValue)
                                   .arg(maxValue));
        
        // 使用信号槽机制调用数据库工作线程的查询方法
        QMetaObject::invokeMethod(dbWorker, "queryGreenhouseDataByValueRange", 
                                 Qt::QueuedConnection,
                                 Q_ARG(QString, attributeName),
                                 Q_ARG(double, minValue),
                                 Q_ARG(double, maxValue));
    } else {
        ui->status->setText("数据库工作线程不可用");
        ui->status->setStyleSheet("color: red;");
    }
}
