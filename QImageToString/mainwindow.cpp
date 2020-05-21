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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Images (*.png *.bmp *.jpg)")
                                                    );
    if(!fileName.isEmpty()){
        image_proc::CImageData::LoadFile(fileName, m_imgSrc);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    image_proc::CImageData::ImageToCvMat(m_imgSrc, m_matSrc);
    std::vector<uchar> imgData;
    cv::imencode(".jpg", m_matSrc, imgData);
    unsigned long len = imgData.size();
    char* cache = reinterpret_cast<char*>(imgData.data());
    std::string data_str(cache, len);
    m_imgString = data_str;
}

void MainWindow::on_pushButton_3_clicked()
{
    std::vector<uchar> imgDataDst;
    int len = m_imgString.length();
    imgDataDst.resize(len+1);
    memcpy(&imgDataDst[0], m_imgString.c_str(), len+1);
    m_matDst = imdecode(imgDataDst, CV_LOAD_IMAGE_COLOR);
    m_imgDst = image_proc::CImageData::CvmatToQImage(m_matDst);
    ui->label->setPixmap(QPixmap::fromImage(m_imgDst));
}
