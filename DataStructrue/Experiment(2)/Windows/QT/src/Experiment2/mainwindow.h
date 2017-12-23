/**
@brief GUI主窗口类
@file mainwindow.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QWidget>
#include "initpage.h"
#include "woogle.h"
#include "searchpage.h"
#include "detailedpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
    //多界面切换布局
	QStackedLayout* stacklayout;
    //初始化界面
    initPage* initpage;
    //搜索界面
    searchPage* searchpage;
    //详情界面
    detailedPage* detailedpage;
	woogle* wo;

	QWidget* centerwidget;
};

#endif // MAINWINDOW_H
