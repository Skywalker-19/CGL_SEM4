#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   void Bresenham_Dotted(float,float,float,float);
   void Bresenham_Dashed(float,float,float,float);
   void Bresenham_DotDash(float,float,float,float);
   void Bresenham_Solid(float,float,float,float);


private slots:
   void on_textEdit_textChanged();

   void on_textEdit_2_textChanged();

   void on_textEdit_3_textChanged();

   void on_textEdit_4_textChanged();

   void on_pushButton_clicked();

   void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_5_clicked();

   void on_pushButton_4_clicked();

   void on_textEdit_5_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
