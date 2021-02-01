#include "findcircle.h"
#include <gsl/gsl_sys.h>

FindCircle::FindCircle()
{
    cnt =0;
    cnt2=0;
    m_thrend     = 70;
    m_innerRadius= 0;
    m_outerRadius= 0;
    m_center.x = 0;
    m_center.y = 0;
    m_center2.x=0;
    m_center2.y=0;
    innerptVec.clear();
    outerptVec.clear();
}

FindCircle::~FindCircle()
{
    innerptVec.clear();
    outerptVec.clear();
    cnt =0;
    cnt2=0;
    m_thrend     =70;
    m_innerRadius=0;
    m_outerRadius=0;
    m_center.x=0;
    m_center.y=0;
    m_center2.x=0;
    m_center2.y=0;
}

void FindCircle::getShapeRecognition(float circleRate, int &res)
{
    float thred=circleRate;
    if(innerptVec.size() <= 24 || outerptVec.size() <= 24){
        res = -1;
        return ;
    }
    int nn[2] = {5, 6};
    vector<vector<float>> angleVec;
    vector<float> mv;
    angleVec.resize(2);
    for(int k = 0; k < 2; k++)
    {
        for(int i = 0; i < innerptVec.size()-2*nn[k];i += nn[k])
        {
            cv::Point2f v1,v2;
            v1.x=innerptVec[(i+nn[k])].x-innerptVec[i].x;
            v1.y=innerptVec[(i+nn[k])].y-innerptVec[i].y;
            v2.x=innerptVec[(i+2*nn[k])].x-innerptVec[(i+nn[k])].x;
            v2.y=innerptVec[(i+2*nn[k])].y-innerptVec[(i+nn[k])].y;
            if(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y)==0.0)continue;
            angleVec[k].push_back(acos((v1.x*v2.x+v1.y*v2.y)/(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y))));
        }
        mv.push_back(*max_element(angleVec[k].begin(),angleVec[k].end()));
    }

    *max_element(mv.begin(), mv.end()) > thred ? res = -1 : res = 1;
}

