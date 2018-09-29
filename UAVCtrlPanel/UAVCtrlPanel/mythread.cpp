#include "mythread.h"
#include <QMessageBox>

MyThread::MyThread()
{
    m_pUdpRecv = nullptr;
}

void MyThread::run()
{
    exec();
}

bool MyThread::event(QEvent* e)
{
    if(e->type() == READY_TO_READ)
    {
        QMessageBox msg;
        msg.setText("Hello");
        msg.exec();
    }

    return true;
}

void MyThread::SetUdpSocketPtr(QUdpSocket* pUScoket, QHostAddress hostAddr, quint16 port)
{
    m_pUdpRecv = pUScoket;
    m_hostAddr = hostAddr;
    m_port = port;
}
