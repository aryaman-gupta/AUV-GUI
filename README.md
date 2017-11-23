GUI used for testing of Autonomous Underwater Vehicle

GUI developed using Qt 4.5, on Ubuntu 14.04, using Robot Operating System (ROS) to fetch data from vehicle. This project subscribes to a topic on which the camera feed from the vehicle is published. It displays the feed from both the cameras and allows the users to test different image processing algorithms on the camera feed. Parameters of the algorithms can be varied through sliders and text boxes.

The pub_rviz file uses the rviz package of ROS to visualize the orientation of the vehicle while it is running. It subscribes to a topic to which IMU sensor values are being published.

To run:
After running the executable, launch rviz and select the Fixed_frame as my_frame and market topic as /visualization_marker.