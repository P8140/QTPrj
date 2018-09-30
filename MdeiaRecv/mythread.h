#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QEvent>
#include <QTcpServer>
#include <QTcpSocket>

//extern QEvent* pEvent = new QEvent((QEvent::Type)5001);
#define READY_TO_READ 5001

class MyThread: public QThread
{
    Q_OBJECT

public:
    MyThread();

    void run();

    bool event(QEvent* e);

    void SetUdpSocketPtr(QTcpSocket* pTcpScoket);
private:
    QTcpSocket* m_pTcpSocket;
    quint64 m_basize;
};

#endif // MYTHREAD_H
