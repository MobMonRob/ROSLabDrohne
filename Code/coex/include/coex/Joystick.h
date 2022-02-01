#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/RCIn.h>

#include "JoystickAxis.h"

/*
 *	https://mavlink.io/en/services/manual_control.html 		this Intervall
 *	x	pitch	forward/nose-down	backward/nose-up		-1 ... 1
 *	y	roll	right-down			left-down				-1 ... 1
 *	z	thrust	positive			negative				 0 ... 1
 *	r	yaw		counter-clockwise	clockwise				-1 ... 1
 */


class Joystick
{
public:
	Joystick(double Roll_Min, double Roll_Max,
			double Pitch_Min, double Pitch_Max,
			double Thrust_Min, double Thrust_Max,
			double Yarn_Min, double Yarn_Max);
	Joystick(double Roll_Min, double Roll_Max, double Roll_Middle,
			double Pitch_Min, double Pitch_Max, double Pitch_Middle,
			double Thrust_Min, double Thrust_Max, double Thrust_Middle,
			double Yarn_Min, double Yarn_Max, double Yarn_Middle);
	
	
	mavros_msgs::ManualControl normalize(mavros_msgs::ManualControl Msg);
	mavros_msgs::ManualControl normalize(mavros_msgs::RCIn Msg);
	mavros_msgs::ManualControl normalize(mavros_msgs::RCIn Msg, int Ch_Roll, int Ch_Pitch, int CH_Thrust, int Ch_Yarn);
	mavros_msgs::ManualControl denormalize(double pitch, double roll, double thrust, double yarn);
	mavros_msgs::ManualControl denormalize(mavros_msgs::ManualControl Msg);
	
private:
	JoystickAxis Roll_;
	JoystickAxis Pitch_;
	JoystickAxis Thrust_;
	JoystickAxis Yarn_;
};

#endif // JOYSTICK_H