void FindCircle::getShapeRecognition0(int &type, float circleRate,int &res )
{
    float thred=circleRate;
    if(innerptVec.size()==0||outerptVec.size()==0){res=-1;return;}
    int nn[2]={5,6};

    vector<vector<float>> angleVec;
    vector<float> mv;
    angleVec.resize(2);
    if(type == 0)
    {
        for(int k=0;k<2;k++)
        {
            for(int i=0;i<innerptVec.size()-2*nn[k];i+=nn[k])
            {
               float thr0=i*CV_PI/180,thr1=(i+nn[k])*CV_PI/180,thr2=(i+2*nn[k])*CV_PI/180;
               if((thr0>=0&&thr0<=0.3142)||(thr0>=1.2566&&thr0<=1.8850)||(thr0>=2.8274&&thr0<=3.4558)||(thr0>= 4.3982&&thr0<=4.9306)||(thr0>=5.9690&&thr0<=2*CV_PI)
                       ||(thr1>=0&&thr1<=0.3142)||(thr1>=1.2566&&thr1<=1.8850)||(thr1>=2.8274&&thr1<=3.4558)||(thr1>= 4.3982&&thr1<=5.0265)||(thr1>=5.9690&&thr1<=2*CV_PI)
                       ||(thr2>=0&&thr2<=0.3142)||(thr2>=1.2566&&thr2<=1.8850)||(thr2>=2.8274&&thr2<=3.4558)||(thr2>= 4.3982&&thr2<=5.0265)||(thr2>=5.9690&&thr2<=2*CV_PI))//475
                    continue;
                cv::Point2f v1,v2;
                v1.x=innerptVec[(i+nn[k])].x-innerptVec[i].x;
                v1.y=innerptVec[(i+nn[k])].y-innerptVec[i].y;
                v2.x=innerptVec[(i+2*nn[k])].x-innerptVec[(i+nn[k])].x;
                v2.y=innerptVec[(i+2*nn[k])].y-innerptVec[(i+nn[k])].y;
                if(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y)==0.0)continue;
                angleVec[k].push_back(acos((v1.x*v2.x+v1.y*v2.y)/(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y))));
            }
            if(isnan(*max_element(angleVec[k].begin(),angleVec[k].end()))) {
                mv.push_back(10);
            }
            else {
                mv.push_back(*max_element(angleVec[k].begin(),angleVec[k].end()));
            }
        }
        *max_element(mv.begin(),mv.end())>thred?res=-1:res=1;
    }
    if(type==1)
    {
        for(int k=0;k<2;k++)
        {
            for(int i=0;i<innerptVec.size()-2*nn[k];i+=nn[k])
            {
               float thr0=i*CV_PI/180,thr1=(i+nn[k])*CV_PI/180,thr2=(i+2*nn[k])*CV_PI/180;
               if((thr0>=0&&thr0<=0.3142)||(thr0>=1.2566&&thr0<=1.8850)||(thr0>=2.8274&&thr0<=3.4558)||(thr0>= 4.3982&&thr0<=4.9306)||(thr0>=5.9690&&thr0<=2*CV_PI)
                       ||(thr1>=0&&thr1<=0.3142)||(thr1>=1.2566&&thr1<=1.8850)||(thr1>=2.8274&&thr1<=3.4558)||(thr1>= 4.3982&&thr1<=5.0265)||(thr1>=5.9690&&thr1<=2*CV_PI)
                       ||(thr2>=0&&thr2<=0.3142)||(thr2>=1.2566&&thr2<=1.8850)||(thr2>=2.8274&&thr2<=3.4558)||(thr2>= 4.3982&&thr2<=5.0265)||(thr2>=5.9690&&thr2<=2*CV_PI))//475
                    continue;
                cv::Point2f v1,v2;
                v1.x=innerptVec[(i+nn[k])].x-innerptVec[i].x;
                v1.y=innerptVec[(i+nn[k])].y-innerptVec[i].y;
                v2.x=innerptVec[(i+2*nn[k])].x-innerptVec[(i+nn[k])].x;
                v2.y=innerptVec[(i+2*nn[k])].y-innerptVec[(i+nn[k])].y;
                if(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y)==0.0)continue;
                angleVec[k].push_back(acos((v1.x*v2.x+v1.y*v2.y)/(gsl_hypot(v1.x,v1.y)*gsl_hypot(v2.x,v2.y))));
            }
        if(isnan(*max_element(angleVec[k].begin(),angleVec[k].end()))==true)mv.push_back(10);
        else mv.push_back(*max_element(angleVec[k].begin(),angleVec[k].end()));
        }
        *max_element(mv.begin(),mv.end())>thred?res=-1:res=1;
    }
}

