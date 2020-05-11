#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btn1 = new QPushButton(this);
    btn1->setObjectName(tr("btn1"));

    QPushButton *btn2 = new QPushButton(this);
    btn2->setObjectName(tr("btn2"));

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout1->addWidget(btn1);
    hLayout1->addWidget(btn2);

    QPushButton *btn3 = new QPushButton(this);
    btn3->setObjectName(tr("btn3"));

    QPushButton *btn4 = new QPushButton(this);
    btn4->setObjectName(tr("btn4"));

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    hLayout2->addWidget(btn3);
    hLayout2->addWidget(btn4);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);


}

MainWindow::~MainWindow()
{
    delete ui;
}
