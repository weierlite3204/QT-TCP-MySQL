#include "widget.h"
#include "ui_widget.h"
#include <QNetworkInterface>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
// 引入QXlsx库
#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxformat.h"
#include "QXlsx/header/xlsxchart.h"
#include "QXlsx/header/xlsxcellrange.h"
using namespace QXlsx;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

//有客户端连接到消息服务器
void Widget::do_msgnewConnection(qintptr socket)//处理客户端msgsocket的连接
{
    //传的是socket描述符，根据socket描述符，可以初始化TcpSocket
    MsgWorker *worker=new MsgWorker(socket);//初始化客户端线程
    worker->start();//因为继承了QThread，这里启动线程，启动run（）函数
    
    // 连接成功，更新连接状态标签为"已连接"
    ui->connectlab->setText("已连接");
    
    // 连接worker的deletethread信号到线程安全销毁的lambda
    connect(worker,&MsgWorker::deletethread,this,[this, worker](){
        worker->wait();// 主线程等待子线程安全退出
        worker->deleteLater();// 安全释放线程对象
        // 连接断开，更新连接状态标签为"未连接"
        ui->connectlab->setText("未连接");
        qDebug()<<"成功删除通信线程"<<'\n';
    });
    
    // 连接worker的rawdata信号到调试窗口的showdata槽函数
    connect(worker, &MsgWorker::rawdata, deb, &debugging::showdata);//发送信号，让原始数据显示在调试界面
    connect(deb,&debugging::senddata,worker,&MsgWorker::sendstrdata);//接收到发送信号，发送数据给下位机
    connect(worker,&MsgWorker::showsensordata,this,&Widget::showdata);//发送信号，让接收到的数据显示在界面上
}

//初始化图表
void Widget::initCharts()
{
    // 清除frame的布局（如果有）
    QLayout *oldLayout1 = ui->charFrame1->layout();
    if (oldLayout1) {
        delete oldLayout1;
    }
    
    QLayout *oldLayout2 = ui->charFrame2->layout();
    if (oldLayout2) {
        delete oldLayout2;
    }
    
    // ===== 初始化第一个图表（空气温度、湿度、氧气） =====
    customPlot1 = new QCustomPlot(ui->charFrame1);
    
    // 添加三条曲线
    customPlot1->addGraph(); // 空气温度
    customPlot1->addGraph(); // 空气湿度
    customPlot1->addGraph(); // 氧气浓度
    
    // 设置曲线颜色和名称
    customPlot1->graph(0)->setPen(QPen(Qt::blue));
    customPlot1->graph(0)->setName("空气温度");
    customPlot1->graph(1)->setPen(QPen(Qt::green));
    customPlot1->graph(1)->setName("空气湿度");
    customPlot1->graph(2)->setPen(QPen(Qt::red));
    customPlot1->graph(2)->setName("氧气含量");
    
    // 设置坐标轴
    customPlot1->xAxis->setLabel("time(see)");
    customPlot1->yAxis->setLabel("");
    customPlot1->yAxis->setRange(0, 100);
    
    // 设置X轴为时间轴
    QSharedPointer<QCPAxisTickerDateTime> timeTicker1(new QCPAxisTickerDateTime);
    timeTicker1->setDateTimeFormat("HH:mm:ss");
    timeTicker1->setDateTimeSpec(Qt::LocalTime);
    customPlot1->xAxis->setTicker(timeTicker1);
    
    // 启用图例
    customPlot1->legend->setVisible(true);
    
    // 设置抗锯齿
    customPlot1->setAntialiasedElements(QCP::aeAll);
    
    // 将图表添加到frame1
    QVBoxLayout *layout1 = new QVBoxLayout(ui->charFrame1);
    layout1->setContentsMargins(0, 0, 0, 0);
    layout1->addWidget(customPlot1);
    
    // ===== 初始化第二个图表（土壤温度、湿度、光照） =====
    customPlot2 = new QCustomPlot(ui->charFrame2);
    
    // 添加三条曲线
    customPlot2->addGraph(); // 土壤温度
    customPlot2->addGraph(); // 土壤湿度
    customPlot2->addGraph(); // 光照强度
    
    // 设置曲线颜色和名称
    customPlot2->graph(0)->setPen(QPen(Qt::blue));
    customPlot2->graph(0)->setName("土壤温度");
    customPlot2->graph(1)->setPen(QPen(Qt::green));
    customPlot2->graph(1)->setName("土壤湿度");
    customPlot2->graph(2)->setPen(QPen(Qt::yellow));
    customPlot2->graph(2)->setName("光照");
    
    // 设置坐标轴
    customPlot2->xAxis->setLabel("time(see)");
    customPlot2->yAxis->setLabel("");
    customPlot2->yAxis->setRange(0, 100);
    
    // 设置X轴为时间轴
    QSharedPointer<QCPAxisTickerDateTime> timeTicker2(new QCPAxisTickerDateTime);
    timeTicker2->setDateTimeFormat("HH:mm:ss");
    timeTicker2->setDateTimeSpec(Qt::LocalTime);
    customPlot2->xAxis->setTicker(timeTicker2);
    
    // 启用图例
    customPlot2->legend->setVisible(true);
    
    // 设置抗锯齿
    customPlot2->setAntialiasedElements(QCP::aeAll);
    
    // 将图表添加到frame2
    QVBoxLayout *layout2 = new QVBoxLayout(ui->charFrame2);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->addWidget(customPlot2);
}