void FindCircle::getConcentricRoi(cv::Mat &srcImg,vector<vector<int>> &resVec)
{
    //    float innerRadius;cv::Point center;
    //    getinnerRadiusAndcenter(srcImg,innerRadius,center);
    //    vector<float> detaRadiusVec,sumVec;
    //    detaRadiusVec.resize(80),sumVec.resize(80);
    //    iota(detaRadiusVec.begin(),detaRadiusVec.end(),60);
    //    float step=0.5;
    ////#pragma omp parallel for num_threads(ALGORITHM_THREAD_NUM)
    //    for(int i=0;i<int(detaRadiusVec.size());i++)
    //    {
    //        m_outerRadius=innerRadius+detaRadiusVec[i];
    //        for(float x=(center.x-m_outerRadius);x<(center.x+m_outerRadius);x+=step)
    //        {
    //            float y1=center.y+sqrt(m_outerRadius*m_outerRadius-(x-center.x)*(x-center.x));
    //            float y2=center.y-sqrt(m_outerRadius*m_outerRadius-(x-center.x)*(x-center.x));
    //            if(srcImg.at<uchar>(int(y1),int(x))<m_thrend&&srcImg.at<uchar>(int(y2),int(x))<m_thrend)
    //            sumVec[i]+=1.0;
    ////            sumVec[i]+=float(srcImg.at<uchar>(int(y1),int(x)));
    ////            sumVec[i]+=float(srcImg.at<uchar>(int(y2),int(x)));
    //        }
    //    }
    ////    vector<float>::iterator minnest = min_element(sumVec.begin(), sumVec.end());
    ////    int minId = distance(sumVec.begin(), minnest);
    //    vector<float>::iterator maxest = max_element(sumVec.begin(), sumVec.end());
    //    int minId = distance(sumVec.begin(), maxest);
    //    m_outerRadius=innerRadius+detaRadiusVec[minId];
    float innerRadius,outerRadius;cv::Point center,c1,c2;
    getinnerouterRadiusAndcenter(srcImg,innerRadius,outerRadius,c1,c2);
    center.x=(c1.x+c2.x)/2,center.y=(c1.y+c2.y)/2;
    int flag=0;
    cv::Point cerqs;
    cerqs.y=center.y,cerqs.x=center.x+(outerRadius+innerRadius)/2;
    resVec.resize(srcImg.rows);
    for(int i=0;i<srcImg.rows;i++)
        resVec[i].resize(srcImg.cols);
    cv::Mat dstImg=srcImg.clone();
    for(int i=0;i<srcImg.rows;i++)
    {
        for(int j=0;j<srcImg.cols;j++)
        {
            float dis=sqrt((i-center.y)*(i-center.y)+(j-center.x)*(j-center.x));
            if(dis>innerRadius&&dis<outerRadius)
            {
                resVec[i][j]=int(srcImg.at<uchar>(i,j));
                dstImg.at<uchar>(i,j)=srcImg.at<uchar>(i,j);
            }
            else
            {
                resVec[i][j]=-1;
                dstImg.at<uchar>(i,j)=0;
            }
        }
    }

    //        int rr=0;
    //        getShapeRecognition(rr);
    //        cout<<"rr: "<<rr<<endl;
    //      for(int i=0;i<innerptVec.size();i++)
    //     {     circle(srcImg,innerptVec[i],3,CV_RGB(255,255,255),2,8,0);
    //          circle(srcImg,outerptVec[i],3,CV_RGB(255,255,255),2,8,0);}

    //      circle(srcImg,c1,innerRadius,CV_RGB(255,255,255),2,8,0);
    //imwrite("/home/qzs/DataFile/WyData/0/cdc.jpg",srcImg);
    //    circle(srcImg,center,m_outerRadius,CV_RGB(255,255,255),2,8,0);
    //    circle(dstImg,center,10,CV_RGB(0,0,255),2,8,0);
    //    cout<<"center:"<<center.x<<" "<<center.y<<" "<<"innerRadius: "<<innerRadius<<"  outerRadius: "<< m_outerRadius<<endl;
    //    imwrite("/home/qzs/DataFile/WyData/0/cd.jpg",dstImg);

}

void FindCircle::getPredictResult1(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res)
{

    float innerRadius,outerRadius;cv::Point center,c1,c2;
    getinnerouterRadiusAndcenter(srcImg,innerRadius,outerRadius,c1,c2);
    if(c1.x == 0||c2.x == 0)
    {
        res = -1;
        return;
    }
    int rr = 0;
    getShapeRecognition(circleRate,rr);
    if(rr == -1)
    {
        res=-1;
        return ;
    }
    center.x=(c1.x+c2.x)/2,center.y=(c1.y+c2.y)/2;
    int flag=0;
    cv::Point cerqs;
    cerqs.y=center.y,cerqs.x=center.x+(outerRadius+innerRadius)/2;

    int nn=0;
    for(float thr=0;thr<2*CV_PI;thr+=(CV_PI/180))
    {
        cv::Point certmp;
        float rd=(outerRadius-innerRadius)/2*0.9;
        if(innerptVec[nn].x==0||outerptVec[nn].x==0||innerptVec[nn].y==0||outerptVec[nn].y==0){
            nn++;
            continue;
        }
        float rds=sqrt((innerptVec[nn].x-outerptVec[nn].x)*(innerptVec[nn].x-outerptVec[nn].x)+
                       (innerptVec[nn].y-outerptVec[nn].y)*(innerptVec[nn].y-outerptVec[nn].y));
        if(abs(rds/2*0.9-rd)>150)
        {
            certmp.x=center.x+(cerqs.x-center.x)*cos(-thr)-(cerqs.y-center.y)*sin(-thr);
            certmp.y=center.y+(cerqs.y-center.y)*cos(-thr)+(cerqs.x-center.x)*sin(-thr);
        }
        else
        {
            certmp.x=(innerptVec[nn].x+outerptVec[nn].x)/2;
            certmp.y=(innerptVec[nn].y+outerptVec[nn].y)/2;
            rd=rds/2*0.9;
        }
        nn++;
        if(nn==360)break;
        float area0=0.0,area1=0.0;
        for(int i=int(certmp.x-rd);i<int(certmp.x+rd);i++)
        {
            for(int j=int(certmp.y-rd);j<int(certmp.y+rd);j++)
            {
                float dis=sqrt((i-certmp.x)*(i-certmp.x)+(j-certmp.y)*(j-certmp.y));
                if(dis<=rd&&srcImg.at<uchar>(j,i)<thresholdLow)
                {
                    area0+=1.0;
                }
                if(dis<=rd&&srcImg.at<uchar>(j,i)>thresholdHight)
                {
                    area1+=1.0;
                }
            }
        }

        if(area0 > area)
        {
            res=-1;
            flag=-1;
            break;
        }
    }

    flag==-1?res=-1:res=1;

}

