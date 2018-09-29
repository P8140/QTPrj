#ifndef MYTESTSOCKET_H
#define MYTESTSOCKET_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class MyTestSocket
{
public:
    MyTestSocket();

private:
    QUdpSocket* m_pUdpSocket;
    qint16 m_port;
    QString m_ip;

public:
    QString GetIP();
   // bool CreateSocket()
};

#endif // MYTESTSOCKET_H
