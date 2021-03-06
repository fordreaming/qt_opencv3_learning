#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /***********************************************************************
     *  @function  LoadFiles
     *  @brief     ex: LoadFiles(filePath, "*.jpg");
     *  @return
     ***********************************************************************/
    static QStringList LoadFiles(const QString &path, QString ext);

private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_btnHistNormalize_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
