#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<math.h>
using namespace std;
float radius;
float xi=250.0;
float yi=195.0;
QImage image(411,341,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    radius=str.toFloat();
}

void MainWindow::on_pushButton_clicked()
{
    Bresenham_Circle(radius);
    triangle();
    QRgb color;
    color= qRgb(0,255,0);
    image.setPixel(xi,yi,color);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}


void MainWindow::Bresenham_Circle(float r){

    float x=0;
    float y=r;
    float p=3-(2*r);
    circle(x,y);
    while((y)>=x){
        x++;
        if(p<0)
            p=p+(4*x)+6;
        else
         {p=p+(4*(x-y))+10;
            y--;}
       circle(x,y);
    }
}

void MainWindow::circle(float x,float y){

    QRgb color;
    color= qRgb(0,255,0);
    image.setPixel(xi+x,yi+y,color);
    image.setPixel(xi-x,yi+y,color);
    image.setPixel(xi+x,yi-y,color);
    image.setPixel(xi-x,yi-y,color);
    image.setPixel(xi+y,yi+x,color);
    image.setPixel(xi-y,yi+x,color);
    image.setPixel(xi+y,yi-x,color);
    image.setPixel(xi-y,yi-x,color);

}

void MainWindow::triangle(){
    float x1=xi;
    float y1=yi-radius;
    float y2=yi+(radius/2);
    float x2=xi+(0.866*radius);
    Bresenham_Line(x2,y2,x1,y1);
    y2=yi+(radius/2);
    x2=xi-(0.866*radius);
    Bresenham_Line(x2,y2,x1,y1);
    x1=xi+(0.866*radius);
    y1=yi+(radius/2);
    Bresenham_Line(x2,y2,x1,y1);
    //Bresenham_Circle((radius/2));
    dda_circle((radius/2));
}

void MainWindow::Bresenham_Line(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

        float dx=x2-x1;
        float dy=y2-y1;
        int x=x1;
        int y=y1;
        bool swapped=false;
        int sx=x2>x1?1:(-1);
        int sy=y2>y1?1:(-1);
        if(abs(dx)<abs(dy)){ //if slope>m
            swap(dx,dy);
            swap(x,y);
            swap(sx,sy);
            swapped=true;
        }
        int pk=2*abs(dy)-abs(dx);
        for(int i=0;i<abs(dx);i++){
            if(swapped)
                image.setPixel(y,x,color);
            else if(!swapped)
                image.setPixel(x,y,color);
            cout<<x<<","<<y<<"\n";
            x+=sx;
            if(pk<0)
                pk=pk+2*abs(dy);
            else{
                y+=sy;
                pk=pk+2*abs(dy)-2*abs(dx);
            }
        }
    return;
}

void MainWindow::dda_circle(float r)
{
    QRgb color;
    color= qRgb(0,255,0);
  int val,i;

  float x1,x2,y1,y2,eps,sx,sy;
   x1=r;
   y1=0;
   sx=x1;
   sy=y1;

  i=0;

  do{

      val=pow(2,i);
      i++;

      }while(val<r);

  eps = 1/pow(2,i-1);

  do{
      x2 = x1 + y1*eps;
      y2 = y1 - eps*x2;
      image.setPixel(xi+x2,yi-y2,color);

      x1=x2;
      y1=y2;

     }while((y1-sy)<eps || (sx-x1)>eps);

}
