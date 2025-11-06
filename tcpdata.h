#ifndef TCPDATA_H
#define TCPDATA_H

#include <QObject>

class TcpData : public QObject
{
    Q_OBJECT
public:
    explicit TcpData(QObject *parent = nullptr);

private:


signals:
};

#endif // TCPDATA_H