void Widget::init()
{
    // 创建调试窗口但默认隐藏
    deb = new debugging();
    deb->setAttribute(Qt::WA_DeleteOnClose, false); // 关闭时不自动删除
    
    // 创建MySQL窗口并显示以确保数据库连接建立
    mysqldb = new Mysql();
    mysqldb->setAttribute(Qt::WA_DeleteOnClose, false); // 关闭时不自动删除
    
    msgserver=new MyTcpServer(this);//创建Tcp服务器对象
    //QHostAddress::Any //双栈任意地址。以这种地址绑定的套接字将同时监听两个端口。 一。
    msgserver->listen(QHostAddress::Any,port);//监听端口
    // 连接服务器的newDescriptor信号到Widget的do_msgnewConnection槽函数
    connect(msgserver, &MyTcpServer::newDescriptor, this, &Widget::do_msgnewConnection);

    // 获取并显示本地IPv4地址，便于复制连接
    QString ipAddress = "";
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 寻找第一个非环回IPv4地址
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到非环回地址，使用环回地址
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    // 设置iplineEdit为可复制的IP地址
    ui->iplineEdit->setText(ipAddress);
    ui->iplineEdit->setReadOnly(true);
    // 初始化图表
    initCharts();

    // 设置raySlider的范围和初始值
    // 滑动条范围设为0-1950，用于映射到50-2000 μmol/m²
    ui->raySlider->setRange(0, 1950);
    ui->raySlider->setValue(0); // 默认在最小值位置

    // 初始化raylabel显示
    ui->raylabel->setText("50 μmol/m²");

    //当端口行编辑完成之后，更改服务器监听的端口
    connect(ui->portlineEdit,&QLineEdit::editingFinished,this,&Widget::portchange);
    // 连接滑动条值变化信号到lambda函数，更新raylabel显示
    connect(ui->raySlider, &QSlider::valueChanged, [this](int value) {
        // 将0-1950映射到50-2000 μmol/m²
        int mappedValue = 50 + value;
        QString rayText = QString::number(mappedValue) + " μmol/m²";
        ui->raylabel->setText(rayText);
        
        // 如果灯是开着的，同步更新lightbtn的文本
        if (light) {
            ui->lightbtn->setText(rayText);
        }
    });
}

// 简单的输入验证函数，检查报警阈值是否为有效数字
bool Widget::isValidNumber(const QString &input)
{
    if (input.isEmpty()) {
        return false;
    }
    
    // 移除空格并检查是否全为数字和小数点
    QString trimmed = input.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    
    // 检查每个字符是否为数字或小数点（仅允许一个小数点）
    int dotCount = 0;
    for (int i = 0; i < trimmed.length(); ++i) {
        QChar c = trimmed.at(i);
        if (c == '.') {
            dotCount++;
            if (dotCount > 1) {
                return false;
            }
        } else if (!c.isDigit()) {
            return false;
        }
    }
    
    // 小数点不能在开头或结尾
    if (trimmed.startsWith('.') || trimmed.endsWith('.')) {
        return false;
    }
    
    return true;
}

