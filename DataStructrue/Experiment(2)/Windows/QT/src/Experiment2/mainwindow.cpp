/**
@brief 主窗口定义
@file mainwindow.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setFixedSize(1200,800);
    this->setWindowTitle(QString::fromLocal8Bit("Woogle搜索"));

	stacklayout=new QStackedLayout();
	initpage=new initPage();
	searchpage=new searchPage();
	detailedpage=new detailedPage();
	wo = new woogle(this);
	initpage->setWoogle(wo);
	searchpage->setWoogle(wo);
	detailedpage->setWoogle(wo);

	stacklayout->addWidget(initpage);
	stacklayout->addWidget(searchpage);
	stacklayout->addWidget(detailedpage);

	connect(initpage,SIGNAL(display(int)),stacklayout,SLOT(setCurrentIndex(int)));
	connect(searchpage,SIGNAL(display(int)),stacklayout,SLOT(setCurrentIndex(int)));
	connect(detailedpage,SIGNAL(display(int)),stacklayout,SLOT(setCurrentIndex(int)));
	connect(searchpage,SIGNAL(passInfoToDetailPage(int)),detailedpage,SLOT(setId(int)));

	centerwidget=new QWidget();
	centerwidget->setLayout(stacklayout);
	this->setCentralWidget(centerwidget);
}

MainWindow::~MainWindow()
{
	delete ui;
}
