#ifndef TESTCASES_H
#define TESTCASES_H

#include "common.h"
#include "imageproc.h"

class TestCases
{
public:
    TestCases();
    /***********************************************************************
     *  @function GenerateBinaryImgTestCase
     *  @brief    image binary
     *  @return
     ***********************************************************************/
    static void GenerateBinaryImgTestCase();

    /***********************************************************************
     *  @function FindOptimalTemplateTestCase
     *  @brief
     *  @return
     ***********************************************************************/
    static void FindOptimalTemplateTestCase();

    /***********************************************************************
     *  @function
     *  @brief    capture optimal template
     *  @return
     ***********************************************************************/
    static void CaptureImgByTemplate(const cv::Mat& templateImg, QString captureImgSavePath);


    static void TemplateMatchTestcase();

    static void MatchRightCircleAccordTemplate();

    static void ExtractRightCircle();

    /***********************************************************************
     *  @function ExtractCircleHistgram
     *  @brief    提取圆环的直方图并打印
     *            采用模板匹配，匹配到到图片后找到直方图并打印
     *  @return
     ***********************************************************************/
    static void ExtractCircleHistgram();


private:
    /***********************************************************************
     *  @function     LoadFiles
     *  @brief        // LoadFiles(filePath, "*.jpg");
     *  @return
     ***********************************************************************/
    static QStringList LoadFiles(const QString &path, QString ext);


private:
    QStringList             m_fileNameList;
};

#endif // TESTCASES_H
