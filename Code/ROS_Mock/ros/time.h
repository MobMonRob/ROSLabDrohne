#ifndef MOCK_ROS_H
#define MOCK_ROS_H

#include <string>

#include "../std_msgs/Msg.h"
//#include "ros_Talker.h"





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

	class NodeHandle
	{
	public:
		template <class M>
		Publisher advertise(std::string topic, uint32_t queue_size, bool latch = false)
		{
			return Publisher();
		}

		Subscriber subscribe(std::string Str, int Int, void(*Callback))
		{
			return Subscriber();
		};
	};

	class Duration
	{
	public:
		Duration(double Duration) {};

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
