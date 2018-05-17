#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "my_server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void append_text_to_console(QString text);
    void update_combo_box(QMap<int, client*> map);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    my_server* serv;





};

#endif // MAINWINDOW_H
