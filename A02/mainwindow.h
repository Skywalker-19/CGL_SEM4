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
    void bresenhamCircle(int);
    void DDACircle(int);
    void drawCircle(int,int);
    void drawTriangle();
    void DDALine(int,int,int,int);
    ~MainWindow();

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
