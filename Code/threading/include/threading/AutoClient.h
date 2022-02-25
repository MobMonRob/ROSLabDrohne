#ifndef AUTOCLIENT_H
#define AUTOCLIENT_H

#include <ros/ros.h>

#include <string>

#include "threading/rosThread.h"


template <class T>
class AutoClient : public RosThread<T>
{
public:
    AutoClient(std::string Service, double Frequency, bool AutoStart = false);
	
	T runOnce(T Payload) override;
    
private:
	ros::NodeHandle nh_;									// needs to be in derived class.
	ros::ServiceClient Client_;
};



template<class T>
AutoClient<T>::AutoClient(std::string Service, double Frequency, bool AutoStart)
#ifdef DEBUG
	: RosThread<T>("AutoClient", Frequency)
#endif
{
	this->Client_ = this->nh_.serviceClient<T>(Service);
	
	if (AutoStart)
	{
		this->start();
	}
}


template <class T>
T AutoClient<T>::runOnce(T Payload)
{
	this->Client_.call(Payload);
	
#ifdef DEBUG
	ROS_INFO("Called Service %s from runOnce(T Payload).", this->Client_.getService());
#endif

	return Payload;
}

#endif // AUTOCLIENT_H


