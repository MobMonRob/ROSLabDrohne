#include "coex/coexBattery.h"






coexBattery *coex_Battery = nullptr;

void callbackBattery(const sensor_msgs::BatteryState::ConstPtr& msg)
{
	if (coex_Battery != nullptr)
	{
		coex_Battery->cbBattery(msg);
	}
}





coexBattery::coexBattery(double Thershold_Warning, double Intervall_Info)
{
	ROS_INFO("Started coexBattery");
	
	coex_Battery = this;
	
	this->nh_.param("Battery/Warning", this->Thershold_Warning_, Thershold_Warning);
	{
		double Intervall;
		
		
		this->nh_.param("Battery/Intervall", Intervall, Intervall_Info);
		
		this->Intervall_Info_ = ros::Duration(Intervall);
	}
	
	this->SubBattery_ = this->nh_.subscribe("mavros/battery", 5, callbackBattery);
}



double coexBattery::getVoltage()
{
	return static_cast<double>(this->Battery_.voltage);
}

double coexBattery::getPercentage()
{
	return static_cast<double>(this->Battery_.percentage)*100;
}





void coexBattery::cbBattery(const sensor_msgs::BatteryState::ConstPtr& Battery)
{
	double Percentage = static_cast<double>(Battery->percentage)*100;
	double Voltage = static_cast<double>(Battery->voltage);
	
	
	if (Percentage <= this->Thershold_Warning_)
	{
		ROS_WARN("Battery at %f (%f V).", Percentage, Voltage);
	}
	else if (Battery->header.stamp - this->Battery_.header.stamp >= this->Intervall_Info_)
	{
		ROS_INFO("Battery at %f.", Percentage);
	}
	
	this->Battery_ = *Battery;
	
	this->call();
}


