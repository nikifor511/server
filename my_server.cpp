#include "my_server.h"

my_server::my_server(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt), m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                              );
        m_ptcpServer->close();
        qDebug() << "ERROR started on port " + QString::number(nPort);
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()) );

    QMessageBox::information(0, "Server Started !" , "Server started on port " + QString::number(nPort));

}

void my_server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    int id_user_socket = pClientSocket->socketDescriptor();
    map_clients[id_user_socket]  = new client(pClientSocket);

    connect(pClientSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    map_clients[id_user_socket]->sendToClient("123456789");
    emit map_to_combo_box(this->map_clients);
    emit text_to_console("Client connected!");

}

void my_server::slotReadClient()
{

    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    //in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage =
            time.toString() + " " + "Client has sended - " + str;
        emit text_to_console(strMessage);
        qDebug() << strMessage;

        m_nNextBlockSize = 0;
    }
}

void my_server::send_to_client(int id, QString mess)
{
    map_clients[id]->sendToClient(mess);
}

void my_server::slotDisconnected()
{
    emit text_to_console("Client disconnected!!");
    foreach (client * value, this->map_clients)
        if (value->get_socket() == (QTcpSocket*)sender())
            map_clients.remove(map_clients.key(value));
    emit map_to_combo_box(map_clients);
}
