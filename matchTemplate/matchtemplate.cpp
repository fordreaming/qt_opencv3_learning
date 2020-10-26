#include "matchtemplate.h"

using namespace cv;
using namespace std;
MatchTemplate::MatchTemplate()
{

}

int MatchTemplate::twoImgsCalcNonzero(cv::Mat binaryImg1,cv::Mat binaryImg2,int &n)
{
    //两幅相同尺寸大小、类型相同的二值图像进行相减,统计非零像素的个数
    cv::Mat diffBinaryImg;
    MatchTemplate::matrixMinus(binaryImg1, binaryImg2, diffBinaryImg);
    //    cv::imshow("nonZeroImg",diffBinaryImg);
    std::vector<cv::Point> locations;
    cv::findNonZero(diffBinaryImg, locations);
    n = locations.size();
    return n;
}

void MatchTemplate::matrixMinus(cv::Mat binaryImg1, cv::Mat binaryImg2,cv::Mat &resultImg)
{
    if(binaryImg1.size==binaryImg2.size)
        cv::absdiff(binaryImg1, binaryImg2, resultImg);//两幅相同尺寸大小、类型相同的图像进行相减
}

void MatchTemplate::matchTemplateBatch(std::string srcImgpath,cv::Mat tempImg,std::string resultpath,cv::Mat matchResult )
{
    std::string savedFileNames;
    int len=srcImgpath.length();
    //    std::vector<std::string> fileNames;
    std::vector<cv::String> fileNames;
    cv::glob(srcImgpath,fileNames);

    for(int i=0; i<fileNames.size();i++)
    {
        Mat frames;
        frames = imread(fileNames[i],0);
        //        frames = frames(Rect(564,565,295,185));
        //多目标匹配
        MatchTemplate::multimatch(frames,tempImg,matchResult);
        //将匹配结果保存在指定的文件路径
        savedFileNames = resultpath + fileNames[i].substr(len);
        imwrite(savedFileNames, matchResult);
    }
}

void MatchTemplate::binaryImg(Mat srcImg, Mat &binaryResultImg)
{
    //二值化
    cv::Mat srcGray;
    if(srcImg.channels() == 3){
        cv::cvtColor(srcImg,srcGray,cv::COLOR_BGR2GRAY);
    }else{
        srcGray = srcImg.clone();
    }
    cv::threshold(srcGray, binaryResultImg, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY);
}

void MatchTemplate::multimatch(cv::Mat img,cv::Mat img_temp,cv::Mat &img_matchResult)
{
    //调用函数检测
    vector<Point> P;//存储所有检测目标的坐标
    MatchTemplate matchTempl;
    if(img.empty()) {
        std::cout << "image empty" << std::endl;
    }
    matchTempl.GetAllMinLoc(img, img_temp, 0.01, Scalar(0,0,0), &P);
    //根据获取的全部坐标数据圈出待检测目标
    for (int k = 0; k < P.size(); k++)
    {
        Point loc = P[k];
        Rect rect=Rect(loc.x, loc.y, img_temp.cols, img_temp.rows);
        //获取匹配部分的roi图像
        Mat result_image = img.clone();
        rectangle(img, Rect(loc.x, loc.y, img_temp.cols, img_temp.rows), Scalar(0, 0, 255), 2, 8);
        Mat result_imageROI = result_image(rect);
        img_matchResult=result_imageROI.clone();
    }
}

void MatchTemplate::multimatch(cv::Mat img,cv::Mat img_temp)
{
    char *str_Input_Window_Title = "Read Image Window";
    char *str_Template_Window_Title = "Template Window";

    if (!img.data || !img_temp.data)//加载图像失败
    {
        printf("Fault to load image!\n\r");
        //        return -1;
    }
    imshow(str_Input_Window_Title, img);
    imshow(str_Template_Window_Title, img_temp);

    //调用函数检测
    vector<Point> P;//存储所有检测目标的坐标
    MatchTemplate matchTempl;
    matchTempl.GetAllMinLoc(img, img_temp, 0.2, Scalar(0,0,0), &P);
    //根据获取的全部坐标数据圈出待检测目标
    for (int k = 0; k < P.size(); k++)
    {
        Point loc = P[k];
        rectangle(img, Rect(loc.x, loc.y, img_temp.cols, img_temp.rows), Scalar(0, 0, 255), 2, 8);
        //获取匹配部分的roi图像
        Mat result_image = img.clone();
        Rect rect=Rect(loc.x, loc.y, img_temp.cols, img_temp.rows);
        Mat result_imageROI = result_image(rect);
        cv::imshow("result",result_imageROI);
        cv::imwrite("result.jpg",result_imageROI);
    }
    imshow("Match_Result Window", img);
    waitKey(0);
}