// 检查所有报警阈值
void Widget::checkAlarmThresholds(const SensorData &data)
{
    // 空气温度阈值检查
    if (ui->airtemcb->isChecked()) {
        QString input = ui->airtemLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.atemp > threshold) {
                QMessageBox::warning(this, "警报", "空气温度超过设定阈值！");
            }
        }
    }
    
    // 空气相对湿度阈值检查
    if (ui->airwatercb->isChecked()) {
        QString input = ui->airwaterLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.ahumi > threshold) {
                QMessageBox::warning(this, "警报", "空气相对湿度超过设定阈值！");
            }
        }
    }
    
    // 氧气浓度阈值检查
    if (ui->oxygencb->isChecked()) {
        QString input = ui->oxygenLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.oxygen > threshold) {
                QMessageBox::warning(this, "警报", "氧气浓度超过设定阈值！");
            }
        }
    }
    
    // 土壤温度阈值检查
    if (ui->soiltemcb->isChecked()) {
        QString input = ui->soiltemLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.stemp > threshold) {
                QMessageBox::warning(this, "警报", "土壤温度超过设定阈值！");
            }
        }
    }
    
    // 土壤含水量阈值检查
    if (ui->soilwatercb->isChecked()) {
        QString input = ui->soilwaterLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.shumi2 > threshold) {
                QMessageBox::warning(this, "警报", "土壤含水量超过设定阈值！");
            }
        }
    }
    
    // 光照强度阈值检查
    if (ui->raycb->isChecked()) {
        QString input = ui->rayLE->text();
        if (isValidNumber(input)) {
            double threshold = input.toDouble();
            if (data.light > threshold) {
                QMessageBox::warning(this, "警报", "光照强度超过设定阈值！");
            }
        }
    }
}

//接收到数据之后，将数据展示到主界面中
void Widget::showdata(SensorData data)
{
    // 更新主界面数据监控部分的各个控件
    ui->airtem->setText(QString::number(data.atemp, 'f', 1) + "°C");    // 空气温度
    ui->airwater->setText(QString::number(data.ahumi, 'f', 1) + "%");  // 空气相对湿度
    ui->oxygen->setText(QString::number(data.oxygen, 'f', 1) + "%");   // 氧气浓度
    ui->soiltem->setText(QString::number(data.stemp, 'f', 1) + "°C");   // 土壤温度
    ui->soilwater->setText(QString::number(data.shumi2, 'f', 1) + "%"); // 土壤含水量
    ui->ray->setText(QString::number(data.light, 'f', 1) + "%");       // 光照强度
    
    // 调用报警阈值检查函数
    checkAlarmThresholds(data);
    
    // 存储数据到数据库
    qDebug() << "[Widget] 准备存储数据到数据库";
    if (mysqldb) {
        qDebug() << "[Widget] mysqldb对象存在，调用storeDataToDatabase方法";
        mysqldb->storeDataToDatabase(data.atemp, data.ahumi, data.oxygen, data.stemp, data.shumi2, data.light);
        qDebug() << "[Widget] storeDataToDatabase方法调用完成";
    } else {
        qDebug() << "[Widget] mysqldb对象不存在，无法存储数据";
    }
    
    // 获取当前时间
    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    
    // 添加数据到第一个图表
    timeData1.append(currentTime);
    tempData.append(data.atemp);
    humidityData.append(data.ahumi);
    oxygenData.append(data.oxygen);
    
    // 添加数据到第二个图表
    timeData2.append(currentTime);
    soilTempData.append(data.stemp);
    soilHumidityData.append(data.shumi2);
    lightData.append(data.light);
    
    // 限制数据点数量
    if (timeData1.size() > maxDataPoints) {
        timeData1.removeFirst();
        tempData.removeFirst();
        humidityData.removeFirst();
        oxygenData.removeFirst();
    }
    
    if (timeData2.size() > maxDataPoints) {
        timeData2.removeFirst();
        soilTempData.removeFirst();
        soilHumidityData.removeFirst();
        lightData.removeFirst();
    }
    
    // 更新曲线数据
    customPlot1->graph(0)->setData(timeData1, tempData);
    customPlot1->graph(1)->setData(timeData1, humidityData);
    customPlot1->graph(2)->setData(timeData1, oxygenData);
    
    customPlot2->graph(0)->setData(timeData2, soilTempData);
    customPlot2->graph(1)->setData(timeData2, soilHumidityData);
    customPlot2->graph(2)->setData(timeData2, lightData);
    
    // 更新X轴范围
    if (!timeData1.isEmpty()) {
        double minTime = timeData1.first() - 1;
        double maxTime = timeData1.last() + 1;
        customPlot1->xAxis->setRange(minTime, maxTime);
    }
    
    if (!timeData2.isEmpty()) {
        double minTime = timeData2.first() - 1;
        double maxTime = timeData2.last() + 1;
        customPlot2->xAxis->setRange(minTime, maxTime);
    }
    
    // 确保坐标轴标签可见
    customPlot1->axisRect()->setupFullAxesBox();
    customPlot2->axisRect()->setupFullAxesBox();
    
    // 重绘图表
    customPlot1->replot(QCustomPlot::rpQueuedReplot);
    customPlot2->replot(QCustomPlot::rpQueuedReplot);
}

