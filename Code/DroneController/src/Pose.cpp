#include "DroneController/Pose.h"


Pose::Pose(Timestamp Time, Vector3D Position, Vector3D Orientation, Vector3D PositionUncertainty, Vector3D OrientationUncertainty)
	: Time_(Time),
	Position_(Position),
	Orientation_(Orientation),
	PositionUncertainty_(PositionUncertainty),
	OrientationUncertainty_(OrientationUncertainty)
{
}

std::string Pose::getString()
{
	std::string Returnstring = "Pose: [[";
	Vector3D Position = this->getPosition();
	Vector3D Orientation = this->getOrientation();


	Returnstring.append(std::to_string(Position.getX().getValue())).append(", ");
	Returnstring.append(std::to_string(Position.getY().getValue())).append(", ");
	Returnstring.append(std::to_string(Position.getZ().getValue())).append("], [");

	Returnstring.append(std::to_string(Orientation.getX().getValue())).append(", ");
	Returnstring.append(std::to_string(Orientation.getY().getValue())).append(", ");
	Returnstring.append(std::to_string(Orientation.getZ().getValue())).append("]]");

	return Returnstring;
}




