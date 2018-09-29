#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;

//Mat function();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    timer = new QTimer(this);
    SingleSlotsInit();

    cap.open("E:\\QTTools\\MediaTest\\Wildlife.avi");
    if(!cap.isOpened())
    {
        QMessageBox::information(this, tr("提示"), tr("视频没有打开"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Mat function()
//{
//    Mat img(500, 500, CV_8U, 100);
//    return img;
//}

void MainWindow::SingleSlotsInit()
{
    connect(ui->StartButton, SIGNAL(clicked(bool)), this, SLOT(requestNewFortune()));
    connect(ui->StopButton, SIGNAL(clicked(bool)), this, SLOT(enableGetFortuneButton()));
    connect(timer, SIGNAL(timeout()), this, SLOT(SendData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

   //connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
}

void MainWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<"传输出错";
}


void MainWindow::requestNewFortune()
{
    timer->start(30);
    ui->StartButton->setEnabled(true);
}

void MainWindow::enableGetFortuneButton()
{
    ui->StartButton->setEnabled(true);
    tcpSocket->disconnectFromHost();
    timer->stop();
}

void MainWindow::SendData()
{
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress::LocalHost, 8888);
    Mat frame;
    cap>>frame;
    cvtColor(frame, frame, CV_BGR2RGB);

    QByteArray byte;
    QBuffer buf(&byte);
    QImage image((unsigned const char*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    image.save(&buf,"JPEG");
    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();

    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);

    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));
    tcpSocket->write(ba);
    ui->image_label->setPixmap(QPixmap::fromImage(image));
    ui->image_label->resize(image.size());

    update();
}






