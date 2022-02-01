#include "coex/Joystick.h"


Joystick::Joystick(double Roll_Min, double Roll_Max,
		double Pitch_Min, double Pitch_Max,
		double Thrust_Min, double Thrust_Max,
		double Yarn_Min, double Yarn_Max)
	: Roll_(Roll_Min, Roll_Max),
	Pitch_(Pitch_Min, Pitch_Max),
	Thrust_(Thrust_Min, Thrust_Max),
	Yarn_(Yarn_Min, Yarn_Max)
{
}

Joystick::Joystick(double Roll_Min, double Roll_Max, double Roll_Middle,
		double Pitch_Min, double Pitch_Max, double Pitch_Middle,
		double Thrust_Min, double Thrust_Max, double Thrust_Middle,
		double Yarn_Min, double Yarn_Max, double Yarn_Middle)
	: Roll_(Roll_Min, Roll_Max, Roll_Middle),
	Pitch_(Pitch_Min, Pitch_Max, Pitch_Middle),
	Thrust_(Thrust_Min, Thrust_Max, Thrust_Middle),
	Yarn_(Yarn_Min, Yarn_Max, Yarn_Middle)
{
}

mavros_msgs::ManualControl Joystick::normalize(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::ManualControl ReturnMsg;
	
	
	// For Intervalls see Header File!
	ReturnMsg.x = this->Pitch_.normalize(Msg.x);
	ReturnMsg.y = this->Roll_.normalize(Msg.y);
	ReturnMsg.z = (this->Thrust_.normalize(Msg.z) + 1) / 2;
	ReturnMsg.r = this->Yarn_.normalize(Msg.r);
	
	return ReturnMsg;
}

mavros_msgs::ManualControl Joystick::normalize(mavros_msgs::RCIn Msg)
{
	return this->normalize(Msg, 0, 1, 2, 3);
}

mavros_msgs::ManualControl Joystick::normalize(mavros_msgs::RCIn Msg, int Ch_Roll, int Ch_Pitch, int CH_Thrust, int Ch_Yarn)
{
	mavros_msgs::ManualControl ReturnMsg;
	
	
	ReturnMsg.x = Msg.channels[Ch_Pitch];
	ReturnMsg.y = Msg.channels[Ch_Roll];
	ReturnMsg.z = Msg.channels[CH_Thrust];
	ReturnMsg.r = Msg.channels[Ch_Yarn];
	
	return this->normalize(ReturnMsg);
}


mavros_msgs::ManualControl Joystick::denormalize(double Pitch, double Roll, double Thrust, double Yarn)
{
	mavros_msgs::ManualControl ReturnMsg;
	
	
	ReturnMsg.x = Pitch;
	ReturnMsg.y = Roll;
	ReturnMsg.z = Thrust;
	ReturnMsg.r = Yarn;
	
	return this->denormalize(ReturnMsg);
}

mavros_msgs::ManualControl Joystick::denormalize(mavros_msgs::ManualControl Msg)
{
	mavros_msgs::ManualControl ReturnMsg;
	
	
	// For Intervalls see Header File!
	ReturnMsg.x = this->Pitch_.denormalize(Msg.x);
	ReturnMsg.y = this->Roll_.denormalize(Msg.y);
	ReturnMsg.z = (this->Thrust_.denormalize(Msg.z) * 2) - 1;
	ReturnMsg.r = this->Yarn_.denormalize(Msg.r);
	
	return ReturnMsg;
}

