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

	QStackedLayout* stacklayout;
	initPage* initpage;
	searchPage* searchpage;
	detailedPage* detailedpage;
	woogle* wo;

	QWidget* centerwidget;
};

#endif // MAINWINDOW_H
