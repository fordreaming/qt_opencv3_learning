#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    cv::Mat img = imread("0314-0009-07-ng_a.jpg", IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    cv::Mat imgBlured;
    // 均值滤波
    blur(img, imgBlured, Size(7, 7));
    imwrite("bluredImage.jpg", imgBlured);
    // 源图像减去均值滤波的图像
    cv::Mat imgSubtractBlured;
    imgSubtractBlured = img - imgBlured;
    imwrite("subtractBlur.jpg", imgSubtractBlured);

}
