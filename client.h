#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QTime>
#include <QDataStream>
#include <QMap>


class client
{
private:
//    int ID;
    QTcpSocket* socket;


public:
    client(QTcpSocket* current_socket);
    void sendToClient(const QString& str);
    QTcpSocket* get_socket() ;//{ return socket };
};

#endif // CLIENT_H
