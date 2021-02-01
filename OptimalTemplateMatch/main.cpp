#include "mainwindow.h"
#include <QApplication>

#include "testcases.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    TestCases::GenerateBinaryImgTestCase();
//    TestCases::FindOptimalTemplateTestCase();
//    TestCases::TemplateMatchTestcase();
//    TestCases::ExtractRightCircle();
    TestCases::MatchRightCircleAccordTemplate();
    return a.exec();
}
