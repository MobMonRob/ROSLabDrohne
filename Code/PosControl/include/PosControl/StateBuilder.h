#ifndef STATEBUILDER_H
#define STATEBUILDER_H


#include "Application/State.h"
#include "Application/StateHandler.h"
#include "Adapter/ActionAdapter.h"
#include "calling/Callable.h"
#include "coex/coexControl.h"


class StateBuilder : public Callable
{
public:
	StateBuilder(coexControl* Controller, ActionAdapter *Actions);
	~StateBuilder();

	State translateState(State State);
	bool call(Calling* Caller) override;

private:
	void createHandler();
	void deleteHandler();
	
private:
	coexControl *Controller_;
	ActionAdapter *Actions_;

	StateHandler *Handler_ = nullptr;
	State StateAvg_;
};

#endif // STATEBUILDER_H
