#include <PosControl/StateBuilder.h>


#include <ros/time.h>

//State CurrentState;




StateBuilder::StateBuilder(coexControl* Controller, ActionAdapter *Actions)
	: Controller_(Controller),
	Actions_(Actions)
{
	ROS_INFO("Started StateBuilder");
	
}

StateBuilder::~StateBuilder()
{
	this->deleteHandler();
}



State StateBuilder::translateState(State InState)
{
	State StateAvg = this->StateAvg_;


	if (this->Handler_ != nullptr)
	{
		StateAvg = this->Handler_->getAvgState();
	}

	return InState - StateAvg;
}




bool StateBuilder::call(Calling* Caller)
{
	Vector3D Linear = this->Controller_->getPosLinear();
	Vector3D Angular = this->Controller_->getPosAngular();
	Value GroundClearance(Unit_Length, this->Controller_->getGroundClearance());
	Timestamp Time(this->Controller_->getTime());
	State BuildingState(Linear, Angular, GroundClearance, Time);


	if (this->Controller_->getArmed())
	{
		this->deleteHandler();

		Actions_->addState(BuildingState);
	}
	else
	{
		this->createHandler();

		this->Handler_->addEntry(BuildingState);
	}

	return true;
}






void StateBuilder::createHandler()
{
	if (this->Handler_ == nullptr)
	{
		this->Handler_ = new StateHandler(100);
	}
}

void StateBuilder::deleteHandler()
{
	if (this->Handler_ != nullptr)
	{
		this->StateAvg_ = this->Handler_->getAvgState();

		delete this->Handler_;
		this->Handler_ = nullptr;
	}
}





