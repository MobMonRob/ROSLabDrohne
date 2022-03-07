#ifndef CONTROLLERMAIN_H
#define CONTROLLERMAIN_H


#include "Application/State.h"
#include "Application/Transmitable.h"

#include "Application/StateBuilder.h"
#include "Application/StateHandler.h"
#include "Application/PoseBuilder.h"
#include "Application/PoseController.h"


class ControllerMain
{
public:
	ControllerMain(Transmitable* Transmitter);

	State getStateAvg() { return this->StateHandler_.getAvgState(); };

	void updatePose(State S);
	void clearStateHandler() { this->StateHandler_.clear(); };

private:
	StateHandler StateHandler_;
	PoseBuilder PoseBuilder_;
	PoseController PoseController_;
};

#endif // CONTROLLERMAIN_H
