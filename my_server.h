#ifndef MY_SERVER_H
#define MY_SERVER_H

#include <QWidget>
#include <QTcpServer>

#include <QMessageBox>

#include <QDebug>


#include "client.h"
//class QTcpServer;
//class QTextEdit;
//class QTcpSocket;

class my_server : public QWidget {
    Q_OBJECT
    private:
        QTcpServer* m_ptcpServer;
        quint16     m_nNextBlockSize;

    private:

        QMap<int, client*> map_clients;

    public:
        my_server(int nPort, QWidget* pwgt = 0);
        void send_to_client(int id, QString mess);

    public slots:
        virtual void slotNewConnection();
                void slotReadClient   ();
                void slotDisconnected();

    signals:
        void text_to_console(QString text);
        void map_to_combo_box(QMap<int, client*> current_map);
};
#endif // MY_SERVER_H