//端口号改变
void Widget::portchange()
{
    // 获取用户输入的端口号
    QString portText = ui->portlineEdit->text();
    bool ok;//用于指示字符串到无符号整数的转换是否成功
    unsigned int newPort = portText.toUInt(&ok);//如果转换失败，ok = 0
    
    // 验证端口是否在有效范围内（1-65535）
    if (!ok || newPort < 1 || newPort > 65535) {
        // 端口无效，显示错误信息
        ui->portlineEdit->setText("端口输入有误");
        // 设置样式，让错误提示更明显
        ui->portlineEdit->setStyleSheet("color: red; background-color: #FFE0E0;");
        
        // 使用定时器，一段时间后恢复原始端口显示
        QTimer::singleShot(2000, [=]() {
            ui->portlineEdit->setText(QString::number(port));
            ui->portlineEdit->setStyleSheet("");
        });
        return;
    }
    
    // 端口有效，恢复正常样式
    ui->portlineEdit->setStyleSheet("");
    
    // 如果端口号没有变化，不需要重新监听
    if (newPort == port) {
        return;
    }
    
    // 停止当前的服务器监听
    if (msgserver && msgserver->isListening()) {
        msgserver->close();
    }
    
    // 更新端口号
    port = newPort;
    
    // 重新开始监听新端口
    if (msgserver) {
        msgserver->listen(QHostAddress::Any, port);
    }
}

// 发送命令到下位机并在调试界面显示
void Widget::sendCommand(const QString &command)
{
    QByteArray commandData = command.toUtf8();
    emit senddata(commandData);
        // 在调试界面显示发送的消息
        if (deb) {
            deb->showdata("发送: " + command);
        }
}

void Widget::on_lightbtn_clicked()
{
    // 切换灯的状态
    light = !light;
    
    if (light) {
        // 开灯状态：按钮文本显示当前光照强度
        QString rayLabelText = ui->raylabel->text();
        ui->lightbtn->setText(rayLabelText);
        
        // 发送开灯指令到下位机
        sendCommand("lightON");
    } else {
        // 关灯状态：按钮文本显示"开灯"
        ui->lightbtn->setText("开灯");
        
        // 发送关灯指令到下位机
        sendCommand("lightOFF");
    }
}
//浇水按钮按下
void Widget::on_waterbtn_clicked()
{
    // 如果当前是关闭状态，点击要开始浇水
    if (!water) {
        // 获取waterspinBox中设置的秒数
        int seconds = ui->waterspinBox->value();
        
        // 开始浇水
        water = true;
        ui->waterbtn->setText("关水");
        
        // 发送浇水指令到下位机
        sendCommand("waterON");
        
        // 只有当浇水时间大于0秒时，才设置定时器自动关水
        if (seconds > 0) {
            QTimer::singleShot(seconds * 1000, this, [this]() {
            if (water) { // 只有在仍然浇水状态时才执行自动关水
                water = false;
                ui->waterbtn->setText("浇水");
                
                // 发送关水指令到下位机
                sendCommand("waterOFF");
            }
        });
        }
    } else {
        // 停止浇水
        water = false;
        ui->waterbtn->setText("浇水");
        
        // 发送关水指令到下位机
        sendCommand("waterOFF");
    }
}
//退出系统按钮按下
// 窗口关闭事件处理函数
void Widget::closeEvent(QCloseEvent *event)
{
    // 执行与退出按钮相同的关闭逻辑
    // 如果正在浇水，立即关水
    if (water) {
        water = false;
        ui->waterbtn->setText("浇水");
        
        // 发送关水指令到下位机
        sendCommand("waterOFF");
    }
    
    // 关闭debugging界面（如果存在）
    if (deb) {
        deb->close();
        delete deb;
        deb = nullptr;
    }
    
    // 关闭mysql界面（如果存在）
    if (mysqldb) {
        mysqldb->close();
        delete mysqldb;
        mysqldb = nullptr;
    }
    
    // 退出整个系统
    QApplication::quit();
    
    // 接受关闭事件
    event->accept();
}

