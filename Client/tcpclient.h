#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "mainwindow.h"

#define UP 1
#define DOWN 2
#define CHAT 3
#define IMAGE 4
#define SONG 5
#define LED 6
#define TEMP 7

typedef struct sockaddr SA;

typedef struct info {
    int tag;
    int cmd;
    char filename[32];
    char buf[1024];
    float temp;
}INFO;

typedef struct addr {
    QString ip;
    int port;
}ADDR;

void creatConnect(QTcpSocket *tcpsocket, ADDR addr);//Create the connection with Server
void sendMessages(QTcpSocket *tcpsocket, INFO info);//Send message to Server
void disConnect(QTcpSocket *tcpsocket);
void recMessages(QTcpSocket *tcpsocket, INFO info);//Receive the message from Server

#endif // TCPCLIENT_H
