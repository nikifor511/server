#include "client.h"

client::client(QTcpSocket *current_socket)
{
    this->socket = new QTcpSocket;
    this->socket = current_socket;
}

void client::sendToClient(const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    this->socket->write(arrBlock);
}

QTcpSocket* client::get_socket()
{
    return socket;
}
