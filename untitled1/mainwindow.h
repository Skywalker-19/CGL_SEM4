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
    void ddAlgo(float,float,float,float);
    void Bresenham(float,float,float,float);

private slots:
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void on_textEdit_2_textChanged();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
