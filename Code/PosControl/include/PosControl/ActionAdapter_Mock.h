#ifndef ACTIONADAPTER_H
#define ACTIONADAPTER_H

#include "Transmitable.h"

#include "ActionDirection.h"
#include "ControllerType.h"
#include "State.h"


class ActionAdapter
{
public:
	ActionAdapter(Transmitable *Transmitable);

	bool setPos_Abs(double X, double Y, double Z);
	bool setPos_Diff(double DiffX, double DiffY, double DiffZ);
	bool setK(ActionDirection Direction, ControllerType Type, double K);

	void addState(State Entry);

private:
	Transmitable *ActionReceiver_;

	double SaveX = 0, SaveY = 0, SaveZ = 0;
};

#endif // ACTIONADAPTER_H


