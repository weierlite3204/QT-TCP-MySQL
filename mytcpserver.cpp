#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{}

//重写TcpServer里面的 incomingConnection函数
//当有客户端通过 TCP 连接到服务器时，QTcpServer内部会自动触发incomingConnection函数，
//并传入一个唯一的socketDescriptor，传的是socket描述符，根据socket秒速符，可以初始化TcpSocket
void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //函数体内直接通过emit newDescriptor(socketDescriptor)发射信号
    emit newDescriptor(socketDescriptor);
}

