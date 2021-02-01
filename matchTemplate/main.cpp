#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include"findoutercontours.h"
#include"pointsmatch.h"
#include"matchtemplate.h"
#include "gomp/omp.h"
#include "imgproc.h"

using namespace cv;
using namespace std;

cv::Mat g_srcImage, g_tempalteImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;
int g_templateX, g_templateY;
int g_distance;

//cv::Mat ImgStandard,ImgNew,ImgNew_gray;
//std::vector<float> XStandard,YStandard;
//std::vector<float> XOutput,YOutput;
string path = "/mnt/hgfs/VMsharedfiles/kmeansClasses/0/";
//string path_cutting="/mnt/hgfs/VMsharedfiles/kmeansClasses/0cutting/";
//string path_35588="/mnt/hgfs/VMsharedfiles/kmeansClasses4/0/";
//string destpath_3588="/mnt/hgfs/VMsharedfiles/kmeansClasses4/0adaptiveImg/";


int GetArea(const cv::Mat& img)
{
    cv::Mat srcImage_gray = img.clone();
    cv::threshold(srcImage_gray, srcImage_gray, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY_INV);
    return cv::countNonZero(srcImage_gray);
}

void imgStandardmatchImgNew(cv::Mat imgStandard, cv::Mat imgNew,std::vector<float> xStandard,std::vector<float> yStandard,std::vector<float>&xOutput,std::vector<float>&yOutput)
{
    vector<float> x1, y1, x2, y2, resx, resy;
    FindOuterContour obj;
    obj.PeripheralTraversa(imgStandard, x1, y1);
    obj.PeripheralTraversa(imgNew, x2, y2);
    PointsMatch  objp;
    double thea, tx, ty, sxc, syc;
    objp.ICP(x2,y2,x1,y1,resx,resy,thea);
    objp.getTranslationVector(x2, y2,x1, y1, tx, ty,sxc,syc);

    for(int i=0;i<int(xStandard.size());i++)
    {
        float xs=xStandard[i]/obj.NN, ys=yStandard[i]/obj.NN;
        xOutput.push_back(int((sxc+(xs-sxc)*cos(thea)-(ys-syc)*sin(thea)+tx)*obj.NN));
        yOutput.push_back(int((syc+(ys-syc)*cos(thea)+(xs-sxc)*sin(thea)+ty)*obj.NN));
    }
}

void imageAdaptiveOne(cv::Mat srcImage,std::vector<float>&xStandard,std::vector<float>&yStandard)
{
    std::vector<cv::Point> location;
    cv::Mat srcImage_gray;
    if(srcImage.channels()>1)
        cv::cvtColor(srcImage, srcImage_gray, cv::COLOR_BGR2GRAY);
    else
        srcImage_gray=srcImage.clone();
    //阈值分割
    cv::threshold(srcImage_gray, srcImage_gray, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY);
    cv::findNonZero(srcImage_gray, location);
    float cntSize;
    cntSize = location.size();
    for(int k = 0; k < cntSize; k++){
        xStandard.push_back(location[k].x);
        yStandard.push_back(location[k].y);
    }
    //    xStandard.push_back(location);
    //    yStandard.push_back(location);
    //    std::cout<<"XStandard:"<<xStandard.at(x)<<std::endl;
    //    std::cout<<"YStandard:"<<yStandard.at(y)<<std::endl;
    //    cv::imwrite("/mnt/hgfs/VMsharedfiles/kmeansClasses4/0adaptiveImg/ImgNew_gray.gray",srcImage_gray);
}

void imageAdaptive(std::string srcPath,std::string destPath,std::vector<float> &xStandard,std::vector<float> &yStandard){
    int len = srcPath.length();
    std::vector<cv::String> filenames;
    string savedFileName;

    cv::glob(srcPath,filenames);
    Mat srcImage,srcImage_gray;
    std::vector<cv::Point> location;

    for(int i=0;i<filenames.size();i++)
    {
        srcImage=cv::imread(filenames[i],0);

        if(srcImage.channels()>1)
            cv::cvtColor(srcImage,srcImage_gray,cv::COLOR_BGR2GRAY);
        else
            srcImage_gray=srcImage.clone();
        //阈值分割
        //        cv::adaptiveThreshold(srcImage_3588_gray,srcImage_3588_gray,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,11,9);
        cv::threshold(srcImage_gray,srcImage_gray,0,255,cv::THRESH_OTSU|cv::THRESH_BINARY);
        cv::findNonZero(srcImage_gray,location);
        float cntSize;
        cntSize=location.size();
        for(int k=0;k<cntSize;k++){
            xStandard.push_back(location[k].x);
            yStandard.push_back(location[k].y);
        }

        //        savedFileName = destPath + filenames[i].substr(len);

        //        imwrite(savedFileName, srcImage_gray);

        //        xStandard.push_back(location);
        //        yStandard.push_back(location);
        //        std::cout<<"XStandard:"<<xStandard.at(x)<<std::endl;
        //        std::cout<<"YStandard:"<<yStandard.at(y)<<std::endl;
    }
}

