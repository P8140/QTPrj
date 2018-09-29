#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pUdpRecv = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindowInit()
{
    m_pUdpRecv = new QUdpSocket(this);
    m_pMyThread = new MyThread();

    m_pUdpRecv->bind(10000, QUdpSocket::ShareAddress);
    connect(m_pUdpRecv, &QUdpSocket::readyRead, this, &MainWindow::CallThreadRead);
    if(m_pUdpRecv !=  nullptr && m_pMyThread !=  nullptr)
    {
        m_pMyThread->SetUdpSocketPtr(m_pUdpRecv, QHostAddress("127.0.0.1"), 10000);
    }
    m_pMyThread->start();
}

void MainWindow::on_pushButton_clicked()
{
    QEvent* pEvent = new QEvent((QEvent::Type)READY_TO_READ);
    QApplication::postEvent(m_pMyThread, pEvent);
}

void MainWindow::CallThreadRead()
{
    QEvent* pEvent = new QEvent((QEvent::Type)READY_TO_READ);
    QApplication::postEvent(m_pMyThread, pEvent);
}
