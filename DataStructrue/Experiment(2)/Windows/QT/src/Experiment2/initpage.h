/**
@brief GUI��ʼ��ҳ����
@file initpage.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

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
    //����woogleָ�룬���������ź����
    void setWoogle(woogle* _wo);

signals:
    //��mainwindow�������ӣ���ʾ��Ӧҳ��
	void display(int);

public slots:
    //�������ذ�ť���
	void reloadButtonClicked();
    //ֱ�ӳ�ʼ����ť���
	void initButtonClicked();
    //ȡ����ť���
	void cancelButtonClicked();
    //��һ����ť���
    void nextButtonClicked();
    //��QTextBrowser�������
    void addinfo(QString info);
    //��ʼ��������
	void initProBar(int min,int max);
    //���½�����
    void updataProBar(int curr);
    //��ʼ�����
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
