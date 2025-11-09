// databaseworker.cpp - 数据库操作工作线程实现

#include "databaseworker.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

DatabaseWorker::DatabaseWorker(QObject *parent) : QObject(parent)
{}

DatabaseWorker::~DatabaseWorker()
{
    // 确保在对象销毁前断开数据库连接
    disconnectFromDatabase();
}

// connectToMysql - 连接到MySQL数据库的核心方法
// 返回值: 连接是否成功
bool DatabaseWorker::connectToMysql()
{
    QMutexLocker locker(&mutex);
    
    // 检查并清理现有连接
    if (QSqlDatabase::contains("mysqlConnection")) {
        db = QSqlDatabase::database("mysqlConnection");
        if (db.isOpen()) {
            emit connectionStatusChanged(true, "数据库连接已存在且可用");
            return true;
        }
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase("mysqlConnection");
    }
    
    // 创建并配置新连接
    db = QSqlDatabase::addDatabase("QMYSQL", "mysqlConnection");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");
    
    // 尝试打开连接
    if (!db.open()) {
        QString error = db.lastError().text();
        db = QSqlDatabase();
        if (QSqlDatabase::contains("mysqlConnection")) {
            QSqlDatabase::removeDatabase("mysqlConnection");
        }
        emit connectionStatusChanged(false, "连接失败: " + error);
        return false;
    }
    
    emit connectionStatusChanged(true, "数据库连接成功");
    return true;
}

void DatabaseWorker::storeGreenhouseData(double airTemp, double airHumidity, double oxygenContent, double soilTemp, double soilHumidity, double lightIntensity)
{
    QMutexLocker locker(&mutex);
    if (!db.isOpen()) {
        qDebug() << "[DatabaseWorker] 数据库连接未打开，无法存储数据";
        return;
    }

    QSqlQuery query(db);
    // 使用参数化查询插入数据到已创建的表中
    QString insertQuery = "INSERT INTO greenhouse_data (collect_time, air_temp, air_humidity, oxygen_content, soil_temp, soil_humidity, light_intensity) VALUES (?, ?, ?, ?, ?, ?, ?);";
    query.prepare(insertQuery);
    
    // 添加当前时间
    query.addBindValue(QDateTime::currentDateTime());
    // 添加环境参数
    query.addBindValue(airTemp);
    query.addBindValue(airHumidity);
    query.addBindValue(oxygenContent);
    query.addBindValue(soilTemp);
    query.addBindValue(soilHumidity);
    query.addBindValue(lightIntensity);

    if (query.exec()) {
        qDebug() << "[DatabaseWorker] 数据存储成功";
    } else {
        qDebug() << "[DatabaseWorker] 数据存储失败: " << query.lastError().text();
    }
}

void DatabaseWorker::connectToDatabase()
{
    connectToMysql();
}

void DatabaseWorker::disconnectFromDatabase()
{
    QMutexLocker locker(&mutex);
    
    // 清理数据库连接
    db = QSqlDatabase();
    
    if (QSqlDatabase::contains("mysqlConnection")) {
        // 安全关闭连接
        {   
            QSqlDatabase localDb = QSqlDatabase::database("mysqlConnection");
            if (localDb.isOpen()) localDb.close();
        }
        
        QSqlDatabase::removeDatabase("mysqlConnection");
        emit connectionStatusChanged(false, "数据库已断开连接");
    }
}

void DatabaseWorker::queryAllGreenhouseData()
{
    qDebug() << "[DatabaseWorker] 开始查询数据";
    
    QMutexLocker locker(&mutex);
    if (!db.isOpen()) {
        qDebug() << "[DatabaseWorker] 数据库连接未打开";
        emit queryResultsReady(false, QList<QVariantList>(), "数据库连接未打开");
        return;
    }
    
    QSqlQuery query(db);
    QString selectQuery = "SELECT entry_id, collect_time, air_temp, air_humidity, oxygen_content, soil_temp, soil_humidity, light_intensity FROM greenhouse_data ORDER BY collect_time DESC";
    
    if (!query.exec(selectQuery)) {
        qDebug() << "[DatabaseWorker] 查询失败: " << query.lastError().text();
        emit queryResultsReady(false, QList<QVariantList>(), "查询失败: " + query.lastError().text());
        return;
    }
    
    // 获取查询结果
    QList<QVariantList> results;
    int rowCount = 0;
    while (query.next()) {
        QVariantList row;
        row << query.value(0) << query.value(1) << query.value(2) << query.value(3) 
            << query.value(4) << query.value(5) << query.value(6) << query.value(7);
        results.append(row);
        rowCount++;
    }
    
    qDebug() << "[DatabaseWorker] 查询到" << rowCount << "条数据";
    emit queryResultsReady(true, results, QString("查询成功，共 %1 条数据").arg(rowCount));
}
