#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;
float x2,y2,x1,y1,length,breadth;
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


    QRgb value;
        value = qRgb(0,255,0);

        /*x1=(length/2);  y1=0;
        x2=length;  y2=(breadth/2);*/
        ddAlgo(length,breadth/2,length/2,0);

         /*x2=(length/2);  y2=breadth;
         x1=length;  y1=(breadth/2);*/
          ddAlgo(length/2,breadth,length,breadth/2);

         /* x2=0;  y2=(breadth/2);
          x1=(length/2);  y1=breadth;*/
          ddAlgo(0,breadth/2,length/2,breadth);

           /*x2=(length/2);  y2=0;
           x1=0;  y1=(breadth/2);*/
           ddAlgo(length/2,0,0,breadth/2);

            //BRESENHAM'S

            /*x2=(length/2)-(length/4);  y2=(breadth/2)+(breadth/4);
            x1=(length/4);  y1=(breadth/4);*/
            Bresenham((length/2)-(length/4),(breadth/2)+(breadth/4),(length/4),(breadth/4));
            Bresenham((length/2)+(length/4),(breadth/2)+(breadth/4),(length/4),(breadth/2)+(breadth/4));
            Bresenham((length/2)+(length/4),(breadth/2)+(breadth/4),(length/2)+(length/4),(breadth/2)-(breadth/4));
            Bresenham((length/2)+(length/4),(breadth/2)-(breadth/4),(length/4),(breadth/4));


            int x0=0,y0=0;
                int x1=0+length,y1=0;
                int x2=0+length,y2=0+breadth;
                int x3=0,y3=0+breadth;
                Bresenham(x0,y0,x1,y1);
                Bresenham(x1,y1,x2,y2);
                Bresenham(x2,y2,x3,y3);
                Bresenham(x3,x3,x0,y0);


         ui->label->setPixmap(QPixmap::fromImage(image));
         ui->label->show();

}

void MainWindow::ddAlgo(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);
     float dx=x2-x1;  float dy=y2-y1;
    float steps;
   if(abs(dy)>abs(dx))
       steps=abs(dy);
   else
       steps=abs(dx);

     float xi=dx/steps;
    float yi=dy/steps;

    for(int i=0;i<=steps;i++){
    image.setPixel(x1,y1,color);
    x1=x1+xi;
    y1=y1+yi;
    }
}


void MainWindow::Bresenham(float x2,float y2,float x1,float y1){

    QRgb color;
    color= qRgb(0,255,0);

    int dx=x2-x1;
        int dy=y2-y1;
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
            else
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
    length=str.toFloat();
}

void MainWindow::on_textEdit_2_textChanged()
{
    QString str=ui->textEdit_2->toPlainText();
    breadth=str.toFloat();
}
