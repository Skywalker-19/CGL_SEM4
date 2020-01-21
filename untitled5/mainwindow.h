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
   void Bresenham_Circle(float);
   void Bresenham_Line(float,float,float,float);
   void circle(float,float);
   void triangle();
   void dda_circle(float r);

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
