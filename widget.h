#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mytcpserver.h"
#include "msgworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    unsigned int port=1210;//端口号
    MyTcpServer *msgserver=NULL;//tcp服务

private slots:
    void do_msgnewConnection(qintptr socket);
};
#endif // WIDGET_H
