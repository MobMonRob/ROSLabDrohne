#ifndef MOCK_ROS_H
#define MOCK_ROS_H

#define DEBUG


#include <string>

#include "rosTiming.h"
#include "../std_msgs/Msg.h"
#include "ros_Talker.h"

#include "../mavros_msgs/PositionTarget.h"
#include "../mavros_msgs/RCIn.h"
#include "../mavros_msgs/State.h"

#include "../sensor_msgs/BatteryState.h"
#include "../sensor_msgs/Imu.h"
#include "../sensor_msgs/Joy.h"
#include "../sensor_msgs/Range.h"

#include "../std_msgs/Char.h"


namespace ros
{

	void init(int argc, char** argv, std::string Str);
	bool ok();
	void spin();
	void spinOnce();
	void shutdown();


	class Publisher
	{
	public:
		void publish(Msg Message) {};

	};

	class Subscriber
	{
	public:


	};

	class ServiceClient
	{
	public:
		bool call(Msg) { return false; };
		std::string getService() { return std::string(); };
	};

	class NodeHandle
	{
	public:
		template <class M>
		Publisher advertise(std::string topic, uint32_t queue_size, bool latch = false)
		{
			return Publisher();
		}

		

		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const mavros_msgs::PositionTarget::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const mavros_msgs::RCIn::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const mavros_msgs::State::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::BatteryState::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Imu::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Joy::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Range::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const std_msgs::Char::ConstPtr&)) { return Subscriber(); };
		
		template <class M>
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const M*))
		{
			return Subscriber();
		}
		


		template <class M>
		ServiceClient serviceClient(std::string topic)
		{
			return ServiceClient();
		}

		void param(std::string Name, double& Reference, double AltValue) { Reference = AltValue; };


	};

};

#endif // MOCK_ROS_H
