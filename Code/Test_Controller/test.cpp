#include "pch.h"



#include "Controller/Header.h"

#include "MockTransmitable.h"







TEST(Class_PoseController, callTransmitter)
{

	MockTransmitable Transmitter;
	{	// Train Mock
		ON_CALL(Transmitter, transmitAction(testing::_, testing::_, testing::_, testing::_)).WillByDefault(testing::Return(true));
		EXPECT_CALL(Transmitter, transmitAction).Times(1);
	}
	PoseController PC(&Transmitter);

	Timestamp Pose_Time(0.0);
	Vector3D Pose_Position(Unit_Length);
	Vector3D Pose_Orientation(Unit_Length);
	Pose P(Pose_Time, Pose_Position, Pose_Orientation);


	std::cout << "TransmitterAddress = " << &Transmitter << std::endl;


	bool Result = PC.feedbackPose(P);
}