#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork/QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QImage>
#include <QImageReader>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    qint64 blockSize;
    QTcpSocket* tcpSocket;
    cv::VideoCapture cap;
    QTimer* timer;
private:
    void SingleSlotsInit();
private slots:
    void displayError(QAbstractSocket::SocketError);
    void requestNewFortune();
    void enableGetFortuneButton();
    void SendData();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
