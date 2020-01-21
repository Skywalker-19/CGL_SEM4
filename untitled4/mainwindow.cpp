#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
//#include <QtMath>
using namespace std;

float x2,y2,x1,y1,dx,dy,w;
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

void MainWindow::on_pushButton_clicked()
{

    Bresenham_Dotted(x2,y2,x1,y1);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::Bresenham_Dotted(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

        dx=x2-x1;
        dy=y2-y1;
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
            if(swapped && i%2==0)
                image.setPixel(y,x,color);
            else if(!swapped && i%2==0)
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

void MainWindow::Bresenham_Dashed(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

        dx=x2-x1;
        dy=y2-y1;
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
            if(swapped && i%10!=0 && i%10!=1)
                image.setPixel(y,x,color);
            else if(!swapped && i%10!=0 && i%10!=1)
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

void MainWindow::Bresenham_DotDash(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

        dx=x2-x1;
        dy=y2-y1;
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
            if(swapped && (i%8<=4) || (i%8==6))
                image.setPixel(y,x,color);
            else if(!swapped && (i%16<=4) || (i%16==6))
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


void MainWindow::Bresenham_Solid(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

        dx=x2-x1;
        dy=y2-y1;
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

void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    x1=str.toFloat();
}

void MainWindow::on_textEdit_2_textChanged()
{
    QString str=ui->textEdit_2->toPlainText();
    y1=str.toFloat();
}

void MainWindow::on_textEdit_3_textChanged()
{
    QString str=ui->textEdit_3->toPlainText();
    x2=str.toFloat();
}

void MainWindow::on_textEdit_4_textChanged()
{
    QString str=ui->textEdit_4->toPlainText();
    y2=str.toFloat();
}


void MainWindow::on_pushButton_2_clicked()
{

    Bresenham_Dashed(x2,y2,x1,y1);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_3_clicked()
{

    Bresenham_DotDash(x2,y2,x1,y1);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_5_clicked()
{

    Bresenham_Solid(x2,y2,x1,y1);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}



void MainWindow::on_pushButton_4_clicked()
{
    int w1=(w-1)/2;
    dy=y2-y1; dx=x2-x1;
    /*w1*=qSqrt((dx*dx)+(dy*dy))
            w1=w1/abs(y2-y1);
            int w2=w1/(x2-x1);*/
    int m;
    if(dx)
        m=((y2-y1)/(x2-x1));
    if(m==1){
        w1=1.6*w1;
    }
    if(m>1||dx==0)
      for(int i=w1;i>=0;i--){
        Bresenham_Solid(x1-i,y1,x2-i,y2);
        Bresenham_Solid(x1+i,y1,x2+i,y2);
    }
    else{
        for(int i=w1;i>=0;i--){
          Bresenham_Solid(x1,y1-i,x2,y2-i);
          Bresenham_Solid(x1,y1+i,x2,y2+i);
      }
    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_textEdit_5_textChanged()
{
    QString str=ui->textEdit_5->toPlainText();
    w=str.toFloat();
}
