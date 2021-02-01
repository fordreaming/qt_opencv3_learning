#include "testcases.h"
#include "matchtemplate.h"

TestCases::TestCases()
{

}

void TestCases::GenerateBinaryImgTestCase()
{
    QString filePath = "classify6/0/";
    QString imgSavePath = "classify6/0/binaryImg/";
    QStringList fileNameList = LoadFiles(filePath, "*.jpg");
    foreach (QString fileName, fileNameList) {
        QString fileNamePath = filePath + fileName;
        cv::Mat srcImg = imread(fileNamePath.toStdString(), IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
        cv::Mat dstImg;
        ImageProc   imageProc;
        imageProc.ImageBinary(srcImg, dstImg);
        QString saveFileName = imgSavePath + fileName;
        imwrite(saveFileName.toStdString(), dstImg);
    }
}

void TestCases::FindOptimalTemplateTestCase()
{
    std::string templateImgName = "classify6/0/grayImg/templateImg/43079-1-1-11.jpg";
    cv::Mat templateImgWhole = imread(templateImgName, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    if(templateImgWhole.empty()) {
        qDebug() << "load tempalte image fail " << endl;
    }

    QString binarayImgPath = "classify6/0/grayImg/";
    QString L1ImgSavePath = "classify6/0/grayImg/L1Img/";
    ImageProc   imageProc;

    cv::Mat optimalTemplate = imageProc.GetOptimalTemplate(templateImgWhole, binarayImgPath, 0);

//    imageProc.CaptureImgPiece(optimalTemplate, binarayImgPath, L1ImgSavePath);

}

// circle radius = 114/2
// innerRadius =
void TestCases::TemplateMatchTestcase()
{
    ImageProc   imageProc;
    std::string imgName = "/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/good/1536-0022-01.jpg";
    cv::Mat img = imread(imgName, 0);


    qDebug() << "image type: " << img.channels() << endl;

    cv::Rect templateRect(2173, 389, 1356, 1381);
    cv::Mat templateImg = img(templateRect).clone();

    cv::Mat matchedImg;
    imageProc.GetTemplateImg(img, templateImg, MATCHED_IMG_POSITION_TOP_LEFT, matchedImg);
    imshow("matched image", matchedImg);
}

void TestCases::MatchRightCircleAccordTemplate()
{
    cv::Mat srcImg = cv::imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/good1/1536-0022-01.jpg",
                                IMREAD_GRAYSCALE);
    cv::Mat templateImg = cv::imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/template/rightCircleTemlateRect.png",
                                     cv::IMREAD_GRAYSCALE);

    MatchTemplate matchtemplt;

    vector<cv::Point> circleCenterPointsVec;
    if(srcImg.empty() || templateImg.empty()) {
        qDebug() << "input image error!" << endl;
    }

    matchtemplt.ExtarctMatchTemplateCenter(srcImg, templateImg, circleCenterPointsVec);
//    if(1 == circleCenterPointsVec.size()) {
//        qDebug() << "extract right circle error!" << endl;
//        return;
//    }
    // find circle
    cv::Mat outerCircle;
    cv::Mat innerCircle;
    cv::Mat roi;

    outerCircle = cv::Mat::zeros(templateImg.size(), CV_8UC1);
    innerCircle = cv::Mat::zeros(templateImg.size(), CV_8UC1);
    roi = cv::Mat::zeros(templateImg.size(), CV_8UC1);

    int outerRadius = templateImg.cols/2;
    int innerRadius = 500;

    circle(outerCircle, circleCenterPointsVec[0], innerRadius, CV_RGB(255, 255, 255), -1);
    circle(innerCircle, circleCenterPointsVec[0], outerRadius, CV_RGB(255, 255, 255), -1);

    cv::subtract(outerCircle, innerCircle, roi);
    cv::Mat roiMat;

    namedWindow("roi iamge", WINDOW_NORMAL);
    imshow("roi window", outerCircle);

    namedWindow("roi iamge1", WINDOW_NORMAL);
    imshow("roi window1", innerCircle);

    namedWindow("circle image", WINDOW_NORMAL);
    imshow("circle image", roi);

}

void TestCases::ExtractRightCircle()
{
    std::string beMatchedImgpath = "/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/good/";

    cv::Mat templateImg = cv::imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/template/rightCircleTemlateRect.png",
                                        cv::IMREAD_GRAYSCALE);
    std::string matchedImgpath = "/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/matchedImg/";
    cv::Mat image_matched;
    cv::Mat img_matchResult;
    cv::Mat src_modelImg;

    MatchTemplate matchtemplt;
    matchtemplt.matchTemplateBatch(beMatchedImgpath, templateImg, matchedImgpath, img_matchResult);
}

void TestCases::ExtractCircleHistgram()
{
    cv::Mat srcImg = cv::imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/good1/1536-0022-01.jpg",
                                IMREAD_GRAYSCALE);
    cv::Mat templateImg = cv::imread("/home/adt/qt/gitFordreaming/qt_opencv3_learning_build/OptimalTemplateMatch/452/template/rightCircleTemlateRect.png",
                                     cv::IMREAD_GRAYSCALE);

    MatchTemplate matchtemplt;

    vector<cv::Point> circleCenterPointsVec;
    if(srcImg.empty() || templateImg.empty()) {
        qDebug() << "input image error!" << endl;
    }

    matchtemplt.ExtarctMatchTemplateCenter(srcImg, templateImg, circleCenterPointsVec);
    if(1 != circleCenterPointsVec.size()) {
        qDebug() << "extract right circle error!" << endl;
        return;
    }
    // find circle
    cv::Mat outerCircle;
    cv::Mat innerCircle;
    cv::Mat roi;

    outerCircle = cv::Mat::zeros(templateImg.size(), CV_8UC1);
    innerCircle = cv::Mat::zeros(templateImg.size(), CV_8UC1);
    roi = cv::Mat::zeros(templateImg.size(), CV_8UC1);

    int outerRadius = templateImg.cols/2;
    int innerRadius = 500;

    circle(outerCircle, circleCenterPointsVec[0], innerRadius, CV_RGB(255, 255, 255), -1);
    circle(innerCircle, circleCenterPointsVec[0], outerRadius, CV_RGB(255, 255, 255), -1);

    cv::subtract(outerCircle, innerCircle, roi);
    cv::Mat roiMat;

    namedWindow("roi iamge", WINDOW_NORMAL);
    imshow("roi window", outerCircle);

    namedWindow("roi iamge1", WINDOW_NORMAL);
    imshow("roi window1", innerCircle);

    namedWindow("circle image", WINDOW_NORMAL);
    imshow("circle image", roi);
}

QStringList TestCases::LoadFiles(const QString &path, QString ext)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << ext;
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    return files;
}
