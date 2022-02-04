#include "coex/coexState.h"

#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>


coexState *coex_State = nullptr;


void callbackState(const mavros_msgs::State::ConstPtr& msg)
{
	if (coex_State != nullptr)
	{
		coex_State->cbState(msg);
	}
}




coexState::coexState()
	: ClMode_("mavros/set_mode", 10)
{
	ROS_INFO("Started coexState");
	
	coex_State = this;
	
	this->initSystemStatus();
	
	this->SubState_ = this->nh_.subscribe<mavros_msgs::State>("mavros/state", 10, callbackState);
}


bool coexState::setMode(std::string Mode)
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		ros::ServiceClient Client = this->nh_.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
		mavros_msgs::SetMode Cmd;
		
		
		Cmd.request.base_mode = 0;
		Cmd.request.custom_mode = Mode.c_str();
		
		if(Client.call(Cmd))
		{
			if (Cmd.response.mode_sent)
			{
				ROS_INFO("Mode changed to %s.", Mode.c_str());
				
				ReturnBool = true;
			}
			else
			{
				ROS_ERROR("Mode-Change denied!");
			}
		}
		else
		{
			ROS_ERROR("Call denied!");
		}
	}
	else
	{
		ROS_ERROR("Mode-Change denied, not connected!");
	}
	
	return ReturnBool;
}

bool coexState::setArmState(bool arming)
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		std::string ShallState = (arming ? "armed" : "disarmed");
		
		
		if (arming != this->getArmed())
		{
			ros::ServiceClient Client = this->nh_.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
			mavros_msgs::CommandBool Cmd;
			
			
			Cmd.request.value = arming;
			Cmd.response.success = false;
			
			if(Client.call(Cmd))
			{
				if (Cmd.response.success)
				{
					ROS_INFO("Vehicle %s.", ShallState.c_str());
					
					ReturnBool = true;
				}
				else
				{
					ROS_ERROR("Arming denied!");
				}
			}
			else
			{
				ROS_ERROR("Call denied!");
			}
		}
		else
		{
			ROS_INFO("Vehicle already %s.", ShallState.c_str());
			
			ReturnBool = true;
		}
	}
	else
	{
		ROS_ERROR("Arming denied, not connected!");
	}
	
	return ReturnBool;
}



bool coexState::getArmed()
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		ReturnBool = this->State_.armed;
	}
	else
	{
		this->setArmState(false);
	}
	
	return ReturnBool;
}


std::string coexState::getSystemStatus()
{
	return this->getSystemStatus(this->State_.system_status);
}

std::string coexState::getSystemStatus(int StatusID)
{
	std::string ReturnString = "UNKNOWN?";
	std::map<int, std::string>::iterator it = this->SystemStatus_.find(StatusID);
	
	
	if (it != this->SystemStatus_.end())
	{
		ReturnString = it->second;
	}
	
	return ReturnString;
}


void coexState::cbState(const mavros_msgs::State::ConstPtr& State)
{
	if (State->connected != this->getConnected())
	{
		ROS_INFO("Vehicle %s.", (State->connected ? "connected" : "disconnected"));
	}
	
	if (State->mode != this->getMode())
	{
		ROS_INFO("Vehicle Mode changed to %s.", State->mode.c_str());
	}
	
	if (State->armed != this->getArmed())
	{
		ROS_INFO("Vehicle %s.", (State->armed ? "armed" : "disarmed"));
	}
	
	if (State->system_status != this->State_.system_status)
	{
		ROS_INFO("Vehicle SystemStatus changed to %s.", this->getSystemStatus(State->system_status).c_str());
	}
	
	this->State_ = *State;
	
	this->call();
}













void coexState::initSystemStatus()
{
	/* https://mavlink.io/en/messages/common.html#MAV_STATE
	 */
	SystemStatus_.insert(std::pair<int, std::string>(0, "Uninitialized"));
    SystemStatus_.insert(std::pair<int, std::string>(1, "Booting..."));
    SystemStatus_.insert(std::pair<int, std::string>(2, "Calibrating..."));
    SystemStatus_.insert(std::pair<int, std::string>(3, "Grounded + Standby"));
    SystemStatus_.insert(std::pair<int, std::string>(4, "Active + Motors engaged"));
    SystemStatus_.insert(std::pair<int, std::string>(5, "Non-Flight + Navigating..."));
    SystemStatus_.insert(std::pair<int, std::string>(6, "Non-Flight + Lost Control"));
    SystemStatus_.insert(std::pair<int, std::string>(7, "Shutdown Sqeunce..."));
    SystemStatus_.insert(std::pair<int, std::string>(8, "Terminating..."));
}