void FindCircle::getPredictResult0(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res)
{
    float innerRadius,outerRadius;cv::Point center,c1,c2;
    getinnerouterRadiusAndcenter(srcImg,innerRadius,outerRadius,c1,c2);
    if(c1.x==0||c2.x==0)
    {
        res=-1;
        return;
    }
    int rr=0;
    getShapeRecognition0(type,circleRate,rr);
    if(rr==-1)
    {
        res=-1;
        return ;
    }
    center.x=(c1.x+c2.x)/2,center.y=(c1.y+c2.y)/2;
    int flag=0;
    cv::Point cerqs;
    cerqs.y=center.y,cerqs.x=center.x+(outerRadius+innerRadius)/2;
    int nn=0;
    for(float thr=0;thr<2*CV_PI;thr+=(CV_PI/180))
    {
        cv::Point certmp;
        float rd=(outerRadius-innerRadius)/2*0.9;
        if(innerptVec[nn].x == 0 || outerptVec[nn].x == 0 || innerptVec[nn].y == 0 || outerptVec[nn].y == 0) {
            nn++;
            continue;
        }
        float rds=sqrt((innerptVec[nn].x-outerptVec[nn].x)*(innerptVec[nn].x-outerptVec[nn].x)+
                       (innerptVec[nn].y-outerptVec[nn].y)*(innerptVec[nn].y-outerptVec[nn].y));
        if(abs(rds/2*0.9-rd)>150)
        {
            certmp.x=center.x+(cerqs.x-center.x)*cos(-thr)-(cerqs.y-center.y)*sin(-thr);
            certmp.y=center.y+(cerqs.y-center.y)*cos(-thr)+(cerqs.x-center.x)*sin(-thr);
        }
        else
        {
            certmp.x=(innerptVec[nn].x+outerptVec[nn].x)/2;
            certmp.y=(innerptVec[nn].y+outerptVec[nn].y)/2;
            rd=rds/2*0.9;
        }
        nn++;
        if(nn==360)break;
        float area0=0.0,area1=0.0;
        for(int i=int(certmp.x-rd);i<int(certmp.x+rd);i++)
        {
            for(int j=int(certmp.y-rd);j<int(certmp.y+rd);j++)
            {
                float dis=sqrt((i-certmp.x)*(i-certmp.x)+(j-certmp.y)*(j-certmp.y));
                if(dis<=rd&&srcImg.at<uchar>(j,i)<thresholdLow)
                {
                    area0+=1.0;
                }
                if(dis<=rd&&srcImg.at<uchar>(j,i)>thresholdHight)
                {
                    area1+=1.0;
                }
            }
        }
        //        circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
        //        imwrite("/home/qzs/DataFile/WyData/0/cd22.jpg",srcImg);
        //if((thr>=0&&thr<=0.349691)||(thr>=1.149924&&thr<=1.920126)||(thr>=2.727751&&thr<=3.513302)||(thr>=4.333538&&thr<=5.092488)||(thr>=5.871514&&thr<=2*CV_PI))
        //if((thr>=0&&thr<=0.2105)||(thr>=1.3205&&thr<=1.7433)||(thr>=2.8807&&thr<=3.3904)||(thr>= 4.4947&&thr<=4.9494)||(thr>=6.0314&&thr<=2*CV_PI))//452

        //if((thr>=0&&thr<=0.212998)||(thr>=1.419495&&thr<=1.811531)||(thr>=2.965470&&thr<=3.363871)||(thr>= 4.485908&&thr<=4.865857)||(thr>=6.061318&&thr<=2*CV_PI))//475
        if(type==0&&((thr>=0&&thr<=0.2105)||(thr>=1.3205&&thr<=1.7433)||(thr>=2.8807&&thr<=3.3904)||(thr>= 4.4947&&thr<=4.9494)||(thr>=6.0314&&thr<2*CV_PI)))//452
        {
            //if(area0>area*3||area1>area*3)
            if(srcImg.at<uchar>(certmp.y,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y-2,certmp.x+2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x+2)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y+2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x+2)<thresholdLow)
            {
                res=-1;
                flag=-1;
                //circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
                //imwrite("/home/qzs/DataFile/WyData/0/cd2.jpg",srcImg);
                break;
            }
            if(area0>area*2)
            {
                res=-1;
                flag=-1;
                //circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
                //imwrite("/home/qzs/DataFile/WyData/0/cd2.jpg",srcImg);
                break;
            }
        }
        else
        {
            //if(area0>area||area1>area)
            if(area0>area&&type==0)
            {
                res=-1;
                flag=-1;
                //circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
                //imwrite("/home/qzs/DataFile/WyData/0/cd2.jpg",srcImg);
                break;
            }
        }

        if(type==1&&((thr>=0&&thr<=0.212998)||(thr>=1.419495&&thr<=1.811531)||(thr>=2.965470&&thr<=3.363871)||(thr>= 4.485908&&thr<=4.865857)||(thr>=6.061318&&thr<=2*CV_PI)))//475
        {
            //if(area0>area*3||area1>area*3)
            if(srcImg.at<uchar>(certmp.y,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y-2,certmp.x+2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x+2)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y+2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x+2)<thresholdLow)
            {
                res=-1;
                flag=-1;
                //circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
                //imwrite("/home/qzs/DataFile/WyData/0/cd2.jpg",srcImg);
                break;
            }
            if(area0>area*3.3)
            {
                res=-1;
                flag=-1;
                //circle(srcImg,certmp,rd,CV_RGB(0,0,255),2,8,0);
                //imwrite("/home/qzs/DataFile/WyData/0/cd2.jpg",srcImg);
                break;
            }
        }
        else
        {
            if(area0>area&&type==1)
            {
                res=-1;
                flag=-1;
                break;
            }
        }

    }
    flag==-1?res=-1:res=1;

}