void findNoneZero(cv::Mat binaryImage,std::vector<Point> location,std::vector<float>&xStandard,std::vector<float>&yStandard){
    //找到非零像素点的坐标位置
    cv::findNonZero(binaryImage,location);
    for(float i=0;i<location.size();i++){
        Point pnt = location[i];
        xStandard.push_back(pnt.x);
        yStandard.push_back(pnt.y);
    }
}
//int on_matching(std::string path, cv::Mat g_tempalteImage,cv::Mat g_resultImage)
//{
////    string savedFilenames;
////    int len = path.length();
//    std::vector<cv::String> filenames;
//    cv::glob(path,filenames);

//    for(int i=0;i<filenames.size();i++){
//        //待匹配的图
//        Mat g_srcImage;
//        //模板图
//        g_tempalteImage = imread("/mnt/hgfs/VMsharedfiles/kmeansClasses4/0cutting/35588-1-1-12.jpg",0);
//        if (!g_tempalteImage.data)
//        {
//            cout << "模板图读取失败" << endl;
//            return -1;
//        }
//        g_srcImage=imread(filenames[0],0);
////        g_srcImage.copyTo(srcImage);
//        int resultImage_cols = g_srcImage.cols - g_tempalteImage.cols + 1;
//        int resultImage_rows = g_srcImage.rows - g_tempalteImage.rows + 1;
//        g_resultImage.create(resultImage_cols, resultImage_rows, g_resultImage.type());
//        matchTemplate(g_srcImage, g_tempalteImage, g_resultImage, g_nMatchMethod);
//        normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
//        double minValue, maxValue;
//        Point minLocation, maxLocation, matchLocation;
//        minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation);
//    //    std::cout<<"minLocation:"<<minLocation<<std::endl;
//    //    std::cout<<"maxLocation:"<<maxLocation<<std::endl;
//        Rect rect(minLocation.x, minLocation.y,g_tempalteImage.cols,g_tempalteImage.rows);

//        int matchCenterX,matchCenterY;
//        matchCenterX=rect.x+rect.width/2;
//        matchCenterY=rect.y+rect.height/2;
//        std::cout<<"匹配后的中心坐标:("<<matchCenterX<<","<<matchCenterY<<")"<<std::endl;

//        int g_templateX,g_templateY;
//        g_templateX=2489+(1069/2);
//        g_templateY=2263+(653/2);
////    std::cout<<"匹配前的模板中心坐标:("<<(g_templateX)<<","<<(g_templateY)<<")"<<std::endl;


//    //模板与匹配后的中心差值
//        int g_distance = std::sqrt(((g_templateX-matchCenterX)*(g_templateX-matchCenterX))+
//                           ((g_templateY-matchCenterY)*(g_templateY-matchCenterY)));
//        std::cout<<"模板与匹配后的中心差值:"<<g_distance<<std::endl;

//        if(0<=g_distance<10)

////    模板图像的中心坐标
////    std::cout<<"rect.x:"<<rect.x<<std::endl;
////    std::cout<<"rect.y:"<<rect.y<<std::endl;
////    g_distance = std::sqrt(((g_templateX-g_matchX)*(g_templateX-g_matchX))+
////                           ((g_templateY-g_matchY)*(g_templateY-g_matchY)));
////    std::cout<<"distance:"<<g_distance<<std::endl;

//        if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED)
//        {
//            matchLocation = minLocation;
//        }
//        else
//        {
//            matchLocation = maxLocation;
//        }

//        rectangle(g_srcImage, matchLocation, Point(matchLocation.x + g_tempalteImage.cols,
//                                                 matchLocation.y + g_tempalteImage.rows), Scalar(0, 0, 255), 2, 8, 0);
//        rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_tempalteImage.cols,
//                                                 matchLocation.y + g_tempalteImage.rows), Scalar(0, 0, 255), 2, 8, 0);
//        //获取匹配部分的roi图像
//        Mat result_image = g_srcImage.clone();
//        Mat result_imageROI = result_image(rect);
//        imshow("ROI",result_imageROI);
//        imshow("原始图", g_srcImage);
//        imshow("效果图", g_resultImage);
//        }
//        return 0;
//}

/***********************************************************************
     *  @function CaptureTemplateImg
     *  @brief    根据最优模板，在原图像中截取图像
     *  @return
     ***********************************************************************/
