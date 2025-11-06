#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QObject>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);//重写连接函数

signals:
    void newDescriptor(qintptr socket);//用于发送tcp描述符，以供客户端socket初始化
};

#endif // MYTCPSERVER_H
