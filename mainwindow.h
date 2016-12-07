#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QStandardItemModel>
#include <vector>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect(QString);

signals:
  void lista(vector<int> *l);

public slots:
  void listIP();
  void getIP();
  void disconnectS();
  void start();
  void stop();
  void setVelocidade(int);
  void timerEvent(QTimerEvent*);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  bool flag = false;
  int delay =0;
  int frequencia =0;
  int timer =0;

public:
  vector<int> *l = new vector<int>();
};

#endif // MAINWINDOW_H
