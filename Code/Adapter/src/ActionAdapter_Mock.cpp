#ifdef DEBUG
#include "Adapter/ActionAdapter_Mock.h"





ActionAdapter::ActionAdapter(Transmitable *Transmitable)
	: ActionReceiver_(Transmitable)
{
}





bool ActionAdapter::setPos_Abs(double X, double Y, double Z)
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

bool ActionAdapter::setPos_Diff(double DiffX, double DiffY, double DiffZ)
{
	SaveX += DiffX;
	SaveY += DiffY;
	SaveZ += DiffZ;

	return this->setPos_Abs(SaveX, SaveY, SaveZ);
}


bool ActionAdapter::setK(ActionDirection Direction, ControllerType Type, double K)
{
	return true;
}





void ActionAdapter::addState(State Entry)
{
	
}

#endif

