#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    serv = new my_server(9091, this);
    connect(serv, SIGNAL(text_to_console(QString)), this, SLOT(append_text_to_console(QString)));
    connect(serv, SIGNAL(map_to_combo_box(QMap<int,client*>)), this, SLOT(update_combo_box(QMap<int,client*>)));

}

void MainWindow::update_combo_box(QMap<int, client *> map)
{
    ui->comboBox->clear();
    foreach (int key, map.keys())
        ui->comboBox->addItem(QString::number(key));
}

void MainWindow::append_text_to_console(QString text)
{
    ui->textEdit->append(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_3_clicked()
{
  if (serv != NULL)
  {
      serv->send_to_client(ui->comboBox->currentText().toInt(), "hello_)");
  }

}
