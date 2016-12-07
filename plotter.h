#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QTcpSocket>
#include <vector>
#include <mainwindow.h>

using namespace std;

class Plotter : public QWidget{
  Q_OBJECT
private:
  float ampl, freq;
  float teta;
  float velocidade;

public:
  explicit Plotter(QWidget *parent = 0);

  void paintEvent(QPaintEvent *e);
signals:

public slots:
  void getData(vector<int> *l);
  void timerEvent(QTimerEvent *event);

private:
   QTcpSocket *socket;
   vector<int> *data = new vector<int>();
   int t = 0;
};

#endif // PLOTTER_H
