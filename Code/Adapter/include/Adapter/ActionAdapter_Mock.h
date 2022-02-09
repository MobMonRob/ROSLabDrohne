#ifndef ACTIONADAPTER_MOCK_H
#define ACTIONADAPTER_MOCK_H

#include "Domain/ControllerType.h"
#include "Application/State.h"

#include "Adapter/Transmitable.h"
#include "Adapter/ActionDirection.h"


class ActionAdapter_Mock
{
public:
	ActionAdapter_Mock(Transmitable *Transmitable);

	bool setPos_Abs(double X, double Y, double Z);
	bool setPos_Diff(double DiffX, double DiffY, double DiffZ);
	bool setK(ActionDirection Direction, ControllerType Type, double K);

	void addState(State Entry);

private:
	Transmitable *ActionReceiver_;

	double SaveX = 0, SaveY = 0, SaveZ = 0;
};

#endif // ACTIONADAPTER_MOCK_H


