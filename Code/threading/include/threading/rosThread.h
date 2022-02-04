#ifndef ROSTHREAD_H
#define ROSTHREAD_H

#include <ros/ros.h>

#include <thread>

#include "threading/Thread.h"


template <class T>
class RosThread : public Thread<T>
{
public:
	RosThread(double Frequency = 1);
	
	void setFrequency(double Frequency) { this->Rate_ = ros::Rate(Frequency); };
	T setPayload(T Payload);
	
	T getPayload() const { return this->Payload_; };
	ros::Rate getRate() const { return this->Rate_; };
	
	T runOnce() override;
	virtual T runOnce(T Payload) = 0;
	
private:
	static void run(RosThread<T> *Instance);
	
private:
	T Payload_;
	ros::Rate Rate_;
};



template<class T>
RosThread<T>::RosThread(double Frequency)
	: Rate_(Frequency),
	Payload_()
{
}


template<class T>
T RosThread<T>::setPayload(T Payload)
{
    this->Payload_ = Payload;
	
    return this->runOnce();
}

template<class T>
T RosThread<T>::runOnce()
{
    T Payload = this->getPayload();
	
	
    return this->runOnce(Payload);
}


// static
template <class T>
void RosThread<T>::run(RosThread<T>* Instance)
{
    if (Instance != nullptr)
    {
    	ros::Rate Rate = Instance->getRate();
    	
    	
        while (Instance->getNext())
        {
            Instance->runOnce();
            
        	Rate.sleep();
        }
    }
}

#endif // ROSTHREAD_H


