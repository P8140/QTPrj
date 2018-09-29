#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QEvent>
#include <QUdpSocket>
#include <QHostAddress>
//extern QEvent* pEvent = new QEvent((QEvent::Type)5001);
#define READY_TO_READ 5001

class MyThread: public QThread
{
    Q_OBJECT
private:
    QUdpSocket* m_pUdpRecv;
    QHostAddress m_hostAddr;
    quint16 m_port;
public:
    MyThread();
    void UdpSocketInit(QHostAddress hostAddr, qint16 port);
    void run();
    bool event(QEvent* e);
    void SetUdpSocketPtr(QUdpSocket* pUScoket, QHostAddress hostAddr, quint16 port);
};

#endif // MYTHREAD_H
