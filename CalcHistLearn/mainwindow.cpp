#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QStringList>
#include <QString>

#include <QDebug>

#define INPUT_TITLE "input image"
#define OUTPUT_TITLE "histgram "


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

QStringList MainWindow::LoadFiles(const QString &path, QString ext)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << ext;
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = "validity/";
    QStringList fileNameList = LoadFiles(filePath, "*.jpg");

    foreach (QString fileName, fileNameList) {
        std::string fileNameWithPath;
        fileNameWithPath = (filePath + fileName).toStdString();
        cv::Mat img = imread(fileNameWithPath);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    cv::Mat src;
    cv::Mat dst;
    //加载图像
    src = imread("equalizeHist.jpg");
    if (!src.data)
    {
        cout << "ERROR : could not load image.";
        return ;
    }
    namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);

    imshow(INPUT_TITLE, src);

    cvtColor(src, src, CV_BGR2GRAY);

    const int channels[1] = {0};
    const int histSize[1] = {256};
    float hranges[2] = {0, 256};
    const float* ranges[1] = { hranges };

    MatND hist;
    calcHist(&src, 1, channels, Mat(), hist, 1, histSize, ranges);

    float sum = 0.f;
    for(int i = 0; i < hist.rows; i++) {
        for(int j = 0; j < hist.cols; j++) {
            sum += hist.at<float>(i, j);
        }
    }

    if( abs(sum - src.rows * src.cols) < 1E-6) {
        qDebug() << "calc histgram right" << endl;
    } else {
        qDebug() << "calc histgram error" << endl;
    }

    qDebug() << src.rows * src.cols << endl;
    qDebug() << "sum :" << sum << endl;
}

void MainWindow::on_pushButton_3_clicked()
{
    cv::Mat src = imread("timg.jpeg", IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    if (src.empty())
    {
        cout << "ERROR : could not load image.";
        return ;
    }

     // Quantize the hue to 30 levels
     // and the saturation to 32 levels
     int rBins = 256;
     int gBins = 256;
     int bBins = 256;

     int histSize[] = {rBins, gBins, bBins};

     // r,g,b varies from 0 to 255, see cvtColor
     float rRanges[] = { 0, 256 };
     float gRanges[] = { 0, 256 };
     float bRanges[] = { 0, 256 };

     const float* ranges[] = { rRanges, gRanges, bRanges };
     MatND hist;
     // we compute the histogram from the 0-th and 2-st channels
     int channels[] = {0, 1, 2};
     calcHist( &src, 1, channels, Mat(), hist, 3, histSize, ranges, true, false );
     qDebug() << "hist type" << hist.type() << endl;

     ofstream fout;
     fout.open("pixel.txt", ios::app);
     qDebug() << "histRows" << hist.rows << endl;
     qDebug() << "histCols" << hist.cols << endl;
     for(int i = 0; i < hist.rows; i++) {
         for(int j = 0; j < hist.cols; j++) {
             fout << hist.at<float>(i, j) << " ";
         }
         fout << endl;
     }

//     double maxVal = 0;
//     minMaxLoc(hist, 0, &maxVal, 0, 0);
//     int scale = 10;
//     Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);
//     for( int h = 0; h < hbins; h++ )
//         for( int s = 0; s < sbins; s++ )
//         {
//             float binVal = hist.at<float>(h, s);
//             int intensity = cvRound(binVal*255/maxVal);
//             rectangle( histImg, Point(h*scale, s*scale), Point( (h+1)*scale - 1, (s+1)*scale - 1),
//                        Scalar::all(intensity),
//                        CV_FILLED );
//         }
//     namedWindow( "Source", 1 );
//     imshow( "Source", src );
//     namedWindow( "H-S Histogram", 1 );
//     imshow( "H-S Histogram", histImg );
     waitKey();
}

void MainWindow::on_btnHistNormalize_clicked()
{

}
