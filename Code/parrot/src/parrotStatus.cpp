#include "parrot/parrotStatus.h"

#include <std_msgs/Empty.h>
#include <std_srvs/Empty.h>




parrotStatus::parrotStatus(parrotBattery* Battery, parrotIMU* IMU)
	: Statusable(Battery),
	nh_(),
	Sub_(nh_.subscribe("ardrone/navdata", 1, &parrotStatus::callbackNavdata, this)),
	IMU_(IMU)
{
	ROS_INFO("Starting parrotStatus...");
	ros::spinOnce();

	this->initSystemStatus();
	
	ROS_INFO("Started parrotStatus");
}

parrotStatus::~parrotStatus()
{
	ROS_INFO("Termintating parrotStatus...");

	ROS_INFO("Terminated parrotStatus");
	ros::spinOnce();
}




bool parrotStatus::setArmState(bool ArmState)
{
	bool ReturnBool = false;
	ros::Publisher PubCmd;


	if (ArmState)
	{
		if (this->meetsRequirements())
		{
			if (this->isGrounded() || this->getStatusID() == 0)
			{
				if (this->getStatusID() == 0)
				{
					this->resetStatus();
				}

				ROS_INFO("Takeoff...");

				{
					int TryCount = 0;
					const int TryMax = 10;

					while (TryCount++ < TryMax && !this->isFlying())
					{
						ros::Time WaitTime = ros::Time::now();
						ros::Duration WaitDuration(0.25);


						PubCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/takeoff", 1);

						PubCmd.publish(std_msgs::Empty());
						ros::spinOnce();

						while (ros::Time::now() - WaitTime < WaitDuration)
						{
						}
					}
				}
			}
			else
			{
				ROS_INFO("Drone allready flying, no additional Takeoff needed.");
			}
		}
		else
		{
			ROS_WARN("Takeoff not possible, Requirements not met.");
		}

		ReturnBool = this->isFlying();
	}
	else
	{
		ROS_INFO("Landing...");

		PubCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/land", 1);

		PubCmd.publish(std_msgs::Empty());
		ros::spinOnce();

		ReturnBool = true;
	}

	return ReturnBool;
}



















bool parrotStatus::resetStatus()
{
	ROS_INFO("Reset Drone before Takeoff...");



	{
		ros::Publisher ResetCmd = this->nh_.advertise<std_msgs::Empty>("ardrone/reset", 1);

		int TryCount = 0;
		const int TryMax = 10;

		while (TryCount++ < TryMax && this->getStatusID() == 0)
		{
			ros::Time WaitTime = ros::Time::now();
			ros::Duration WaitDuration(1.0);

			ResetCmd.publish(std_msgs::Empty());
			ros::spinOnce();

			while (ros::Time::now() - WaitTime < WaitDuration)
			{
			}
		}


		/* no need for an explicit shutdown of PubCmd
		 * https://docs.ros.org/en/jade/api/roscpp/html/classros_1_1Publisher.html#a5ba460ae4cbf805d35055d054ad034c2
		 */
	}

	{
		ros::ServiceClient ClienCalibrate = this->nh_.serviceClient<std_srvs::Empty>("ardrone/imu_recalib");

		std_srvs::Empty srvEmpty;


		ClienCalibrate.call(srvEmpty);
	}

	{
		ros::ServiceClient ClienTrim = this->nh_.serviceClient<std_srvs::Empty>("ardrone/flattrim");

		std_srvs::Empty srvEmpty;


		ClienTrim.call(srvEmpty);
	}

	
	return false;
}





void parrotStatus::initSystemStatus()
{
	/* https://github.com/AutonomyLab/ardrone_autonomy/blob/indigo-devel/msg/Navdata.msg
	 * 
	 */
	this->addSystemStatus(0, "Unknown");
	this->addSystemStatus(1, "Init");
	this->addSystemStatus(2, "Landed");
	this->addSystemStatus(3, "Flying");			// isFlying
	this->addSystemStatus(4, "Hovering");
	this->addSystemStatus(5, "Test");
	this->addSystemStatus(6, "Taking off...");
	this->addSystemStatus(7, "Goto Fix Point");	// isFlying
	this->addSystemStatus(8, "Landing...");
	this->addSystemStatus(9, "Looping...");
}

void parrotStatus::callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	bool StatusChange = this->getStatusID() != navdataPtr->state;


	if (StatusChange)
	{
		ROS_INFO("Status changed to %s.", this->getStatusTranslation(navdataPtr->state).c_str());
	}

	this->setStatusID(navdataPtr->state);
	this->setTime(Timestamp(navdataPtr->header.stamp.toSec()));

	if (StatusChange)
	{
		this->IMU_->setFlightState(this->isFlying());
	}
}
