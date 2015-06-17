#include "tcpclient.h"


/*
 * Create the connection with Server
*/
void creatConnect(QTcpSocket *tcpsocket, ADDR addr){
    tcpsocket->connectToHost(addr.ip, addr.port);
}

/*
 * Send message to Server
*/
void sendMessages(QTcpSocket *tcpsocket, INFO info){

   // tcpsocket->write();
    tcpsocket->write((char *)&info,sizeof(info));
}

/*
 * Disconnect the connection
*/
void disConnect(QTcpSocket *tcpsocket){

    tcpsocket->disconnectFromHost();
}


void recMessages();//Receive the message from Server
