#include "mainwindow.h"
#include <QApplication>

#include "gethtmlfile.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	getHtmlFile get;
	get.getUrl("http://bbs.cehome.com/thread-1174881-1-1.html");

	return a.exec();
}
