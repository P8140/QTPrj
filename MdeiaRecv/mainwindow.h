#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork/QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QImage>
#include <QMessageBox>
#include "mythread.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public:
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;
    QStringList *fortunes;
    QImage *img;
    quint64 basize;

    MyThread* m_pMyThread;

public slots:
    void sendFortune();
    QByteArray GetPicData(QString fromPic);
    void DisplayError(QAbstractSocket::SocketError socketError);
    void ReadMyData();
    void ShowImage(QByteArray ba);
};

#endif // MAINWINDOW_H
