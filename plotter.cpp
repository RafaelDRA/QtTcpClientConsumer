#define M_PI 3.14
#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>
#include <QMouseEvent>
#include <QDateTime>
#include <cstring>

using namespace std;

Plotter::Plotter(QWidget *parent) : QWidget(parent){
  startTimer(100);
  socket = new QTcpSocket(this);
}

void Plotter::getData(vector<int> *l)
{
    for(int i=0; i<l->size(); i++){
        data->push_back(l->at(i));
        }
    while(data->size() < width()){
            data->push_back(height()/50);
        }
    repaint();
}

void Plotter::timerEvent(QTimerEvent *event){
    t += 10;
}

void Plotter::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  QBrush brush;
  QPen pen;
  int x1, x2;
  int y1, y2;

  // habilita o anti-aliasing para que as
  // linhas sejam desenhadas sem serrilhados
  painter.setRenderHint(QPainter::Antialiasing);

  // define as props do preenchimento
  brush.setColor(QColor(0,0,0));
  brush.setStyle(Qt::SolidPattern);

  // define as props da caneta
  pen.setColor(QColor(45,255,75));
  pen.setWidth(3);

  // comunica as mudancas ao objeto painter
  painter.setBrush(brush);
  painter.setPen(pen);

  // desenha um retangulo
  painter.drawRect(0,0,width(), height());

  // atualiza as propriedades da caneta
  pen.setColor(QColor(45,255,75));
  pen.setWidth(1);
  // atualiza a caneta e desenha o eixo
  painter.setPen(pen);

  // primeiro ponto
  x1 = 0;
  y1 = height();
  if (t > 2){
      for(int i=0; i<width(); i++){
          x2 = i;
          y2 = height() - data->at(i)*height()/99;
          painter.drawLine(x1,y1,x2,y2);
          x1 = x2;
          y1 = y2;
      }
  }
  t = 0;
}

