void Widget::on_exitbtn_clicked()
{
    // 调用窗口关闭事件处理函数
    close();
}

//调试按钮按下
void Widget::on_debugbtn_clicked()
{
    if (!deb) {
        // 如果窗口不存在，创建新窗口
        deb = new debugging();
        deb->setAttribute(Qt::WA_DeleteOnClose, false); // 关闭时不自动删除
        deb->show();
    } else if (deb->isMinimized()) {
        // 如果窗口最小化，恢复正常窗口
        deb->showNormal();
        deb->raise();
        deb->activateWindow();
    } else if (!deb->isVisible()) {
        // 如果窗口隐藏，显示窗口（使用showNormal确保不是最大化状态）
        deb->showNormal();
        deb->raise();
        deb->activateWindow();
    } else {
        // 如果窗口已经显示，将其置于前台
        deb->raise();
        deb->activateWindow();
    }
}

//数据库按钮按下
void Widget::on_mysqlbtn_clicked()
{
    if (!mysqldb) {
        // 如果窗口不存在，创建新窗口
        mysqldb = new Mysql();
        mysqldb->setAttribute(Qt::WA_DeleteOnClose, false); // 关闭时不自动删除
        mysqldb->show();
    } else if (mysqldb->isMinimized()) {
        // 如果窗口最小化，恢复正常窗口
        mysqldb->showNormal();
        mysqldb->raise();
        mysqldb->activateWindow();
    } else if (!mysqldb->isVisible()) {
        // 如果窗口隐藏，显示窗口（使用showNormal确保不是最大化状态）
        mysqldb->showNormal();
        mysqldb->raise();
        mysqldb->activateWindow();
    } else {
        // 如果窗口已经显示，将其置于前台
        mysqldb->raise();
        mysqldb->activateWindow();
    }
}

void Widget::on_exportbtn_clicked() // 导出按钮点击事件处理函数
{
    qDebug() << "[导出数据] 开始从数据库导出图表数据到Excel文件"; // 输出调试信息，指示导出开始
    
    
    // 确保数据库工作线程正在运行
    if (mysqldb->chackconnect()) {
        // 连接数据库查询结果信号到当前类的槽函数
        connect(mysqldb->getdataworker(), &DatabaseWorker::queryResultsReady, this, &Widget::onQueryResultsReady);
        
        qDebug() << "[导出数据] 请求查询所有数据库数据"; // 输出调试信息
        
        // 使用信号槽机制调用数据库工作线程的查询所有数据方法
        QMetaObject::invokeMethod(mysqldb->getdataworker(), "queryAllGreenhouseData", Qt::QueuedConnection);
        
    } else {
        qDebug() << "[导出数据] 数据库工作线程不可用"; // 输出调试信息
        QMessageBox::warning(this, "导出失败", "数据库工作线程不可用，请先连接数据库");
    }
}

