#include "imagedata.h"
#include <vector>
#include <QDebug>
#include <QFileDialog>

namespace image_proc {

CImageData::CImageData()
{

}

CImageData::~CImageData()
{

}

bool CImageData::LoadFile(QString fileName, QImage &img)
{
    if(!img.load(fileName)){
        return false;
    }
    return true;
}

bool CImageData::LoadFile(QString fileName, cv::Mat &img)
{
    img = imread(fileName.toStdString());
    return true;
}

bool CImageData::ImageToGray8(const QImage &img, std::vector<unsigned char> &v_gray, int &rows, int &cols)
{
    if(img.isNull()){
        qDebug() << "qimage is null" << endl;
        return false;
    }
    QImage rgbImg = img.convertToFormat(QImage::Format_RGB888);
    rows = img.height();
    cols = img.width();
    v_gray.resize(rows * cols);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            v_gray[i*cols + j] = qBlue(rgbImg.pixel(j, i));
        }
    }
    return true;
}

bool CImageData::ImageToString(const QImage &img, const std::string &ext, std::string imgString)
{
    if((img.isNull()) || (ext.empty())){
        qDebug() << "qimage is null or file extension is null" << endl;
        return false;
    }
    cv::Mat mat;
    ImageToCvMat(img, mat);
    if(mat.empty()){
        qDebug() << "qimage convert to mat fail" << endl;
        return false;
    }
    std::vector<unsigned char> buff;
    if(!imencode(ext, mat, buff)){
        qDebug() << "image decode fail" << endl;
        return false;
    }
    imgString.resize(buff.size());
    memcpy(&imgString[0], buff.data(), buff.size());
    return true;
}

void CImageData::ImageToCvMat(const QImage &img, cv::Mat &mat)
{
    switch(img.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(img.height(), img.width(), CV_8UC4, (void*)img.constBits(), img.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(img.height(), img.width(), CV_8UC3, (void*)img.constBits(), img.bytesPerLine());
        cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(img.height(), img.width(), CV_8UC1, (void*)img.constBits(), img.bytesPerLine());
        break;
    }
}

QImage CImageData::CvmatToQImage(Mat mat)
{
    switch ( mat.type() )
    {
    case CV_8UC4:
    {
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32 );
        return image;
    }
    case CV_8UC3:
    {
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
        return image.rgbSwapped();
    }
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;
        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
            for (int i = 0; i < 256; ++i){
                sColorTable.push_back(qRgb( i, i, i ));
            }
        }
        QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        return image;
    }
    default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
    }
    return QImage();
}

void CImageData::SaveImg(const Mat img)
{
    QString fileName = QFileDialog::getSaveFileName(NULL,
        ("Save Image"),
        ".",
        ("Image Files (*.jpg)")
        );

    if (!fileName.isNull())
    {
        imwrite(fileName.toStdString(), img);
    }
}

}


