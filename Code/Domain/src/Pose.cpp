#include "Domain/Pose.h"


Pose::Pose(Vector3D Position, Vector3D Orientation, Vector3D PositionUncertainty, Vector3D OrientationUncertainty)
	: Position_(Position),
	Orientation_(Orientation),
	PositionUncertainty_(PositionUncertainty),
	OrientationUncertainty_(OrientationUncertainty)
{
}

