#ifndef DETAILEDPAGE_H
#define DETAILEDPAGE_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QWebEngineView>
#include "woogle.h"
#include "pageinfo.h"
#include "CharString.h"
#include <QString>
#include <QUrl>
#include <string>
#include <QTextCodec>
#include <QTextDecoder>
using namespace std;

class detailedPage : public QWidget
{
	Q_OBJECT
public:
	explicit detailedPage(QWidget *parent = nullptr);

	void setWoogle(woogle* _wo) {wo=_wo;}

signals:
	void display(int);

public slots:
	void setId(int _id);
	void backButtonClicked();

private:
	QGridLayout* layout;
	QTextBrowser* textb;
	QPushButton* back;
	QWebEngineView* webView;
	woogle* wo;
	int id;
	QTextCodec* code;
	QTextDecoder* decoder;
};

#endif // DETAILEDPAGE_H
