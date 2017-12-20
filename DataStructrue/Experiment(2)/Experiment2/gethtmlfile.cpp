#include "gethtmlfile.h"
#include <QtNetwork>
#include <QTextCodec>

getHtmlFile::getHtmlFile()
{
	/*
	QTextCodec *gbk = QTextCodec::codecForName("gb18030");
	QTextCodec::setCodecForLocale(gbk);

	//QCoreApplication a(argc, argv);
	const QString URLSTR = "http://bbs.cehome.com/thread-1174881-1-1.html";
	//储存网页代码的文件
	const QString FILE_NAME = "test1.html";

	QUrl url(URLSTR);
	QNetworkAccessManager manager;
	QEventLoop loop;
	qDebug() << "Reading code form " << URLSTR;
	//发出请求
	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	//请求结束并下载完成后，退出子事件循环
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//开启子事件循环
	loop.exec();
	//将读到的信息写入文件
	QByteArray codeContent = reply->readAll();

	QFile file(FILE_NAME);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	QTextCodec *tc = QTextCodec::codecForName("gb18030");
	QString code = tc->toUnicode(codeContent);

	out << code << endl;
	file.close();

	qDebug() << "Finished, the code have written to " << FILE_NAME;
	*/
}

void getHtmlFile::getUrl(QString _url)
{
	QTextCodec *gbk = QTextCodec::codecForName("gb18030");
	QTextCodec::setCodecForLocale(gbk);

	//QCoreApplication a(argc, argv);
	const QString URLSTR = _url;//"http://bbs.cehome.com/thread-1174881-1-1.html";
	//储存网页代码的文件
	const QString FILE_NAME = "test.html";

	QUrl url(URLSTR);
	QNetworkAccessManager manager;
	QEventLoop loop;
	qDebug() << "Reading code form " << URLSTR;
	//发出请求
	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	//请求结束并下载完成后，退出子事件循环
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//开启子事件循环
	loop.exec();
	//将读到的信息写入文件
	QByteArray codeContent = reply->readAll();

	QFile file(FILE_NAME);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	QTextCodec *tc = QTextCodec::codecForName("gb18030");
	QString code = tc->toUnicode(codeContent);

	out << code << endl;
	file.close();

	qDebug() << "Finished, the code have written to " << FILE_NAME;

}
