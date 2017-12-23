/**
@brief GUI����ҳ����
@file searchpage.h
@author �鷽��
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

    //����woogleָ��
	void setWoogle(woogle* _wo);

signals:
    //��ʾ�ź�
	void display(int);
    //���û�ѡ�е�ҳ��ID���ݸ�����ҳ
    void passInfoToDetailPage(int);

public slots:
    //������ť���
	void searchButtonClicked(bool useAVL);
    //�б������ź�
	void pageItemDoubleClicked(QListWidgetItem *item);
    //AVL��������ť���
	void AVLSearchButtonClicked();
    //��ϣ��������ť���
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
