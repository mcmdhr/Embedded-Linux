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
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

int MainWindow::newConnect(){
   /* tcpsocket->abort();
    QString ip = ui->lineEditIP->text();
    QString sport = ui->lineEditPort->text();
    int port = sport.toInt();
    tcpsocket->connectToHost(ip, port);
    return 0;*/
    return 0;
}


MainWindow::~MainWindow()
{
    tcpsocket->disconnectFromHost();
    delete ui;
}

void MainWindow::readMessage(){
        INFO inforec;
        memset(&inforec, 0, sizeof(inforec));
        tcpsocket->read((char *)&inforec, sizeof(inforec));
        qDebug()<<"TEMP:"<<inforec.temp;
        qDebug()<<"IMAGE:"<<inforec.filename;
}

void MainWindow::on_btnConnect2Server_clicked()
{
    ADDR addr;
    addr.ip = ui->lineEditIP->text();
    QString sport = ui->lineEditPort->text();
    addr.port = sport.toInt();
    creatConnect(tcpsocket, addr);
    qDebug()<<tcpsocket->errorString();
    memset(&info, 0, sizeof(info));

}

int flag1 = 1;
void MainWindow::on_btnLED1_clicked()
{
    INFO info;
    //if (flag1 == 0)flag1 = 1; else flag1 = 0;
    info = setInfo(LED, flag1);
    qDebug()<<info.tag<<(info.cmd>>20);
    sendMessages(tcpsocket, info);
}

int flag2=2;
void MainWindow::on_btnLED2_clicked()
{
    INFO info;
    //if (flag2 == 0)flag2 = 2; else flag2 = 0;
    info = setInfo(LED, flag2);
    qDebug()<<info.tag<<(info.cmd>>20);
    sendMessages(tcpsocket, info);
}

int flag3=4;
void MainWindow::on_btnLED3_clicked()
{
    INFO info;
    //if (flag3 == 0)flag3 = 4; else flag3 = 0;
    info = setInfo(LED, flag3);
    qDebug()<<info.tag<<(info.cmd>>20);
    sendMessages(tcpsocket, info);
}

int flag4=8;
void MainWindow::on_btnLED4_clicked()
{
    INFO info;
    //if (flag4 == 0)flag4 = 8; else flag4 = 0;
    info = setInfo(LED, flag4);
    qDebug()<<info.tag<<(info.cmd>>20);

    sendMessages(tcpsocket, info);
}

void MainWindow::on_brnTem_clicked()
{
    INFO info;
    info = setInfo(TEMP, 1);
    qDebug()<<info.tag<<info.cmd;
    sendMessages(tcpsocket, info);
  //  work(info.tag);
}

void MainWindow::on_btnSong_clicked()
{
    INFO info;
    info = setInfo(SONG, 1);
    qDebug()<<info.tag<<info.cmd;
    sendMessages(tcpsocket, info);
}

void MainWindow::on_btnViewImage_clicked()
{
    INFO info;
    info = setInfo(IMAGE, 1);
    qDebug()<<info.tag<<info.cmd;
    sendMessages(tcpsocket, info);
    return;
}


void MainWindow::work(int tag){
    //recMessages(tcpsocket);
    //qDebug()<<"Rec"<<info.tag<<info.cmd;
   /* switch (tag) {
    case UP:
        break;
    case DOWN:
        break;
    case CHAT:
        break;
    case IMAGE:

        break;
    case SONG:
        break;
    case LED:
        break;
    case TEMP:
        break;
    default:
        break;

    }*/
    return;
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
            info.cmd ^= 0xf000;
            break;
        case SONG:
            temp ^=(cmd << 16);
            info.cmd = temp;
            break;
        case LED:
            temp ^= (cmd << 20);
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

