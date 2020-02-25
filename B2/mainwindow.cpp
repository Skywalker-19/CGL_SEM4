#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include "QMouseEvent"
#include<iostream>
using namespace std;

int r,g,b;
QRgb color;
QRgb black=qRgb(0,0,0);
QImage image(411,341,QImage::Format_RGB888);
QImage pallete(411,341,QImage::Format_RGB888);
int coordinates[20][2];
int i=0;
int points;
int seedx,seedy;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e){
        if(i<points)
        {
            if(e->button()==Qt::LeftButton)
            {int x=e->pos().x();
            int y=e->pos().y();
            image.setPixel(x,y,color);
            coordinates[i][0]=x;
            coordinates[i][1]=y;
            i=i+1;
            }
        }

        if(e->button()==Qt::RightButton){
             seedx=e->pos().x();
              seedy=e->pos().y();
              image.setPixel(seedx,seedy,black);
        }

    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
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
                image.setPixel(ya,xa,color);
            else if(!swapped)
                image.setPixel(xa,ya,color);
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


void MainWindow::floodfill(int x,int y,QRgb fill_color,QRgb old_color) {
    if(image.pixel(x,y)==old_color)
     {
        image.setPixel(x,y,fill_color);
        floodfill(x+1,y,fill_color,old_color);
        floodfill(x-1,y, fill_color,old_color);
        floodfill(x,y+1, fill_color,old_color);
        floodfill(x,y-1, fill_color,old_color);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    points=str.toInt();
}

void MainWindow::on_pushButton_clicked()
{
    floodfill(seedx,seedy,color,black);
    black=color;
    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    r=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    g=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    b=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<points;i++){
        if(i!=points-1){
         Bresenham_Solid(coordinates[i][0],coordinates[i][1],coordinates[i+1][0],coordinates[i+1][1]);
        }
        else{
       Bresenham_Solid(coordinates[i][0],coordinates[i][1],coordinates[0][0],coordinates[0][1]);
        }
    }

    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
}
