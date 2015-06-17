#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpclient.h"

INFO info;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket, SIGNAL(readyRead), this, SLOT(readMessage()));
}

int MainWindow::newConnect(){
    tcpsocket->abort();
    QString ip = ui->lineEditIP->text();
    QString sport = ui->lineEditPort->text();
    int port = sport.toInt();
    tcpsocket->connectToHost(ip, port);
    return 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnConnect2Server_clicked()
{
    ADDR addr;
    addr.ip = ui->lineEditIP->text();
    QString sport = ui->lineEditPort->text();
    addr.port = sport.toInt();
    creatConnect(tcpsocket, addr);
    memset(&info, 0, sizeof(info));

}

void MainWindow::on_btnLED1_clicked()
{
    INFO info;
    info = setInfo(6, 1);

    sendMessages(tcpsocket, info);
}

void MainWindow::on_btnLED2_clicked()
{
    INFO info;
    info = setInfo(6, 2);

    sendMessages(tcpsocket, info);
}

void MainWindow::on_btnLED3_clicked()
{
    INFO info;
    info = setInfo(6, 3);

    sendMessages(tcpsocket, info);
}

void MainWindow::on_btnLED4_clicked()
{
    INFO info;
    info = setInfo(6, 4);

    sendMessages(tcpsocket, info);
}


struct info MainWindow::setInfo(int tag, int cmd){

    info.tag = tag;
    int temp = info.cmd;
    switch (tag) {
    case UP:
        break;
    case DOWN:
        break;
    case CHAT:
        break;
    case IMAGE:
        //temp ~= (temp && 0xf000);
        //temp = temp >> 8;
        info.cmd ^= 0xf000;
        return info;
        break;
    case SONG:
        temp =(temp && 0xfff0ffff);
        temp +=(cmd << 16);
        info.cmd = temp;
        break;
    case LED:
        temp |= (cmd << 20);
        info.cmd = temp;
        break;
    case TEMP:
        info.cmd ^= 0xf000000;
        break;
    default:
        break;
    }
    return info;
}
