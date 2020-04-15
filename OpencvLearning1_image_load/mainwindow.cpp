#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("open image"), ".", tr("image file(*.png *.jpg *.jpeg *.bmp"));
    if(fileName.isEmpty()){
        return;
    }
    ui->stackedWidget->setCurrentIndex(0);
    Mat srcImg = imread(fileName.toLatin1().data());
    //format transform bgr2rgb
    cvtColor(srcImg, srcImg, COLOR_BGR2RGB);
    //construct QImage
    QImage disImage = QImage(static_cast<const uchar *>(srcImg.data), srcImg.cols, srcImg.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(disImage));
    ui->label->resize(ui->label->pixmap()->size());

}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open image"), ".", tr("image file(*.png *.jpg *.jpeg *.bmp"));
    if(fileName.isEmpty()){
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);
    Mat srcImg = imread(fileName.toLatin1().data());
    cvtColor(srcImg, srcImg, COLOR_BGR2RGB);
    QImage disImage = QImage(static_cast<const uchar *>(srcImg.data), srcImg.cols, srcImg.rows, QImage::Format_RGB888);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(disImage));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}
