/**
@brief 程序主入口
@file main.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include "woogle.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    std::locale::global(std::locale("chs"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	MainWindow w;
	w.show();

	return a.exec();
}