void FindCircle::getPredictResult2(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type,float &circleRate,int &res)
{
    float innerRadius,outerRadius;cv::Point center,c1,c2;
    getinnerouterRadiusAndcenter(srcImg,innerRadius,outerRadius,c1,c2);
    if(c1.x==0||c2.x==0)
    {
        res=-1;
        return;
    }
    int rr=0;
    getShapeRecognition(circleRate,rr);
    if(rr==-1)
    {
        res=-1;
        return ;
    }
    center.x=(c1.x+c2.x)/2,center.y=(c1.y+c2.y)/2;
    int flag=0;
    cv::Point cerqs;
    cerqs.y=center.y,cerqs.x=center.x+(outerRadius+innerRadius)/2;
    int nn=0;
    for(float thr=0;thr<2*CV_PI;thr+=(CV_PI/180))
    {
        cv::Point certmp;
        float rd=(outerRadius-innerRadius)/2*0.9;
        if(innerptVec[nn].x == 0 || outerptVec[nn].x == 0 || innerptVec[nn].y == 0 || outerptVec[nn].y == 0) {
            nn++;
            continue;
        }
        float rds=sqrt((innerptVec[nn].x-outerptVec[nn].x)*(innerptVec[nn].x-outerptVec[nn].x)+
                       (innerptVec[nn].y-outerptVec[nn].y)*(innerptVec[nn].y-outerptVec[nn].y));
        if(abs(rds/2*0.9-rd)>150)
        {
            certmp.x=center.x+(cerqs.x-center.x)*cos(-thr)-(cerqs.y-center.y)*sin(-thr);
            certmp.y=center.y+(cerqs.y-center.y)*cos(-thr)+(cerqs.x-center.x)*sin(-thr);
        }
        else
        {
            certmp.x=(innerptVec[nn].x+outerptVec[nn].x)/2;
            certmp.y=(innerptVec[nn].y+outerptVec[nn].y)/2;
            rd=rds/2*0.9;
        }
        nn++;
        if(nn==360)break;
        float area0=0.0, area1=0.0;
        for(int i = int(certmp.x - rd); i < int(certmp.x+rd); i++)
        {
            for(int j=int(certmp.y-rd);j<int(certmp.y+rd);j++)
            {
                float dis=sqrt((i-certmp.x)*(i-certmp.x)+(j-certmp.y)*(j-certmp.y));
                if(dis<=rd&&srcImg.at<uchar>(j,i)<thresholdLow)
                {
                    area0+=1.0;
                }
                if(dis<=rd&&srcImg.at<uchar>(j,i)>thresholdHight)
                {
                    area1+=1.0;
                }
            }
        }
        if(thr>=4.183047&&thr<=5.191337&&type==0)
        {
            //if(area0>area*4||area1>area*4)
            if(srcImg.at<uchar>(certmp.y,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y-2,certmp.x)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y-2,certmp.x+2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y,certmp.x+2)<thresholdLow
                    &&srcImg.at<uchar>(certmp.y+2,certmp.x-2)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x)<thresholdLow&&srcImg.at<uchar>(certmp.y+2,certmp.x+2)<thresholdLow)
            {
                res=-1;
                flag=-1;
                break;
            }
            if(area0>area/2)
            {
                res=-1;
                flag=-1;
                break;
            }
        }
        else
        {
            if(area0>area)
            {
                res=-1;
                flag=-1;
                break;
            }
        }
    }

    flag==-1?res=-1:res=1;

}

