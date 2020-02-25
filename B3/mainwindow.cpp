#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include "QMouseEvent"
#include<iostream>
using namespace std;

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

string code="";
int decider=0;
int clip=0;
int InitialX = 0;
   int InitialY = 0;
 int  FinalX = 0;
 int FinalY = 0;
 int xMin,yMin,xMax,yMax;
 QRgb color=qRgb(255,0,0);
  QRgb black=qRgb(0,0,0);
 QImage image(411,341,QImage::Format_RGB888);
 bool  MousePressed = false;
 int n=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        ui->label->setPixmap(QPixmap::fromImage(image));
        ui->label->show();
    }


MainWindow::~MainWindow()
{
    delete ui;
}



  void MainWindow::mousePressEvent(QMouseEvent* event)
  {
      MousePressed = true;
      if(event->button()==Qt::LeftButton){
      InitialX = event->pos().x();
      InitialY = event->pos().y();
      }
  }

  void MainWindow::mouseReleaseEvent(QMouseEvent* event)
  {
      MousePressed = false;
      if(event->button()==Qt::LeftButton){
      FinalX = event->pos().x();
      FinalY = event->pos().y();
      }
      DrawItem();
  }

  void MainWindow::DrawItem(){
      if(decider==0)
      {
       if(clip==0){
       coordinates[n][0]=InitialX;
       coordinates[n][1]=InitialY;
       coordinates[n][2]=FinalX;
       coordinates[n][3]=FinalY;
       }
       Bresenham_Solid(coordinates[n][2],coordinates[n][3],coordinates[n][0],coordinates[n][1]);
       ++n;

      }
   if(decider==1)
      {
       if(clip==0){
       xMin=min(InitialX,FinalX);
       yMin=min(InitialY,FinalY);
       xMax=max(InitialX,FinalX);
       yMax=max(InitialY,FinalY);
       }
       Bresenham_Solid(xMin,yMin,xMax,yMin);
       Bresenham_Solid(xMin,yMin,xMin,yMax);
       Bresenham_Solid(xMax,yMin,xMax,yMax);
       Bresenham_Solid(xMin,yMax,xMax,yMax);
      }
   ui->label->setPixmap(QPixmap::fromImage(image));
   ui->label->show();

}


  void MainWindow::Bresenham_Solid(int x2,int y2,int x1,int y1){

          int dx=x2-x1;
          int dy=y2-y1;
          int xa=x1;
          int ya=y1;
          bool swapped=false;
          int sx=x2>x1?1:(-1);
          int sy=y2>y1?1:(-1);
          if(abs(dx)<abs(dy)){ //if slope>m
              swap(dx,dy);
              swap(xa,ya);
              swap(sx,sy);
              swapped=true;
          }
          int pk=2*abs(dy)-abs(dx);
          for(int i=0;i<abs(dx);i++){
               if(swapped)
              {
                      image.setPixel(ya,xa,color);
              }
              else if(!swapped)
                 {
                      image.setPixel(xa,ya,color);
                }
              cout<<xa<<","<<ya<<"\n";
              xa+=sx;
              if(pk<0)
                  pk=pk+2*abs(dy);
              else{
                  ya+=sy;
                  pk=pk+2*abs(dy)-2*abs(dx);
              }
          }
      return;
  }


  int MainWindow::computeCode(int x, int y)
  {
      int code=INSIDE;
      if(x<xMin)
          code=code|LEFT;
      if(x>xMax)
          code=code|RIGHT;
      if(y<yMin)
          code=code|BOTTOM;
      if(y>yMax)
          code=code|TOP;

      return code;
  }

  void MainWindow::cohenSutherlandClip(int i)
  {
      int x1=coordinates[i][0];
      int y1=coordinates[i][1];
      int x2=coordinates[i][2];
      int y2=coordinates[i][3];

      int code1=computeCode(x1,y1);
      int code2=computeCode(x2,y2);

      bool clipped=false;

      while(true){
          if(code1==0 && code2==0){
              clipped=true;
              break;
          }
          else if(code1 & code2)
              break;
          else{
              int codeOut,x,y;

              if(code1)
                  codeOut=code1;
              else
                  codeOut=code2;

              if(codeOut & TOP){
                  x=x1+(x2-x1)*(yMax-y1)/(y2-y1);
                  y=yMax;
              }
              else if(codeOut & BOTTOM){
                  x=x1+(x2-x1)*(yMin-y1)/(y2-y1);
                  y=yMin;
              }
              else if(codeOut & RIGHT){
                  x=xMax;
                  y=y1+(y2-y1)*(xMax-x1)/(x2-x1);
              }
              else if(codeOut & LEFT){
                  x=xMin;
                  y=y1+(y2-y1)*(xMin-x1)/(x2-x1);
              }
              if(code1==codeOut){
                  x1=x;
                  y1=y;
                  code1=computeCode(x1,y1);
              }
              else{
                  x2=x;
                  y2=y;
                  code2=computeCode(x2,y2);
              }
          }
      }
      if(clipped){
          coordinates[i][0]=x1;
          coordinates[i][1]=y1;
          coordinates[i][2]=x2;
          coordinates[i][3]=y2;
          cout<<"\nClipped!";
      }
      else{
          coordinates[i][0]=0;
          coordinates[i][1]=0;
          coordinates[i][2]=0;
          coordinates[i][3]=0;
          cout<<"\nRejected";
      }
  }

void MainWindow::on_pushButton_clicked()
{
    clip=0;
    decider=0;
}

void MainWindow::on_pushButton_2_clicked()
{
    clip=0;
    decider=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    image.fill(black);
    clip=1;
    decider=0;
    int f=n;
    n=0;
    for(int i=0;i<f;i++){
        cohenSutherlandClip(i);
        DrawItem();

    }

    decider=1;
    DrawItem();
}