void Widget::onQueryResultsReady(bool success, const QList<QVariantList> &results, const QString &message)
{
    qDebug() << "[导出数据] 收到数据库查询结果: 成功=" << success << ", 记录数=" << results.size(); // 输出调试信息

    // 断开信号连接，避免重复处理
    disconnect(mysqldb->getdataworker(), &DatabaseWorker::queryResultsReady, this, &Widget::onQueryResultsReady);
    
    
    if (!success || results.isEmpty()) {
        QMessageBox::warning(this, "导出失败", "查询数据失败或没有数据可供导出");
        return;
    }
    
    // 创建一个新的Excel文档对象
    Document xlsx;
    
    // 创建表头格式对象
    Format headerFormat;
    headerFormat.setFontBold(true); // 设置表头字体为粗体
    headerFormat.setHorizontalAlignment(Format::AlignHCenter); // 设置表头水平居中对齐
    headerFormat.setVerticalAlignment(Format::AlignVCenter); // 设置表头垂直居中对齐
    headerFormat.setBorderStyle(Format::BorderThin); // 设置表头边框为细边框
    
    // 创建数据单元格格式对象
    Format dataFormat;
    dataFormat.setBorderStyle(Format::BorderThin); // 设置数据单元格边框为细边框
    
    // 首先添加空气参数工作表
    xlsx.addSheet("空气参数");
    xlsx.selectSheet("空气参数");
    
    // 写入表头
    xlsx.write("A1", "时间", headerFormat);
    xlsx.write("B1", "空气温度(°C)", headerFormat);
    xlsx.write("C1", "空气湿度(%)", headerFormat);
    xlsx.write("D1", "氧气浓度(%)", headerFormat);
    
    int airDataRowCount = 0; // 计数器，用于记录实际写入的空气参数数据行数
    
    // 遍历查询结果，写入空气参数数据
    for (int i = 0; i < results.size(); ++i) {
        const QVariantList &row = results.at(i);
        if (row.size() >= 5) { // 确保有足够的数据列
            int excelRow = i + 2; // Excel行号从2开始
            
            // 从数据库结果中提取数据
            QString timeString = row.at(1).toDateTime().toString("yyyy-MM-dd HH:mm:ss"); // 时间
            double airTemp = row.at(2).toDouble(); // 空气温度
            double airHumidity = row.at(3).toDouble(); // 空气湿度
            double oxygenContent = row.at(4).toDouble(); // 氧气浓度
            
            // 写入Excel
            xlsx.write(excelRow, 1, timeString, dataFormat);
            xlsx.write(excelRow, 2, airTemp, dataFormat);
            xlsx.write(excelRow, 3, airHumidity, dataFormat);
            xlsx.write(excelRow, 4, oxygenContent, dataFormat);
            
            airDataRowCount++;
        }
    }
    
    // 如果有数据，创建空气参数图表
    if (airDataRowCount > 0) {
        int chartRow = airDataRowCount + 3; // 图表位置在数据下方3行
        Chart *airChart = xlsx.insertChart(chartRow, 1, QSize(800, 400)); // 插入图表
        
        airChart->setChartType(Chart::CT_LineChart); // 设置为折线图
        airChart->setChartTitle("空气参数变化趋势"); // 设置图表标题
        
        // 添加温度数据系列（使用时间作为X轴）
        CellRange tempRange("A2:B" + QString::number(airDataRowCount + 1));
        airChart->addSeries(tempRange, nullptr, false, true);
        
        // 添加湿度数据系列
        CellRange humidityRange("A2:A" + QString::number(airDataRowCount + 1) + ",C2:C" + QString::number(airDataRowCount + 1));
        airChart->addSeries(humidityRange, nullptr, false, true);
        
        // 添加氧气浓度数据系列
        CellRange oxygenRange("A2:A" + QString::number(airDataRowCount + 1) + ",D2:D" + QString::number(airDataRowCount + 1));
        airChart->addSeries(oxygenRange, nullptr, false, true);
        
        // 设置图表属性
        airChart->setChartLegend(Chart::Top, false); // 图例在顶部
        airChart->setAxisTitle(Chart::Bottom, "时间"); // X轴标题
        airChart->setAxisTitle(Chart::Left, "数值"); // Y轴标题
    }
    
    // 接下来添加土壤参数工作表
    xlsx.addSheet("土壤参数");
    xlsx.selectSheet("土壤参数");
    
    // 写入表头
    xlsx.write("A1", "时间", headerFormat);
    xlsx.write("B1", "土壤温度(°C)", headerFormat);
    xlsx.write("C1", "土壤湿度(%)", headerFormat);
    xlsx.write("D1", "光照强度(%)", headerFormat);
    
    int soilDataRowCount = 0; // 计数器，用于记录实际写入的土壤参数数据行数
    
    // 遍历查询结果，写入土壤参数数据
    for (int i = 0; i < results.size(); ++i) {
        const QVariantList &row = results.at(i);
        if (row.size() >= 8) { // 确保有足够的数据列
            int excelRow = i + 2; // Excel行号从2开始
            
            // 从数据库结果中提取数据
            QString timeString = row.at(1).toDateTime().toString("yyyy-MM-dd HH:mm:ss"); // 时间
            double soilTemp = row.at(5).toDouble(); // 土壤温度
            double soilHumidity = row.at(6).toDouble(); // 土壤湿度
            double lightIntensity = row.at(7).toDouble(); // 光照强度
            
            // 写入Excel
            xlsx.write(excelRow, 1, timeString, dataFormat);
            xlsx.write(excelRow, 2, soilTemp, dataFormat);
            xlsx.write(excelRow, 3, soilHumidity, dataFormat);
            xlsx.write(excelRow, 4, lightIntensity, dataFormat);
            
            soilDataRowCount++;
        }
    }
    
    // 如果有数据，创建土壤参数图表
    if (soilDataRowCount > 0) {
        int chartRow = soilDataRowCount + 3; // 图表位置在数据下方3行
        Chart *soilChart = xlsx.insertChart(chartRow, 1, QSize(800, 400)); // 插入图表
        
        soilChart->setChartType(Chart::CT_LineChart); // 设置为折线图
        soilChart->setChartTitle("土壤参数变化趋势"); // 设置图表标题
        
        // 添加土壤温度数据系列
        CellRange soilTempRange("A2:B" + QString::number(soilDataRowCount + 1));
        soilChart->addSeries(soilTempRange, nullptr, false, true);
        
        // 添加土壤湿度数据系列
        CellRange soilHumidityRange("A2:A" + QString::number(soilDataRowCount + 1) + ",C2:C" + QString::number(soilDataRowCount + 1));
        soilChart->addSeries(soilHumidityRange, nullptr, false, true);
        
        // 添加光照强度数据系列
        CellRange lightRange("A2:A" + QString::number(soilDataRowCount + 1) + ",D2:D" + QString::number(soilDataRowCount + 1));
        soilChart->addSeries(lightRange, nullptr, false, true);
        
        // 设置图表属性
        soilChart->setChartLegend(Chart::Top, false); // 图例在顶部
        soilChart->setAxisTitle(Chart::Bottom, "时间"); // X轴标题
        soilChart->setAxisTitle(Chart::Left, "数值"); // Y轴标题
    }
    
    // 打开文件保存对话框，让用户选择保存位置
    QString fileName = QFileDialog::getSaveFileName(
        this, 
        "导出Excel文件", 
        QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"), 
        "Excel Files (*.xlsx);;All Files (*)"
    );
    
    if (!fileName.isEmpty()) {
        // 确保文件扩展名为.xlsx
        if (!fileName.endsWith(".xlsx", Qt::CaseInsensitive)) {
            fileName += ".xlsx";
        }
        
        // 保存Excel文件
        if (xlsx.saveAs(fileName)) {
            qDebug() << "[导出数据] 成功保存Excel文件: " << fileName;
            QMessageBox::information(this, "导出成功", QString("数据已成功导出到\n%1").arg(fileName));
        } else {
            qDebug() << "[导出数据] 保存Excel文件失败";
            QMessageBox::warning(this, "导出失败", "无法保存Excel文件，请检查文件路径和权限");
        }
    } else {
        qDebug() << "[导出数据] 用户取消了导出操作";
    }
}

