#ifndef MSGWORKER_H
#define MSGWORKER_H

#include <QObject>
#include<QThread>
#include<QTcpSocket>

class MsgWorker : public QThread
{
    Q_OBJECT
public:
    explicit MsgWorker(qintptr sock,QObject *parent = nullptr);

    void disconnect();//断开连接

    ~MsgWorker();

private:
    QTcpSocket *msgsocket;//tcp套接字对象
    qintptr m_sock;//用于初始化tcp套接字的描述符。

protected:
    void run()override;

private:
    void managejson(QByteArray data,QTcpSocket *msgtcp);

public:signals:
    void deletethread();//要销毁线程

private slots:
    void msgreaddata(QTcpSocket *msgtcp);
};

#endif // MSGWORKER_H
