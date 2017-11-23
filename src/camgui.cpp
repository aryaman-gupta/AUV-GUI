/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <QImage>

 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

#include <sstream>
#include "../include/camgui/camgui.hpp"
#include "../include/camgui/main_window.hpp"
#include <boost/thread.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace camgui {

using namespace cv;

QPixmap* camImg::returnImage() { return image; }

QPixmap* camImg::returnImage2() { return image2; }

QPixmap* camImg::returnProcImg1() { return procImg1; }

QPixmap* camImg::returnProcImg2() { return procImg2; }

void camImg::displayInfo() { ROS_INFO("Hi there"); }



camImg::~camImg() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}



QImage camImg::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
 
            return image;
         }
 
         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
 
            return image.rgbSwapped();
         }
 
         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;
 
            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }
 
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
 
            image.setColorTable( sColorTable );
 
            return image;
         }
 
         default:
            ROS_ERROR("camImg::cvMatToQImage() - cv::Mat image type not handled in switch:"); //<< inMat.type();
            break;
      }
 
      return QImage();
   }


QPixmap camImg::cvMatToQPixmap( const cv::Mat &inMat )
   {
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
   }


void camImg::proc1CallBack(const sensor_msgs::ImageConstPtr& msg)
{


//ROS_INFO("In procCallBack 1");
cv_bridge::CvImagePtr cv_ptr;
cv::Mat img;
cv::Mat thresh;

try
  {
      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }


	if(argcam1==0)
	{
		*this->procImg1 = cvMatToQPixmap(cv_ptr->image);
		ROS_INFO("Image has been converted");
	}
	else if(argcam1==1)
	{



		cvtColor(cv_ptr->image, img, COLOR_BGR2HSV);
		inRange(img, Scalar(p1s1, p1s2, p1s3), Scalar(p1s4, p1s5, p1s6), thresh);
		*this->procImg1 = cvMatToQPixmap(thresh);
	//	ROS_INFO("Threshold");
	}
	

Q_EMIT proc1Update();	
}



void camImg::proc2CallBack(const sensor_msgs::ImageConstPtr& msg)
{


//ROS_INFO("In procCallBack 2");
cv_bridge::CvImagePtr cv_ptr;
cv::Mat img;
cv::Mat thresh;
try
  {
      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }


	if(argcam2==0)
	{
		*this->procImg2 = cvMatToQPixmap(cv_ptr->image);
//		ROS_INFO("Image has been converted");
	}
	else if(argcam2==1)
	{

		ROS_INFO("%d %d %d %d %d %d", p1s1, p1s2, p1s3, p1s4, p1s5, p1s6);

		cvtColor(cv_ptr->image, img, COLOR_BGR2HSV);
		inRange(img, Scalar(p1s1, p1s2, p1s3), Scalar(p1s4, p1s5, p1s6), thresh);
		*this->procImg2 = cvMatToQPixmap(thresh);
		//ROS_INFO("Threshold");
	}
	

Q_EMIT proc2Update();	
}


void camImg::cam1CallBack(const sensor_msgs::ImageConstPtr& msg)
{


//ROS_INFO("In callback 1");
cv_bridge::CvImagePtr cv_ptr;
try
  {
      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }


	*this->image = cvMatToQPixmap(cv_ptr->image);
//ROS_INFO("Image has been converted");

Q_EMIT imgUpdated();	


}



void camImg::cam2CallBack(const sensor_msgs::ImageConstPtr& msg)
{

cv_bridge::CvImagePtr cv_ptr;
try
  {
      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  }
  catch (cv_bridge::Exception& e)
  {
 //   ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }


	*this->image2 = cvMatToQPixmap(cv_ptr->image);


}

void spinThread()
{
  ros::spin();
}

void spinThread2()
{
  ros::spin();
}





void camImg::printImg()
{
//ROS_INFO("Int print img");
ros::init(this->c, this->v,"camgui");

	if ( ! ros::master::check() ) {
		ROS_INFO("master fail");
	}


	ros::start(); // explicitly needed since our nodehandle is going out of scope.

	
	ros::NodeHandle nh;

	subimg1 = nh.subscribe("/camera_image", 1, &camImg::cam1CallBack, this);
	subimg2 = nh.subscribe("/camera_image", 1, &camImg::cam2CallBack, this);


	boost::thread spin_thread(&spinThread);

//	ros::spin();

}


void camImg::printProc()
{
//ROS_INFO("In print proc");
//ros::init(this->c, this->v,"camgui");

	if ( ! ros::master::check() ) {
		ROS_INFO("master fail");
	}


	ros::start(); // explicitly needed since our nodehandle is going out of scope.

	
	ros::NodeHandle nh;

	proc1 = nh.subscribe("/camera_image", 1, &camImg::proc1CallBack, this);
	proc2 = nh.subscribe("/camera_image", 1, &camImg::proc2CallBack, this);


	//boost::thread spin_thread(&spinThread2);

//	ros::spin();

}


camImg::camImg(int argc, char** argv )
{

	/*ros::init(argc, argv,"camgui");

	if ( ! ros::master::check() ) {
		ROS_INFO("master fail");
	}


	ros::start(); // explicitly needed since our nodehandle is going out of scope.

	
	ros::NodeHandle nh;*/

	c = argc;
	v = argv;
	argcam1 = 0;
	argcam2 = 0;
	p1s1 = p1s2 = p1s3 = p1s4 = p1s5 = p1s6 = 0;

	image=new QPixmap();
	image2=new QPixmap();

	procImg1=new QPixmap();
	procImg2=new QPixmap();
	//subimg1 = nh.subscribe("/camera_image", 1000, &camImg::cam1CallBack, this);

	//subimg2 = nh.subscribe("/camera_image", 1000, &camImg::cam2CallBack, this);

	//boost::thread spin_thread(&spinThread);
//ros::spin();



}


}//namespace camgui