Widget::~Widget()
{
    // 确保在释放图表前清除数据
    if (customPlot1) {
        customPlot1->clearGraphs();
        delete customPlot1;
        customPlot1 = nullptr;
    }
    
    if (customPlot2) {
        customPlot2->clearGraphs();
        delete customPlot2;
        customPlot2 = nullptr;
    }
    
    // 清除数据向量
    timeData1.clear();
    tempData.clear();
    humidityData.clear();
    oxygenData.clear();
    timeData2.clear();
    soilTempData.clear();
    soilHumidityData.clear();
    lightData.clear();
    
    // 安全删除调试窗口
    if (deb) {
        delete deb;
        deb = nullptr;
    }
    
    // 安全删除MySQL窗口 - 在主窗口关闭时正确断开数据库连接
    if (mysqldb) {
        try {
            // 调用Mysql类提供的公共方法断开数据库连接
            mysqldb->disconnectDatabase();
            
            // 给一点额外时间确保所有事件都已处理
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            
            // 安全删除MySQL窗口对象
            delete mysqldb;
            mysqldb = nullptr;
        } catch (...) {
            // 捕获异常，避免程序崩溃
            delete mysqldb;
            mysqldb = nullptr;
        }
    }
    
    // 释放UI对象
    delete ui;
}