void FindCircle::getPredictResult(cv::Mat &srcImg, float &thresholdLow, float &thresholdHight,float &area,int &type, int &flag,float &circleRate,int &res)
{
    if(flag==0) {
        getPredictResult0(srcImg, thresholdLow, thresholdHight, area, type, circleRate, res);
    }

    if(flag==1) {
        getPredictResult1(srcImg, thresholdLow, thresholdHight, area, type, circleRate, res);
    }

    if(flag==2) {
        getPredictResult2(srcImg, thresholdLow, thresholdHight, area, type, circleRate, res);
    }
}


void FindCircle::getInnerOuterCirclePointSet(cv::Mat &srcImg,std::vector<cv::Point> &pointVec,std::vector<cv::Point> &pointVec2)
{
    float rthd=200;
    uchar uz=m_thrend;
    Point fc;
    fc.x=srcImg.cols/2,fc.y=srcImg.rows/2;
    vector<float> thrVec;
    //iota(thrVec.begin(),thrVec.end(),CV_PI/180);
    for(int i=0;i<360;i++)
    {
        thrVec.push_back(float(i)*CV_PI/180);
    }
    pointVec.resize(thrVec.size());
    pointVec2.resize(thrVec.size());
    vector<int> cntVec, cntVec2;
    cntVec.resize(8);
    cntVec2.resize(8);
    float step=0.5,nstp=6;
#pragma omp parallel for num_threads(OMP_PARALLEL_THREAD_NUM)
    for(int i=0;i<int(thrVec.size());i++)
    {
        if(i<=45)
        {
            for(float x=fc.x;x<float(srcImg.cols);x+=step)
            {
                float y=tan(thrVec[i])*(x-fc.x)+fc.y;
                if(y>=srcImg.rows-10*step || x>=(float(srcImg.cols)-10*step))
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[0]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float x2=x+nstp*step;x2<float(srcImg.cols);x2+=step)
                    {
                        float y2=tan(thrVec[i])*(x2-fc.x)+fc.y;
                        if(y2>=srcImg.rows-10*step || x2>=(float(srcImg.cols)-10*step))
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[0]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(i>45&&i<=90)
        {
            for(float y=fc.y;y<float(srcImg.rows);y+=step)
            {
                float x=tan(CV_PI/2-thrVec[i])*(y-fc.y)+fc.x;
                if(x>=srcImg.cols-10*step || y>=(float(srcImg.rows)-10*step))
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[1]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float y2=y+nstp*step;y2<float(srcImg.rows);y2+=step)
                    {
                        float x2=tan(CV_PI/2-thrVec[i])*(y2-fc.y)+fc.x;
                        if(x2>=srcImg.cols-10*step || y2>=(float(srcImg.rows)-10*step))
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[1]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }


        if(i>90&&i<=135)
        {
            for(float y=fc.y;y<float(srcImg.rows);y+=step)
            {
                float x=fc.x-tan(thrVec[i]-CV_PI/2)*(y-fc.y);
                if(x<=10*step || y>=(float(srcImg.rows)-10*step))
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[2]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float y2=y+nstp*step;y2<float(srcImg.rows);y2+=step)
                    {
                        float x2=fc.x-tan(thrVec[i]-CV_PI/2)*(y2-fc.y);
                        if(x2>=srcImg.cols-10*step || y2>=(float(srcImg.rows)-10*step))
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[2]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }


        if(i>135&&i<=180)
        {
            for(float x=fc.x;x>0;x-=step)
            {
                float y=tan(CV_PI-thrVec[i])*(fc.x-x)+fc.y;
                if(y>=srcImg.rows-10*step || x<=10*step)
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[3]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float x2=x-nstp*step;x2>0;x2-=step)
                    {
                        float y2=tan(CV_PI-thrVec[i])*(fc.x-x2)+fc.y;
                        if(y2>=srcImg.rows-10*step || x2<=10*step)
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[3]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(i>180&&i<=225)
        {
            for(float x=fc.x;x>0;x-=step)
            {
                float y=fc.y-tan(thrVec[i]-CV_PI)*(fc.x-x);
                if(y<=10*step || x<=10*step)
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[4]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float x2=x-nstp*step;x2>0;x2-=step)
                    {
                        float y2=fc.y-tan(thrVec[i]-CV_PI)*(fc.x-x2);
                        if(y2<10*step || x2<=10*step)
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[4]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(i>225&&i<=270)
        {
            for(float y=fc.y;y>0;y-=step)
            {
                float x=fc.x-tan(CV_PI*3/2-thrVec[i])*(fc.y-y);
                if(x<=10*step || y<=10*step)
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[5]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float y2=y-nstp*step;y2>0;y2-=step)
                    {
                        float x2=fc.x-tan(CV_PI*3/2-thrVec[i])*(fc.y-y2);
                        if(x2<=10*step || y2<=10*step)
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[5]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        if(i>270&&i<315)
        {
            for(float y=fc.y;y>0;y-=step)
            {
                float x=fc.x+tan(thrVec[i]-CV_PI*3/2)*(fc.y-y);
                if(x>=float(srcImg.cols)-10*step || y<=10*step)
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[6]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float y2=y-nstp*step;y2>0;y2-=step)
                    {
                        float x2=fc.x+tan(thrVec[i]-CV_PI*3/2)*(fc.y-y2);
                        if(x2>=float(srcImg.cols)-10*step || y2<=10*step)
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[6]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(i>=315&&i<360)
        {
            for(float x=fc.x;x<float(srcImg.cols);x+=step)
            {
                float y=fc.y-tan(2*CV_PI-thrVec[i])*(x-fc.x);
                if(y<=10*step || x>=float(srcImg.cols)-step)
                {
                    pointVec[i].x=0;
                    pointVec[i].y=0;
                    cntVec[7]++;
                    break;
                }
                if(srcImg.at<uchar>(int(y),int(x))>=uz&&sqrt((y-fc.y)*(y-fc.y)+(x-fc.x)*(x-fc.x))<rthd)continue;
                if(srcImg.at<uchar>(int(y),int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)-1)<uz||srcImg.at<uchar>(int(y)-1,int(x))<uz||srcImg.at<uchar>(int(y)-1,int(x)+1)<uz
                        ||srcImg.at<uchar>(int(y),int(x)-1)<uz||srcImg.at<uchar>(int(y),int(x)+1)<uz||srcImg.at<uchar>(int(y)+1,int(x)-1)<uz||srcImg.at<uchar>(int(y)+1,int(x))<uz||srcImg.at<uchar>(int(y)+1,int(x)+1)<uz)
                {
                    continue;
                }
                else
                {
                    pointVec[i].x=int(x);
                    pointVec[i].y=int(y);
                    for(float x2=x+nstp*step;x2<float(srcImg.cols);x2+=step)
                    {
                        float y2=fc.y-tan(2*CV_PI-thrVec[i])*(x2-fc.x);
                        if(y2<=10*step || x2>=float(srcImg.cols)-10*step)
                        {
                            pointVec2[i].x=0;
                            pointVec2[i].y=0;
                            cntVec2[7]++;
                            break;
                        }
                        if(srcImg.at<uchar>(int(y2),int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)-1,int(x2))>uz||srcImg.at<uchar>(int(y2)-1,int(x2)+1)>uz
                                ||srcImg.at<uchar>(int(y2),int(x2)-1)>uz||srcImg.at<uchar>(int(y2),int(x2)+1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2)-1)>uz||srcImg.at<uchar>(int(y2)+1,int(x2))>uz||srcImg.at<uchar>(int(y2)+1,int(x2)+1)>uz)
                        {
                            continue;
                        }
                        else
                        {
                            pointVec2[i].x=int(x2);
                            pointVec2[i].y=int(y2);
                            break;
                        }
                    }
                    break;
                }
            }
        }

    }
    cnt=accumulate(cntVec.begin(),cntVec.end(),0);
    cnt2=accumulate(cntVec2.begin(),cntVec2.end(),0);
    innerptVec=pointVec;
    outerptVec=pointVec2;

    //        ofstream fout1("1.txt"),fout2("2.txt");
    //        for(int i=0;i<int(pointVec.size());i++)
    //        {
    //            fout1<<pointVec[i].x<<" "<<pointVec[i].y<<endl;
    //        }
    //        for(int i=0;i<int(pointVec2.size());i++)
    //        {
    //            fout2<<pointVec2[i].x<<" "<<pointVec2[i].y<<endl;
    //        }
    //        fout1.close(),fout2.close();

}


void FindCircle::getinnerouterRadiusAndcenter(cv::Mat &srcImg,float &innerRadius,float &outerRadius,cv::Point &innercenter,cv::Point &outercenter)
{
    innerptVec.clear(),outerptVec.clear();
    std::vector<cv::Point> innerpointVec,outerpointVec;
    getInnerOuterCirclePointSet(srcImg,innerpointVec,outerpointVec);
    innercenter.x=0,innercenter.y=0,innerRadius=0.0,outercenter.x=0,outercenter.y=0,outerRadius=0.0;
    for(int i=0;i<int(innerpointVec.size());i++)
    {
        innercenter.x+=innerpointVec[i].x;
        innercenter.y+=innerpointVec[i].y;
    }
    for(int i=0;i<int(outerpointVec.size());i++)
    {
        outercenter.x+=outerpointVec[i].x;
        outercenter.y+=outerpointVec[i].y;
    }
    if(outercenter.x==0||innercenter.x==0)
    {
        return;
    }
    innercenter.x/=int(innerpointVec.size()-cnt),innercenter.y/=int(innerpointVec.size()-cnt);
    outercenter.x/=int(outerpointVec.size()-cnt2),outercenter.y/=int(outerpointVec.size()-cnt2);

    for(int i=0;i<int(innerpointVec.size());i++)
    {
        if(innerpointVec[i].x==0&&innerpointVec[i].y==0)continue;
        innerRadius+=sqrt((innerpointVec[i].x-innercenter.x)*(innerpointVec[i].x-innercenter.x)+(innerpointVec[i].y-innercenter.y)*(innerpointVec[i].y-innercenter.y));
    }
    innerRadius/=float(innerpointVec.size()-cnt);
    m_innerRadius=innerRadius,m_center=innercenter;

    for(int i=0;i<int(outerpointVec.size());i++)
    {
        if(outerpointVec[i].x==0&&outerpointVec[i].y==0)continue;
        outerRadius+=sqrt((outerpointVec[i].x-outercenter.x)*(outerpointVec[i].x-outercenter.x)+(outerpointVec[i].y-outercenter.y)*(outerpointVec[i].y-outercenter.y));
    }
    outerRadius/=float(outerpointVec.size()-cnt2);
    m_outerRadius=outerRadius,m_center2=outercenter;
}
