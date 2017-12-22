#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	stacklayout=new QStackedLayout();
	initpage=new initPage();
	searchpage=new searchPage();
	wo = new woogle(this);
	initpage->setWoogle(wo);
	searchpage->setWoogle(wo);

	stacklayout->addWidget(initpage);
	stacklayout->addWidget(searchpage);
	connect(initpage,SIGNAL(display(int)),stacklayout,SLOT(setCurrentIndex(int)));

	centerwidget=new QWidget();
	centerwidget->setLayout(stacklayout);
	this->setCentralWidget(centerwidget);
}

MainWindow::~MainWindow()
{
	delete ui;
}
