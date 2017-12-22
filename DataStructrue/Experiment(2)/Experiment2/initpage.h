#ifndef INITPAGE_H
#define INITPAGE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QProgressBar>
#include <QGridLayout>
#include <QTextCursor>

#include "woogle.h"

class initPage : public QWidget
{
	Q_OBJECT
public:
	explicit initPage(QWidget *parent = nullptr);
	void setWoogle(woogle* _wo)
	{
		wo=_wo;
		connect(wo,SIGNAL(updataProBar(int)),this,SLOT(updataProBar(int)));
		connect(wo,SIGNAL(initProBar(int,int)),this,SLOT(initProBar(int,int)));
		connect(wo,SIGNAL(appendText(QString)),this,SLOT(addinfo(QString)));
		connect(wo,SIGNAL(initComplete()),this,SLOT(initComplete()));
	}

signals:
	void display(int);

public slots:
	void reloadButtonClicked();
	void initButtonClicked();
	void cancelButtonClicked();
	void nextButtonClicked();
	void addinfo(QString info);
	void initProBar(int min,int max);
	void updataProBar(int curr);
	void initComplete();

private:
	QLabel* label;
	QPushButton* reloadButton;
	QPushButton* initButton;
	QPushButton* next;
	QPushButton* cancel;
	QProgressBar* proBar;
	QTextBrowser* textBrowser;
	QGridLayout* layout;
	woogle* wo;
};

#endif // INITPAGE_H
