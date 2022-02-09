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




coexState::coexState(coexBattery* Battery, bool silent)
	: ClMode_("mavros/set_mode", 10),
	Battery_(Battery),
	silent_(silent)
{
	ROS_INFO("Started coexState");

	coex_State = this;
	
	this->initSystemStatus();
	
	this->SubState_ = this->nh_.subscribe("mavros/state", 10, callbackState);
}

coexState::~coexState()
{
	ROS_INFO("Termintating coexState...");

	this->setModeAuto(false);

	ROS_INFO("Terminated coexState");
}


bool coexState::setMode(std::string Mode)
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		mavros_msgs::SetMode Cmd;
		
		
		Cmd.request.base_mode = 0;
		Cmd.request.custom_mode = Mode.c_str();
		
		this->setModeAuto(false);
		Cmd = this->ClMode_.setPayload(Cmd);
		this->setModeAuto(Mode == coexMode_Offboard);
		ros::spinOnce();

		if (Cmd.response.mode_sent)
		{
			ReturnBool = true;
		}
		else
		{
			ROS_ERROR("Mode-Change denied!");

			if (this->Battery_->getPercentageLow())
			{
				ROS_INFO("Possible cause: Battery low.");
			}
		}
	}
	else
	{
		ROS_ERROR("Mode-Change denied, not connected!");
	}
	
	return ReturnBool;
}


void coexState::setModeAuto(bool AutoMode)
{
	if (AutoMode)
	{
		this->ClMode_.start();
	}
	else
	{
		this->ClMode_.stop();
	}
}


bool coexState::setArmState(bool arming)
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		if (!arming || this->getMode() == coexMode_Offboard)
		{
			ros::ServiceClient Client = this->nh_.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
			mavros_msgs::CommandBool Cmd;
			
			
			Cmd.request.value = arming;
			
			if(Client.call(Cmd))
			{
				ros::spinOnce();

				if (Cmd.response.success)
				{
					ReturnBool = true;
				}
				else
				{
					ROS_WARN("Arming denied!");
				}
			}
			else
			{
				ROS_ERROR("Call denied!");
			}
		}
	}
	else
	{
		ROS_ERROR("Arming denied, not connected!");
	}
	
	return ReturnBool;
}




bool coexState::getConnected()
{
	bool ReturnBool = this->State_.connected;


	if (!ReturnBool)
	{
		this->setModeAuto(false);
	}

	return ReturnBool;
}

bool coexState::getArmState()
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
	return this->getSystemStatus(this->getSystemStatusID());
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

void coexState::waitNextState()
{
	double Time = this->getTime();


	while (ros::ok() && Time == this->getTime())
	{
		ros::spinOnce();
	}
}



void coexState::cbState(const mavros_msgs::State::ConstPtr& State)
{
	if (!this->silent_)
	{
		if (State->connected != this->getConnected())
		{
			ROS_INFO("Vehicle %s.", (State->connected ? "connected" : "disconnected"));
		}

		if (State->mode != this->getMode())
		{
			ROS_INFO("Vehicle Mode changed to %s.", State->mode.c_str());
		}

		if (State->armed != this->getArmState())
		{
			ROS_INFO("Vehicle %s.", (State->armed ? "armed" : "disarmed"));
		}

		if (State->system_status != this->State_.system_status)
		{
			ROS_INFO("Vehicle SystemStatus changed to %s.", this->getSystemStatus(State->system_status).c_str());
		}
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









