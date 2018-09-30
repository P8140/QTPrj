#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any, 8888))
    {
        QMessageBox::critical(this, tr("Fortune Server"), tr("Unable to start the server"));
        close();
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
    m_pMyThread = new MyThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendFortune()
{
    basize = 0;
    tcpServerConnection = tcpServer->nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(ReadMyData()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayError(QAbstractSocket::SocketError)));

    m_pMyThread->SetUdpSocketPtr(tcpServerConnection);
}

QByteArray MainWindow::GetPicData(QString fromPic)
{
    QImage img(fromPic);
    QByteArray block;
    QBuffer buf(&block);
    img.save(&buf, "JPEG");
    QByteArray cc = qCompress(block, 1);
    QByteArray hh;
    hh = cc.toBase64();
    return hh;
}

void MainWindow::DisplayError(QAbstractSocket::SocketError socketError)
{
    tcpServerConnection->close();
}

void MainWindow::ReadMyData()
{
    QEvent* pEvent = new QEvent((QEvent::Type)READY_TO_READ);
    QApplication::postEvent(m_pMyThread, pEvent);


    /*QByteArray message;
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_6);
    if(basize == 0)
    {
        if(tcpServerConnection->bytesAvailable() < (int)sizeof(quint64))
        {
            return;
        }
        in>>basize;
    }

    if(tcpServerConnection->bytesAvailable()<basize)
        return;
    in>>message;
    ShowImage(message);*/
}

void MainWindow::ShowImage(QByteArray ba)
{
    QString ss = QString::fromLatin1(ba.data(), ba.size());
    QByteArray rc;
    rc = QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc = qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->image_label->setPixmap(QPixmap::fromImage(img));
    ui->image_label->resize(img.size());
    update();
}