void CaptureTemplateImg(int x0, int y0, int a, int b){
    double start = cv::getTickCount();
    //函数功能：根据最优的矩形模板长a和宽b进行模板匹配
    MatchTemplate matchtemplt;
    std::string srcImgpath,resultMatchImgpath;
    //待匹配图像的路径
    srcImgpath="/mnt/hgfs/VMsharedfiles/kmeansClasses/1-11/0RotationImg/";
    //模板匹配成功之后,匹配的图像保存路径
    resultMatchImgpath="/mnt/hgfs/VMsharedfiles/kmeansClasses/1-11/0ResultMatch/5/";
    //已选定的矩形模板图像
    //    cv::Rect rect=cv::Rect(990,607,1203-990,737-607);
    //    cv::Rect rect=cv::Rect(1230,751,141,213);
    cv::Rect rect=cv::Rect(x0, y0, a - x0, b - y0);
    cv::Mat src_modelImg;
    src_modelImg=cv::imread("/mnt/hgfs/VMsharedfiles/kmeansClasses/1-11/0RotationImg/43079-1-1-11.jpg",0);
    cv::Mat modelImg;
    modelImg=src_modelImg(rect);
    cv::Mat img_matchResult;
    //批量模板匹配,匹配成功保存的路径resultMatchImgpath
    matchtemplt.matchTemplateBatch(srcImgpath,modelImg,resultMatchImgpath,img_matchResult);

    double duration = (cv::getTickCount()-start)/ cv::getTickFrequency();
    std::cout<<"time:"<<duration<<std::endl;
}

/***********************************************************************
     *  @function GetOptimalTemplate
     *  @brief    获取最优模板
     *  @return
     ***********************************************************************/
void GetOptimalTemplate()
{
    //函数功能：匹配图像，计算最优模板长a和宽b
    MatchTemplate matchtemplt;
    std::string srcImgpath, resultMatchImgpath;
    //待匹配图像的路径
    srcImgpath = "classify5/0/srcImg/";
    //模板匹配成功之后,匹配的图像保存路径
    resultMatchImgpath = "classify5/0/matchedImg/";

    //已选定的矩形模板图像
    cv::Mat img_temp = imread("classify5/0/cutedImg/L1.png", 0);
    //随机生成模板图像像素位置起始点(左上角坐标)
    //根据人为给定范围(a1<a<a2,b1<b<b2范围)截取模板大小
    cv::Mat src_temp = cv::imread("classify5/0/srcImg/3785-4-11.jpg", 0);

    //    int min_x=952,max_x=1000;
    //    int min_y=580,max_y=615;
    //    int min_x=1200,max_x=1241;
    //    int min_y=741,max_y=773;
    //    int min_x=1200,max_x=1233;
    //    int min_y=1248,max_y=1280;

    int min_x = 909, max_x = 999;
    int min_y = 567, max_y = 648;

    float start = cv::getTickCount();

    std::vector<float> sValue;
    std::vector<float>::iterator minValue;
    #pragma omp parallel for num_threads(4)
    for(int x0 = min_x; x0 <= max_x; x0++)
    {
        for(int y0 = min_y; y0 <= max_y; y0++)
        {
            int a  = img_temp.cols + x0;
            int b  = img_temp.rows + y0;

            int aa = img_temp.cols;
            int bb = img_temp.rows;

            cv::Rect rect = cv::Rect(x0, y0, aa, bb);

            cv::Mat src_model;
            if(rect.x+rect.width > src_temp.cols || rect.y+rect.height > src_temp.rows)
            {
                std::cout << "截取的ROI尺寸不在图像内" << std::endl;
                continue;
            }
            else{
                src_model = src_temp(rect);
            }

            //留下月牙，没有月牙的模板不匹配
            //计算阈值
            cv::Mat src_gray;
            if(src_model.channels() > 1)
                cv::cvtColor(src_model,src_gray,cv::COLOR_BGR2GRAY);
            else
                src_gray = src_model.clone();
            cv::threshold(src_gray, src_gray, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY_INV);
            //计算面积(非零像素)
            int areaTh = cv::countNonZero(src_gray);
            cv::Mat src_modelImg;
            int area = GetArea(img_temp);

            if(areaTh <= (area + 20) && areaTh >= (area - 20))
            {
                cout << "template area:" << area << endl;
                std::cout << "a:" << a << std::endl;
                std::cout << "b:" << b << std::endl;
                std::cout << "模板起始坐标:(" << x0 << "," << y0 << ")"<<std::endl;
                std::cout << "area:" << areaTh << std::endl;
                src_modelImg = src_model.clone();
                cv::Mat img_matchResult;
                //批量模板匹配,匹配成功保存的路径resultMatchImgpath
                matchtemplt.matchTemplateBatch(srcImgpath, src_modelImg, resultMatchImgpath, img_matchResult);

                //批量计算
                std::vector<cv::String> fileNames;
                cv::glob(resultMatchImgpath, fileNames);
                std::vector<double> nn;
                std::vector<std::vector<double>> mm;
                for(int i = 0; i < fileNames.size(); i++)
                {
                    Mat frames;
                    frames=cv::imread(fileNames[i], 0);//读取文件夹下的每张图像

                    MatchTemplate matchTemp;
                    cv::Mat framesBinImg,img_tempBin;
                    //匹配的图像frames,矩形模板图像img_temp分别进行二值化
                    matchTemp.binaryImg(frames, framesBinImg);
                    matchTemp.binaryImg(src_modelImg, img_tempBin);
                    int n;
                    matchTemp.twoImgsCalcNonzero(framesBinImg, img_tempBin, n);
                    nn.push_back(n);
                }
                int total;
                total = std::accumulate(nn.begin(), nn.end(), 0);
                //计算均值
                int mean;
                mean = total/nn.size();
                std::cout << "mean:" << mean << std::endl;
                //计算方差
                int stdev;
                int accum = 0;
                for(int i = 0; i < nn.size(); i++) {
                    accum += ((nn[i]-mean)*(nn[i]-mean));
                }
                stdev=std::sqrt(accum/nn.size());
                std::cout<<"stdev Value:"<<stdev<<std::endl;
                //计算均值和方差的平方根
                float sqrtValue;
                sqrtValue=std::sqrt(pow(mean,2)+pow(stdev,2));
                sValue.push_back(sqrtValue);

                std::cout<<"sqrtValue:"<<sqrtValue<<std::endl;
                std::cout<<std::endl;
                //                    std::cout<<"sValue:"<<sValue[i]<<std::endl;
            }
        }
    }
    //find the minmum sqrtValue
    minValue=std::min_element(std::begin(sValue),std::end(sValue));
    std::cout<<"min sqrtValue:"<<*minValue<<std::endl;
    double duration = (cv::getTickCount()-start)/ cv::getTickFrequency();
    std::cout<<"time:"<<duration<<std::endl;
}

