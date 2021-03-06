#ifndef ROSTHREAD_H
#define ROSTHREAD_H

#include <ros/ros.h>

#include "threading/Thread.h"


template <class T>
class RosThread : public Thread<T>
{
public:
	RosThread(double Frequency = 1);
	RosThread(std::string Descriptor, double Frequency = 1);
	
	inline void setFrequency(double Frequency) { this->Rate_ = ros::Rate(Frequency); };
	T setPayload(T Payload);
	
	inline T getPayload() const { return this->Payload_; };
	inline ros::Rate getRate() const { return this->Rate_; };
	

	bool start() override;
	T runOnce() override;
	virtual T runOnce(T Payload) = 0;
	
protected:


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
RosThread<T>::RosThread(std::string Descriptor, double Frequency)
{
	std::cout << "New Thread \"" << Descriptor << "\" at " << this << std::endl;

	this->setFrequency(Frequency);
}

template <class T>
bool RosThread<T>::start()
{
	if (this->Thread_ == nullptr)
	{
		this->setRunning(true);

		this->Thread_ = new std::thread(RosThread::run, this);
#ifdef DEBUG
		std::cout << "Creating Thread " << this->Thread_ << std::endl;
#endif
	}

	return this->isThreaded();
}




template<class T>
T RosThread<T>::setPayload(T Payload)
{
	T ReturnLoad = this->getPayload();
	

	if (this->lock())
	{
		this->Payload_ = Payload;
		ReturnLoad = this->runOnce(this->getPayload());
		ros::spinOnce();
	}
	this->unlock();

	return Payload;
}

template<class T>
T RosThread<T>::runOnce()
{
	T ReturnLoad = this->getPayload();


	if (this->getNext())
	{
		ReturnLoad = this->runOnce(this->getPayload());
	}
	
	return ReturnLoad;
}


// static
template <class T>
void RosThread<T>::run(RosThread<T>* Instance)
{
    if (Instance != nullptr)
    {
    	ros::Rate Rate = Instance->getRate();
    	
    	
        while (ros::ok() && Instance->isRunning())
        {
			Instance->runOnce();
            
			ros::spinOnce();
        	Rate.sleep();
        }
    }
}

#endif // ROSTHREAD_H


