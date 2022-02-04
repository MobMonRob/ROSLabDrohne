#ifndef MOCK_ROS_H
#define MOCK_ROS_H


#include <string>

#include "../std_msgs/Msg.h"
#include "ros_Talker.h"


#include "../mavros_msgs/RCIn.h"
#include "../mavros_msgs/State.h"

#include "../sensor_msgs/BatteryState.h"
#include "../sensor_msgs/Imu.h"
#include "../sensor_msgs/Joy.h"
#include "../sensor_msgs/Range.h"

#include "../std_msgs/Char.h"


class ros
{
public:
	static void init(int argc, char** argv, std::string Str) {};
	static bool ok() { return false; };
	static void spin() {};
	static void spinOnce() {};
	static void shutdown() {};


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
	};

	class NodeHandle
	{
	public:
		template <class M>
		Publisher advertise(std::string topic, uint32_t queue_size, bool latch = false)
		{
			return Publisher();
		}


		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const mavros_msgs::RCIn::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const mavros_msgs::State::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::BatteryState::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Imu::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Joy::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const sensor_msgs::Range::ConstPtr&)) { return Subscriber(); };
		Subscriber subscribe(std::string Str, int Int, void(*Callback)(const std_msgs::Char::ConstPtr&)) { return Subscriber(); };



		template <class M>
		ServiceClient serviceClient(std::string topic)
		{
			return ServiceClient();
		}

		void param(std::string Name, double& Reference, double AltValue) { Reference = AltValue; };


	};

	class Duration
	{
	public:
		Duration(double Duration = 0) {};

	};

	class Time
	{
	public:
		Time operator-(const Time& T) { return Time(); };
		bool operator<=(const Duration& T) { return false; };
		static Time now() { return Time(); };
	};




	class Rate
	{
	public:
		Rate() {};
		Rate(int i) {};


		void sleep() {};
	};

};

#endif // MOCK_ROS_H