void test2(){

    cv::Mat img=cv::imread("/mnt/hgfs/VMsharedfiles/kmeansClasses4/0resultMatch/43079-1-6-11.jpg",0);
    cv::Mat imgModel=cv::imread("/mnt/hgfs/VMsharedfiles/kmeansClasses4/0model/model0.jpg",0);
    MatchTemplate matchTemp;
    cv::Mat resultBinImg,imgModelBin,resultMinus;
    matchTemp.binaryImg(img,resultBinImg);
    matchTemp.binaryImg(imgModel,imgModelBin);
    int n;
    matchTemp.twoImgsCalcNonzero(resultBinImg,imgModelBin,n);
}

void rotationImg(cv::Mat &imgStandard, cv::Mat &imgNew,cv::Mat &destImage)
{
    vector<float> x1,y1,x2,y2,resx,resy;
    FindOuterContour obj;
    obj.PeripheralTraversa(imgStandard,x1,y1);
    obj.PeripheralTraversa(imgNew,x2,y2);
    PointsMatch  objp;
    double thea,tx,ty,sxc,syc;
    objp.ICP(x2,y2,x1,y1,resx,resy,thea);
    objp.getTranslationVector(x2, y2,x1, y1, tx, ty,sxc,syc);
    Point2f center(imgNew.cols/2,imgNew.rows / 2);
    cv::Mat M = getRotationMatrix2D(center,thea/CV_PI*180*(-1), 1);
    warpAffine(imgNew, destImage, M, Size(imgNew.cols,imgNew.rows));
}

void test3()
{
    //函数功能:修正图像
    std::string imgNewPath = "/mnt/hgfs/VMsharedfiles/kmeansClasses/1-13/5";
    std::string destImgPath = "/mnt/hgfs/VMsharedfiles/kmeansClasses/1-13/5RationImg/";
    std::string savedFileNames;
    int len=imgNewPath.length();

    std::vector<cv::String> fileNames;
    cv::glob(imgNewPath,fileNames);

    cv::Mat imgStand;
    imgStand=cv::imread("/mnt/hgfs/VMsharedfiles/kmeansClasses/1-13/5/35588-1-3-13.jpg",0);
    for(int i=0;i<fileNames.size();i++)
    {
        cv::Mat framesImgNew;
        cv::Mat destImg;

        framesImgNew=cv::imread(fileNames[i],0);
        rotationImg(imgStand,framesImgNew,destImg);

        savedFileNames=destImgPath+fileNames[i].substr(len);
        cv::imwrite(savedFileNames,destImg);
    }
}

int main()
{
    // 获取最优模板
    GetOptimalTemplate();
    //    test3();
    //    根据最优模板在图像中抠图
//    CaptureTemplateImg();
    waitKey(0);
    return 0;
}
