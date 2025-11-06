#include "msgworker.h"

MsgWorker::MsgWorker(qintptr sock,QObject *parent)//构造函数
    : QThread{parent},m_sock(sock)
{

}

void MsgWorker::disconnect()//断开连接
{
    msgsocket->disconnectFromHost();
}

MsgWorker::~MsgWorker()//析构函数
{
    if(msgsocket){
        msgsocket->deleteLater();
    }
}

//线程启动，构建TcpSocket对象，读取数据
void MsgWorker::run()
{
    //sql=new LinkSQL(this);
    msgsocket=new QTcpSocket;
    msgsocket->setSocketDescriptor(m_sock);
    connect(msgsocket,&QTcpSocket::readyRead,this,[this](){//有数据要接受
        qDebug()<<"--------------数据到达"<<'\n';
        msgreaddata(msgsocket);
    },Qt::DirectConnection);
    connect(msgsocket, &QTcpSocket::disconnected,this, [this](){//收到信号断开连接
        qDebug()<<"线程结束-------------"<<'\n';
        quit();//中止事件循环
        this->wait();
        emit deletethread();

    },Qt::DirectConnection);
    exec();//开始事件循环
}

//接收下位机传来的数据
void MsgWorker::msgreaddata(QTcpSocket *msgtcp)
{
    //TCP 是 “流式传输”，客户端发送的多个数据包可能被合并成一个 “数据流” 到达服务器
    //用while循环持续处理socket中所有可用数据
    while(msgtcp->bytesAvailable()>0){//收到的数据不为空
        if(msgtcp->bytesAvailable()<static_cast<qint64>(sizeof(qint64))){//可读取的字节数小于8字节
            return;
        }
        qint64 len;
        // msgtcp->read(reinterpret_cast<char*>(&len), sizeof(len));//读取8字节的数据（二进制流），存入len变量。
        // len = qFromBigEndian(len);// 网络字节序→主机字节序，因为之前传输的时候变成了大端，所以接收的时候要反转
        // while (msgtcp->bytesAvailable() < len) {
        //     if (!msgtcp->waitForReadyRead(1000))//等1s，超时为假，！假为真
        //         break;
        // }
        QByteArray data = msgtcp->read(len);
        managejson(data,msgtcp);
    }
}


void MsgWorker::managejson(QByteArray data, QTcpSocket *msgtcp)
{

}

