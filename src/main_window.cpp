#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include <QPixmap>
#include "../include/camgui/main_window.hpp"
#include "../include/camgui/camgui.hpp"
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace camgui {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, cg(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
	ui.cam1_label->setScaledContents(true);
	ui.cam2_label->setScaledContents(true);
	ui.proc1_label->setScaledContents(true);
	ui.proc2_label->setScaledContents(true);

	ui.p1Slider1->setRange(0, 179);
	ui.p1Slider2->setRange(0, 255);
	ui.p1Slider3->setRange(0, 255);
	ui.p1Slider4->setRange(0, 179);
	ui.p1Slider5->setRange(0, 255);
	ui.p1Slider6->setRange(0, 255);
					
	cg.printImg();
	cg.printProc();
	QObject::connect(&cg, SIGNAL(imgUpdated()), this, SLOT(updateImgView()));
	QObject::connect(&cg, SIGNAL(proc1Update()), this, SLOT(updateProcView1()));
	QObject::connect(&cg, SIGNAL(proc2Update()), this, SLOT(updateProcView2()));

}


void MainWindow::on_process1_1_clicked()
{
 cg.argcam1=1;
}


void MainWindow::on_process1_2_clicked()
{
 cg.argcam2=1;
}

void MainWindow::on_p1Slider1_valueChanged(int value)
{
	cg.p1s1 = value;
}


void MainWindow::on_p1Slider2_valueChanged(int value)
{
	cg.p1s2 = value;
}


void MainWindow::on_p1Slider3_valueChanged(int value)
{
	cg.p1s3 = value;
}


void MainWindow::on_p1Slider4_valueChanged(int value)
{
	cg.p1s4 = value;
}


void MainWindow::on_p1Slider5_valueChanged(int value)
{
	cg.p1s5 = value;
}


void MainWindow::on_p1Slider6_valueChanged(int value)
{
	cg.p1s6 = value;
}


void MainWindow::updateImgView()
{
	QPixmap pix(*cg.returnImage());
	ui.cam1_label->setPixmap(pix);
	QPixmap pix2(*cg.returnImage2());
	ui.cam2_label->setPixmap(pix2);
		
}

void MainWindow::updateProcView1()
{

	QPixmap pix(*cg.returnProcImg1());
	ui.proc1_label->setPixmap(pix);
}

void MainWindow::updateProcView2()
{

	QPixmap pix(*cg.returnProcImg2());
	ui.proc2_label->setPixmap(pix);
}


MainWindow::~MainWindow() {}

}//namespace camgui
