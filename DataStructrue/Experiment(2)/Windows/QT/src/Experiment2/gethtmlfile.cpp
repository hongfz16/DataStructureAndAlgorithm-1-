/**
@brief 下载html页面类定义
@file gethtmlfile.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "gethtmlfile.h"
#include <QtNetwork>
#include <QTextCodec>

getHtmlFile::getHtmlFile()
{
}

void getHtmlFile::getUrl(QString _url,QString filename)
{
	QTextCodec *gbk = QTextCodec::codecForName("gb18030");
	QTextCodec::setCodecForLocale(gbk);

    QString URLSTR = _url;

    QString FILE_NAME = filename;

	QUrl url(URLSTR);
	QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
	QByteArray codeContent = reply->readAll();

	QFile file(FILE_NAME);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);

	QTextCodec *tc = QTextCodec::codecForName("gb18030");
	QString code = tc->toUnicode(codeContent);

	out << code << endl;
	file.close();


}
