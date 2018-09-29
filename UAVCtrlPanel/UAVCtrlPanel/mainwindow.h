#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include "mythread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MainWindowInit();
private slots:
    void on_pushButton_clicked();
    void CallThreadRead();
private:
    Ui::MainWindow *ui;
    MyThread* m_pMyThread;
    QUdpSocket* m_pUdpRecv;
};

#endif // MAINWINDOW_H
