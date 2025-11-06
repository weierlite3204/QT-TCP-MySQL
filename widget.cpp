#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    msgserver=new MyTcpServer(this);//创建Tcp服务器对象
    //QHostAddress::Any //双栈任意地址。以这种地址绑定的套接字将同时监听两个端口。 一。
    msgserver->listen(QHostAddress::Any,port);//监听端口

}

//有客户端连接到消息服务器
void Widget::do_msgnewConnection(qintptr socket)//处理客户端msgsocket的连接
{
    //传的是socket描述符，根据socket描述符，可以初始化TcpSocket
    MsgWorker *worker=new MsgWorker(socket);//初始化客户端线程
    worker->start();//因为继承了QThread，这里启动线程，启动run（）函数
    connect(worker,&MsgWorker::deletethread,this,[worker](){//线程的安全销毁
        worker->exit();//通知子线程退出事件循环
        worker->wait();//阻塞当前线程（这里是主线程），等待子线程完全退出
        worker->deleteLater();//安排worker对象在合适的时机（主线程事件循环中）被删除，
        //避免直接delete可能导致的线程安全问题（如子线程仍在运行时被删除）。
        qDebug()<<"成功删除通信线程"<<'\n';
    });
}

Widget::~Widget()
{
    delete ui;
}
