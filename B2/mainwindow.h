#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QRgb"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void Bresenham_Solid(int x2,int y2,int x1,int y1);
     void floodfill(int x,int y,QRgb fill_color,QRgb old_color);
private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

    void mousePressEvent(QMouseEvent *e);

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
