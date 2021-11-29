#ifndef ACTIONADAPTER_H
#define ACTIONADAPTER_H




#include "PosControl/ControllerSystem.h"

#include "PosControl/AccelToPos.h"
#include "PosControl/StateHandler.h"

#include "PosControl/Transmitable.h"


enum ActionDirection
{
	DirX,
	DirY,
	DirZ

};


class ActionAdapter
{
public:
	ActionAdapter(Transmitable Transmitable);

	bool setPos_Abs(double X, double Y, double Z);
	bool setPos_Diff(double DiffX, double DiffY, double DiffZ);

	bool setK_Abs(ActionDirection Direction, ControllerType Type, double K);






	void addState(State Entry);





private:
	Transmitable ActionReceiver_;
	StateHandler StateHandler_;

	AccelToPos PosX_;
	AccelToPos PosY_;
	AccelToPos PosZ_;

	ControllerSystem ControlX_;
	ControllerSystem ControlY_;
	ControllerSystem ControlZ_;
};

#endif // ACTIONADAPTER_H
