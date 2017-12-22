#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QWidget>
#include "initpage.h"
#include "woogle.h"
#include "searchpage.h"

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

	QStackedLayout* stacklayout;
	initPage* initpage;
	searchPage* searchpage;
	woogle* wo;

	QWidget* centerwidget;
};

#endif // MAINWINDOW_H
