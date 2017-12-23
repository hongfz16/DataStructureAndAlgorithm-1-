/**
@brief GUIҳ������ҳ
@file detailedpage.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

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

    //����woogleָ��
	void setWoogle(woogle* _wo) {wo=_wo;}

signals:
    //������ذ�ť��������mainwindow��SLOT��Ӧ����������ҳ
	void display(int);

public slots:
    //��Ӧ����ҳ˫���źţ����ñ�ҳ����������ҳ�������
	void setId(int _id);
    //��Ӧ���ذ�ť�źţ�����display(1)�ź�
	void backButtonClicked();

private:
    //������
	QGridLayout* layout;
    //��ʾҳ�������Ϣ
    QTextBrowser* textb;
    //���ذ�ť
	QPushButton* back;
    //��ҳ�������
	QWebEngineView* webView;
    //woogleָ��
	woogle* wo;
    //��ǰ��ʾҳ��ID
	int id;
    //���������
	QTextCodec* code;
	QTextDecoder* decoder;
};

#endif // DETAILEDPAGE_H
