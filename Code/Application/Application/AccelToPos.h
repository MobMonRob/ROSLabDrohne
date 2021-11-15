#ifndef ACCELTOPOS_H
#define ACCELTOPOS_H

<<<<<<< HEAD
#include "Value.h"
#include "Outputable.h"
#include "Controller_Input.h"
#include "Controller_I.h"
=======
#include <Value.h>
#include <Outputable.h>
#include <Controller_Input.h>
#include <Controller_I.h>
>>>>>>> devel_app


class AccelToPos : Outputable
{
public:
	AccelToPos(double InitPos = 0.0, double InitVel = 0.0);
<<<<<<< HEAD

	/*
=======
<<<<<<< Updated upstream




=======
>>>>>>> Stashed changes

>>>>>>> devel_app
	bool setInput(Value V) { return this->Input_.setInput(V); };

	Value getOutputValue() { return this->VelToPos_.getOutputValue(); };
	Unit getOutputUnit() { return this->VelToPos_.getOutputUnit(); };

private:
	Controller_Input Input_;
	Controller_I AccelToVel_;
	Controller_I VelToPos_;
<<<<<<< HEAD
	*/
=======
>>>>>>> devel_app
};

#endif // ACCELTOPOS_H
