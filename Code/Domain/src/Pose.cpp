#include "Domain/Pose.h"


Pose::Pose(Timestamp Time, Vector3D Position, Vector3D Orientation, Vector3D PositionUncertainty, Vector3D OrientationUncertainty)
	: Time_(Time),
	Position_(Position),
	Orientation_(Orientation),
	PositionUncertainty_(PositionUncertainty),
	OrientationUncertainty_(OrientationUncertainty)
{
}

