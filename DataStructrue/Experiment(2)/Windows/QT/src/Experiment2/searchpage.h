/**
@brief GUI搜索页面类
@file searchpage.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

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

    //设置woogle指针
	void setWoogle(woogle* _wo);

signals:
    //显示信号
	void display(int);
    //将用户选中的页面ID传递给详情页
    void passInfoToDetailPage(int);

public slots:
    //搜索按钮点击
	void searchButtonClicked(bool useAVL);
    //列表项点击信号
	void pageItemDoubleClicked(QListWidgetItem *item);
    //AVL树搜索按钮点击
	void AVLSearchButtonClicked();
    //哈希表搜索按钮点击
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
