#ifndef AUTOPUBLISHER_H
#define AUTOPUBLISHER_H

#include <ros/ros.h>

#include <string>

#include "threading/rosThread.h"


template <class T>
class AutoPublisher : public RosThread<T>
{
public:
    AutoPublisher(std::string Topic, double Frequency, int Queue = 10, bool AutoStart = false);
	
    T runOnce(T Payload) override;
	
private:
	ros::NodeHandle nh_;									// needs to be in derived class.
	ros::Publisher Pub_;
};



template<class T>
AutoPublisher<T>::AutoPublisher(std::string Topic, double Frequency, int Queue, bool AutoStart)
	: RosThread<T>(Frequency)
{
	this->Pub_ = this->nh_.advertise<T>(Topic, Queue, true);
	
	if (AutoStart)
	{
		this->start();
	}
}


template <class T>
T AutoPublisher<T>::runOnce(T Payload)
{
	this->Pub_.publish(Payload);
	
	ros::spinOnce();
	
	return Payload;
}

#endif // AUTOPUBLISHER_H


