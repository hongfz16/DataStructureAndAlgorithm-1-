#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextCodec>
#include <QTextDecoder>
#include <QLabel>
#include "woogle.h"
#include "pageinfo.h"

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class searchPage : public QWidget
{
	Q_OBJECT
public:
	explicit searchPage(QWidget *parent = nullptr);

	void setWoogle(woogle* _wo);

signals:
	void display(int);
	void passInfoToDetailPage(int);

public slots:
	void searchButtonClicked(bool useAVL);
	void pageItemDoubleClicked(QListWidgetItem *item);
	void AVLSearchButtonClicked();
	void HashSearchButtonClicked();

private:
	QGridLayout* layout;
	QLineEdit* lineedit;
	QListWidget* list;
	QPushButton* avlsearch;
	QPushButton* hashsearch;
	QLabel* info;

	woogle* wo;
	QString query;
	vector<pageInfo> result;
};

#endif // SEARCHPAGE_H
