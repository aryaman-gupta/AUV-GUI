#ifndef camgui_MAIN_WINDOW_H
#define camgui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "camgui.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace camgui {

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	
	~MainWindow();
	camImg cg;


public Q_SLOTS:

	void updateImgView();

	void updateProcView1();
	void updateProcView2();
	void on_process1_1_clicked();
	void on_process1_2_clicked();

	void on_p1Slider1_valueChanged(int value);
	void on_p1Slider2_valueChanged(int value);
	void on_p1Slider3_valueChanged(int value);
	void on_p1Slider4_valueChanged(int value);
	void on_p1Slider5_valueChanged(int value);
	void on_p1Slider6_valueChanged(int value);

private:
	Ui::MainWindowDesign ui;

};

}  // namespace camgui

#endif
