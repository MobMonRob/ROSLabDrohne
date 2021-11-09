#ifndef ACCELTOPOS_H
#define ACCELTOPOS_H

#include <Value.h>
#include <Outputable.h>
#include <Controller_Input.h>
#include <Controller_I.h>


class AccelToPos : Outputable
{
public:
	AccelToPos(double InitPos = 0.0, double InitVel = 0.0);
<<<<<<< Updated upstream

	/*
	bool setInput(Value V) { return this->Input_.setInput(V); };

	Value getOutputValue() { return this->VelToPos_.getOutputValue(); };
	Unit getOutputUnit() { return this->VelToPos_.getOutputUnit(); };


=======
>>>>>>> Stashed changes

	bool setInput(Value V) { return this->Input_.setInput(V); };

	Value getOutputValue() { return this->VelToPos_.getOutputValue(); };
	Unit getOutputUnit() { return this->VelToPos_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I AccelToVel_;
	Controller_I VelToPos_;
};

#endif // ACCELTOPOS_H
