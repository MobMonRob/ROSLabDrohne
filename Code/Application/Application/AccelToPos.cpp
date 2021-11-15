#include "AccelToPos.h"


AccelToPos::AccelToPos(double InitPos, double InitVel)
	: Outputable(Unit("m"))/*,
	Input_(Unit("m/s²")),
	AccelToVel_(Unit("m/s²"), Unit("m/s"), 1.0),
	VelToPos_(Unit("m/s"), Unit("m"), 1.0)*/
{
	/*
	this->AccelToVel_.setIntputAddr(&this->Input_);
	// set Sum to InitVel

	this->VelToPos_.setIntputAddr(&this->AccelToVel_);
	// set Sum to InitPos
	*/
}

