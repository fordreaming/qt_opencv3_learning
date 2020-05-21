#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <string>
#include "imagedata.h"

using namespace image_proc;
using namespace cv;
using std::string;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow              *ui;
    QImage                      m_imgSrc;
    cv::Mat                     m_matSrc;
    cv::Mat                     m_matDst;
    QImage                      m_imgDst;
    string                      m_imgString;
};

#endif // MAINWINDOW_H
