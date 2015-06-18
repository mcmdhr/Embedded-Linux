#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QString>
#include <QDebug>
#include "tcpclient.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
public:
    struct info setInfo(int tag, int cmd);
    int newConnect();
    ~MainWindow();

private slots:

    void on_btnLED1_clicked();

    void on_btnConnect2Server_clicked();

    void on_btnLED2_clicked();

    void on_btnLED3_clicked();

    void on_btnLED4_clicked();

    void on_brnTem_clicked();

    void on_btnSong_clicked();

    void on_btnViewImage_clicked();

private:
    QTcpSocket *tcpsocket;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H




