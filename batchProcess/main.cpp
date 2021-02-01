#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<string>

using namespace std;
using namespace cv;

//int main()
//{
//    string path = "/mnt/hgfs/VMsharedfiles/kmeansClasses4/0/";
//    string dest = "/mnt/hgfs/VMsharedfiles/kmeansClasses4/0cutting/";

//    string savedFileName;
//    int len = path.length();

//    vector<cv::String> filenames;

//    cv::glob(path, filenames);

//    for(int i=0; i<filenames.size();i++){
//        Mat frames;
//        frames = imread(filenames[i],0);
//        frames = frames(Rect(564,565,295,185));
//        savedFileName = dest + filenames[i].substr(len);
//        imwrite(savedFileName, frames);
//    }
//    cout << "Cutting images is successful!" << endl;
//    return 0;
//}
int main()
{

        cv::Mat srcImage;
        srcImage=cv::imread("/mnt/hgfs/VMsharedfiles/kmeansClasses/1-11/0ResultMatch/43079-1-8-11.jpg",0);
        cv::Mat srcImage_gray;

        //阈值分割
        if(srcImage.channels()>1)
            cv::cvtColor(srcImage,srcImage_gray,cv::COLOR_BGR2GRAY);
        else
            srcImage_gray=srcImage.clone();

        cv::threshold(srcImage_gray,srcImage_gray,0,255,cv::THRESH_OTSU|cv::THRESH_BINARY_INV);
        int areaTh=cv::countNonZero(srcImage_gray);
        cv::imshow("threshold_Img",srcImage_gray);
        std::cout<<"area threshold:"<<areaTh<<std::endl;
        waitKey(0);
        return 0;

}
