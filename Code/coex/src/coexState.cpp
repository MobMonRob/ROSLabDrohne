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
	: Battery_(Battery),
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

	ROS_INFO("Terminated coexState");
	ros::spinOnce();
}


bool coexState::operator==(const mavros_msgs::State& S)
{
	bool ReturnBool = true;


	ReturnBool &= this->getConnected() == S.connected;
	ReturnBool &= this->getArmState() == S.armed;
	ReturnBool &= this->getGuided() == S.guided;
	ReturnBool &= this->getManualInput() == S.manual_input;
	ReturnBool &= this->getMode() == S.mode;
	ReturnBool &= this->getSystemStatusID() == S.system_status;

	return false;
}


bool coexState::setMode(std::string Mode)
{
	bool ReturnBool = false;
	
	
	if (this->getConnected())
	{
		ros::ServiceClient Client = this->nh_.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
		mavros_msgs::SetMode Cmd;
		
		
		Cmd.request.custom_mode = Mode.c_str();
		
		if (Client.call(Cmd))
		{
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

std::string coexState::getState()
{
	std::string ReturnString = "PrintOut State at ";
	std::string NL = "\n";
	std::string Tab = "\t";


	ReturnString.append(std::to_string(this->getTime())).append(NL);
	ReturnString.append(Tab).append((this->getConnected() ? "" : "not ")).append("connected").append(NL);
	ReturnString.append(Tab).append((this->getArmState() ? "" : "not ")).append("armed").append(NL);
	ReturnString.append(Tab).append((this->getGuided() ? "" : "not ")).append("guided").append(NL);
	ReturnString.append(Tab).append((this->getManualInput() ? "" : "not ")).append("manually inputed").append(NL);
	ReturnString.append(Tab).append("Mode: ").append(this->getMode()).append(NL);
	ReturnString.append(Tab).append(this->getSystemStatus());

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









