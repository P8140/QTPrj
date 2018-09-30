#include "mythread.h"
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>

MyThread::MyThread()
{
    m_pTcpSocket = nullptr;
    m_basize = 0;
}

void MyThread::run()
{
    exec();
}

bool MyThread::event(QEvent* e)
{
    if(e->type() == ((QEvent::Type)READY_TO_READ))
    {

        QByteArray message;
        QDataStream in(m_pTcpSocket);
        in.setVersion(QDataStream::Qt_5_6);
        if(m_basize == 0)
        {
            if(m_pTcpSocket->bytesAvailable() < (int)sizeof(quint64))
            {
                return false;
            }
            in>>m_basize;
        }

        if(m_pTcpSocket->bytesAvailable( )< m_basize)
            return false;
        in>>message;
        ShowImage(message);
    }

    return true;
}


void MyThread::SetUdpSocketPtr(QTcpSocket* pTcpScoket)
{
    m_pTcpSocket = pTcpScoket;
}
