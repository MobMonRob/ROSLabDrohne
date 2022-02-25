#include "Adapter/ActionAdapter_Mock.h"

#include <iostream>



ActionAdapter_Mock::ActionAdapter_Mock(Transmitable *Transmitable)
	: ActionReceiver_(Transmitable)
{
	std::cout << "using ActionAdapter_Mock..." << std::endl;
}





bool ActionAdapter_Mock::setPos_Abs(double X, double Y, double Z)
{
	SaveX = X;
	SaveY = Y;
	SaveZ = Z;
	
	if (SaveZ < 0)
	{
		SaveZ = 0;
	}

	this->ActionReceiver_->transmitAction(SaveX, SaveY, SaveZ, 0);

	return true;
}

bool ActionAdapter_Mock::setPos_Diff(double DiffX, double DiffY, double DiffZ)
{
	SaveX += DiffX;
	SaveY += DiffY;
	SaveZ += DiffZ;

	return this->setPos_Abs(SaveX, SaveY, SaveZ);
}


bool ActionAdapter_Mock::setK(ActionDirection Direction, ControllerType Type, double K)
{
	return true;
}





void ActionAdapter_Mock::addState(State Entry)
{
	
}


