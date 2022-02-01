#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <ros/time.h>


double Timestamp;
int Counter = 0;


void chatterCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
	double Time = msg->header.stamp.toSec();


	// Send data to State-Builder




	// legacy
	if (++Counter >=100)
	{
		ROS_INFO("100 Messages took %f Seconds.", msg->header.stamp.toSec() - Timestamp);

		Counter = 0;
		Timestamp = msg->header.stamp.toSec();
	}
}




int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Accel_Reader");

	ros::init(argc, argv, "Accel_Reader");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("mavros/imu/data", 100, chatterCallback);
	
	while (ros::ok())
	{
		ros::spinOnce();
	}

	return 0;
}


