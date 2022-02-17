#include "coex/coexBattery.h"



coexBattery *coex_Battery = nullptr;

void callbackBattery(const sensor_msgs::BatteryState::ConstPtr& msg)
{
	if (coex_Battery != nullptr)
	{
		coex_Battery->cbBattery(msg);
	}
}





coexBattery::coexBattery(double Perc_thershold, double Intervall_Info)
	: Thershold_Warning_(Perc_thershold)
{
	ROS_INFO("Starting coexBattery...");
	ros::spinOnce();
	
	coex_Battery = this;

	this->initHealth();
	
	this->nh_.param("Battery/Warning", this->Thershold_Warning_, Perc_thershold);
	{
		double Intervall;
		
		
		this->nh_.param("Battery/Intervall", Intervall, Intervall_Info);
		
		this->Intervall_Info_ = ros::Duration(Intervall);
	}
	
	this->SubBattery_ = this->nh_.subscribe("mavros/battery", 5, callbackBattery);

	ROS_INFO("Started coexBattery");
}

coexBattery::coexBattery(double V_min, double V_max, double V_thershold, double Intervall_Info)
	: coexBattery((100 * (V_thershold - V_min) / (V_max - V_min)), Intervall_Info)
{
}


coexBattery::~coexBattery()
{
	ROS_INFO("Terminating coexBattery...");

	ROS_INFO("Battery at %f%", this->getPercentage());
	ROS_INFO("Terminated coexBattery");
	ros::spinOnce();
}


double coexBattery::getVoltage() const
{
	return static_cast<double>(this->Battery_.voltage);
}

double coexBattery::getPercentage() const
{
	return static_cast<double>(this->Battery_.percentage)*100;
}

std::string coexBattery::getHealth()
{
	return this->getHealth(this->getHealthID());
}

std::string coexBattery::getHealth(int StatusID)
{
	std::string ReturnString = "UNKNOWN?";
	std::map<int, std::string>::iterator it = this->Health_.find(StatusID);


	if (it != this->Health_.end())
	{
		ReturnString = it->second;
	}

	return ReturnString;
}







void coexBattery::cbBattery(const sensor_msgs::BatteryState::ConstPtr& Battery)
{
	double Percentage = static_cast<double>(Battery->percentage)*100;
	double Voltage = static_cast<double>(Battery->voltage);
	
	
	if (Percentage <= this->Thershold_Warning_)
	{
		ROS_WARN("Battery at %f (%f V).", Percentage, Voltage);
	}
	else if ((Battery->header.stamp - this->Battery_.header.stamp) >= this->Intervall_Info_)
	{
		ROS_INFO("Battery at %f%", Percentage);
	}
	
	this->Battery_ = *Battery;
	
	this->call();
}








void coexBattery::initHealth()
{
	/* https://mavlink.io/en/messages/common.html#MAV_STATE
	 */
	this->Health_.insert(std::pair<int, std::string>(0, "UNKNOWN"));
	this->Health_.insert(std::pair<int, std::string>(1, "GOOD"));
	this->Health_.insert(std::pair<int, std::string>(2, "OVERHEAT"));
	this->Health_.insert(std::pair<int, std::string>(3, "DEAD"));
	this->Health_.insert(std::pair<int, std::string>(4, "OVERVOLTAG"));
	this->Health_.insert(std::pair<int, std::string>(5, "UNSPEC_FAILURE"));
	this->Health_.insert(std::pair<int, std::string>(6, "COLD"));
	this->Health_.insert(std::pair<int, std::string>(7, "WATCHDOG_TIMER_EXPIRE"));
	this->Health_.insert(std::pair<int, std::string>(8, "SAFETY_TIMER_EXPIRE"));
}