void MatchTemplate::GetAllMinLoc(Mat image, Mat templ, double sim, Scalar mask, vector<Point> *all_min_loc)
{
    /*
    *函数功能：基于matchTemplate函数检测原图像中所有的目标
    *参数说明：
    *         image：输入原图像
    *         templ：输入的模板图像
    *         sim:   相似度，0~1之间，越接近0越相似
    *         mask： 覆盖区颜色,一般情况下直接取黑色即可Scalar(0,0,0)
    *         *all_min_loc：所有匹配到的目标的坐标
    */
    bool test = true;
    int i=0;
    int src_Width = image.cols, src_Height=image.rows;
    int templ_Width=templ.cols, templ_Height=templ.rows;
    double min_value, max_value;
    Point min_Loc, max_Loc;
    Mat img_result(image.size(), CV_32FC1);
    Mat img_clon = image.clone();
    if (templ_Width > src_Width || templ_Height > src_Height)
    {
        printf("模板尺寸大于原图像，请选择正确的模板\n");
        exit;
    }
    while (1)
    {

        //        std::cout << "img clone type" << img_clon.type() << endl;
        //        std::cout << "temp img type" << templ.type() << endl;
        matchTemplate(img_clon, templ, img_result, TM_SQDIFF_NORMED);
        minMaxLoc(img_result, &min_value, &max_value, &min_Loc, &max_Loc);
        if (min_value < sim)//检测结果符合预期范围
        {
            all_min_loc->push_back(min_Loc);
            rectangle(img_clon, Rect(min_Loc.x, min_Loc.y, templ_Width, templ_Height), mask, -1);//掩盖检测到的第一块区域
            //            std::cout<<"find the object successfully"<<std::endl;
        }
        else break;
    }
}

void MatchTemplate::matchTemplateOne(cv::Mat srcImage,cv::Mat modelImage)
{
    /*
    srcImage:待匹配的图;
    modelImage:模板图
    两副图像进行匹配
    */
    //步骤一：创建一个空画布用来绘制匹配结果
    cv::Mat dstImg;
    dstImg.create(srcImage.dims,srcImage.size,srcImage.type());
//    cv::imshow("createImg",dstImg);

    //步骤二：匹配，最后一个参数为匹配方式，共有6种，详细请查阅函数介绍
    cv::matchTemplate(srcImage, modelImage, dstImg, 0);

    //步骤三：归一化图像矩阵，可省略
    cv::normalize(dstImg, dstImg, 0, 1, 32);

    //步骤四：获取最大或最小匹配系数
    //首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
    //找矩阵的最小位置的函数是 minMaxLoc函数
    cv::Point minPoint;
    cv::Point maxPoint;
    double *minVal = 0;
    double *maxVal = 0;
    cv::minMaxLoc(dstImg, minVal, maxVal, &minPoint,&maxPoint);

    //步骤五：开始正式绘制
    cv::rectangle(srcImage, minPoint, cv::Point(minPoint.x + modelImage.cols, minPoint.y + modelImage.rows), cv::Scalar(0,255,0), 2, 8);
    cv::imshow("【匹配后的图像】", srcImage);
    cv::rectangle(dstImg, minPoint, cv::Point(minPoint.x + modelImage.cols, minPoint.y + modelImage.rows), cv::Scalar(0,0,0), 3, 8);
    cv::imshow("【匹配后的计算过程图像】", dstImg);
    cv::waitKey(0);
}
