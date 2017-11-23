/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef camgui_CAMGUI_HPP_
#define camgui_CAMGUI_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QPixmap>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>



/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace camgui {

/****************************************************************************
** Class
******************************************************************************/

class camImg : public QThread {
    Q_OBJECT
public:
	camImg();
	camImg(int argc, char** argv );
	virtual ~camImg();

	//camgui::MainWindow mw;

	void cam1CallBack(const sensor_msgs::ImageConstPtr& msg);
	void cam2CallBack(const sensor_msgs::ImageConstPtr& msg);

	void proc1CallBack(const sensor_msgs::ImageConstPtr& msg);
	void proc2CallBack(const sensor_msgs::ImageConstPtr& msg);



	QImage cvMatToQImage( const cv::Mat &inMat);
	QPixmap cvMatToQPixmap( const cv::Mat &inMat ); 



	void printImg();
	void printProc();
	int c;
	char** v;
	int argcam1;
	int argcam2;



	QPixmap* returnImage();
	QPixmap* returnImage2();
	QPixmap* returnProcImg1();
	QPixmap* returnProcImg2();
	void displayInfo();

	int p1s1;
	int p1s2;
	int p1s3;
	int p1s4;
	int p1s5;
	int p1s6;
Q_SIGNALS:
	void imgUpdated();
	void proc1Update();
	void proc2Update();

private:

	QPixmap* image;
	QPixmap* procImg1;
	

	QImage Qimg;

	QPixmap* image2;
	QPixmap* procImg2;
	QImage Qimg2;

	ros::Subscriber subimg1;
	ros::Subscriber subimg2;

	ros::Subscriber proc1;
	ros::Subscriber proc2;

};

}  // namespace camgui

#endif

