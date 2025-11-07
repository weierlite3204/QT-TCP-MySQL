#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    deb = new debugging();
    deb->show(); // 显示调试窗口
    msgserver=new MyTcpServer(this);//创建Tcp服务器对象
    //QHostAddress::Any //双栈任意地址。以这种地址绑定的套接字将同时监听两个端口。 一。
    msgserver->listen(QHostAddress::Any,port);//监听端口
    // 连接服务器的newDescriptor信号到Widget的do_msgnewConnection槽函数
    connect(msgserver, &MyTcpServer::newDescriptor, this, &Widget::do_msgnewConnection);
    
    // 初始化图表
    initCharts();
}

//有客户端连接到消息服务器
void Widget::do_msgnewConnection(qintptr socket)//处理客户端msgsocket的连接
{
    //传的是socket描述符，根据socket描述符，可以初始化TcpSocket
    MsgWorker *worker=new MsgWorker(socket);//初始化客户端线程
    worker->start();//因为继承了QThread，这里启动线程，启动run（）函数
    
    // 连接worker的deletethread信号到线程安全销毁的lambda
    connect(worker,&MsgWorker::deletethread,this,[worker](){
        worker->wait();// 主线程等待子线程安全退出
        worker->deleteLater();// 安全释放线程对象
        qDebug()<<"成功删除通信线程"<<'\n';
    });
    
    // 连接worker的rawdata信号到调试窗口的showdata槽函数
    connect(worker, &MsgWorker::rawdata, deb, &debugging::showdata);//发送信号，让原始数据显示在调试界面
    connect(deb,&debugging::senddata,worker,&MsgWorker::sendstrdata);//接收到发送信号，发送数据给下位机
    connect(worker,&MsgWorker::showsensordata,this,&Widget::showdata);//发送信号，让接收到的数据显示在界面上
}

void Widget::initCharts()
{

}

void Widget::showdata(SensorData data)
{
    // 更新主界面数据监控部分的各个控件
    ui->airtem->setText(QString::number(data.atemp, 'f', 1) + "°C");    // 空气温度
    ui->airwater->setText(QString::number(data.ahumi, 'f', 1) + "%");  // 空气相对湿度
    ui->oxygen->setText(QString::number(data.oxygen, 'f', 1) + "%");   // 氧气浓度
    ui->soiltem->setText(QString::number(data.stemp, 'f', 1) + "°C");   // 土壤温度
    ui->soilwater->setText(QString::number(data.shumi2, 'f', 1) + "%"); // 土壤含水量
    ui->ray->setText(QString::number(data.light, 'f', 1) + "%");       // 光照强度
    

}

Widget::~Widget()
{

    
    delete ui;
}
