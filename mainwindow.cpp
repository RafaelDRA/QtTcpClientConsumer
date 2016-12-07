#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QListWidget>
#include <QStandardItem>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  //linka o botão connect com o slot getIP
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(getIP()));

  //linka o botão disconnect com o slot disconnectS
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(disconnectS()));

  //linka o botão refresh com o slot refresh
  connect(ui->pushButtonRefresh,
          SIGNAL(clicked(bool)),
          this,
          SLOT(listIP()));

  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(start()));

  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stop()));

  connect(this,
          SIGNAL(lista(vector<int>*)),
          ui->widget,
          SLOT(getData(vector<int>*)));

}

// conecta o cliente ao servidor especificado
void MainWindow::tcpConnect(QString str){
  socket->connectToHost(str,1234);
  qDebug() << str;
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected to " + str;
  }
  else{
    qDebug() << "Disconnected";
  }
}

//copia o texto da caixa de texto para uma qstring
void MainWindow::getIP()
{
    QString str= ui->lineEditIP->text();
    tcpConnect(str);
}

//desconecta o cliente do servidor
void MainWindow::disconnectS()
{
    socket->disconnectFromHost();
    qDebug() << "Disconnected from server";
}

void MainWindow::timerEvent(QTimerEvent *e){
    delay += frequencia;
    if (delay>=100 && socket->state() == QAbstractSocket::ConnectedState){
        QString str, req;
        req = "get " + ui->listWidget->currentItem()->text() + "\r\n";
        QStringList list;
        QDateTime datetime;
        qDebug() << "to get data...";
        if(socket->state() == QAbstractSocket::ConnectedState){
            if(socket->isOpen()){
                qDebug() << "reading...";
                ui->listWidget->currentItem()->text();
                socket->write(req.toStdString().c_str());
                socket->waitForBytesWritten(3000);
                socket->waitForReadyRead(3000);
                qDebug() << socket->bytesAvailable();
                while(socket->bytesAvailable()){
                    str = socket->readLine().replace("\n","").replace("\r","");
                    list = str.split(" ");
                    if(list.size() == 2){
                        datetime.fromString(list.at(0),Qt::ISODate);
                        str = list.at(1);
                        l->push_back(str.toInt());
                    }
                }
            }
        }
        emit lista(l);
    }
}

void MainWindow::setVelocidade(int freq){
    this->frequencia = freq;
}

void MainWindow::start(){
    if (!flag && socket->state() == QAbstractSocket::ConnectedState){
    timer = startTimer(10);
    flag = true;
    }
}

void MainWindow::stop()
{
    killTimer(timer);
    flag = false;
}

void MainWindow::listIP()
{
    QString str;
    QStringList list;
    QDateTime datetime;
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
          qDebug() << "reading...";
          socket->write("list \r\n");
          socket->waitForBytesWritten();
          socket->waitForReadyRead();
          qDebug() << socket->bytesAvailable();
          while(socket->bytesAvailable()){
              str = socket->readLine().replace("\n","").replace("\r","");
              list = str.split(" ");
              if(list.size() == 2){
                  datetime.fromString(list.at(0),Qt::ISODate);
                  str = list.at(1);
              }
          }

        }
    }
    ui->listWidget->clear();
    ui->listWidget->addItem(str);
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
