
#include <iostream>
#include <string>

#include "parrot/parrotIMU.h"
#include "parrot/parrotTransmitter.h"

#include "BagPlotter/DataCollector.h"
#include "BagPlotter/DataLoader.h"
#include "BagPlotter/DataPersister.h"

#include "PosControl/PoseBuilder.h"
#include "Controller/PoseController.h"

#include "ardrone_autonomy/Navdata.h"



void createNavData(DataCollector* NavDataCollector, size_t Index, ardrone_autonomy::Navdata* NavDataMsg)
{
    if (NavDataCollector->isData(Index, "Time"))
    {
        NavDataMsg->header.stamp = ros::Time(std::atof(NavDataCollector->getData(Index, "Time").c_str()));
    }

    if (NavDataCollector->isData(Index, "State"))
    {
        NavDataMsg->state = std::atoi(NavDataCollector->getData(Index, "State").c_str());
    }

    if (NavDataCollector->isData(Index, "ax"))
    {
        NavDataMsg->ax = std::atof(NavDataCollector->getData(Index, "ax").c_str());
    }
    if (NavDataCollector->isData(Index, "ay"))
    {
        NavDataMsg->ay = std::atof(NavDataCollector->getData(Index, "ay").c_str());
    }
    if (NavDataCollector->isData(Index, "az"))
    {
        NavDataMsg->az = std::atof(NavDataCollector->getData(Index, "az").c_str());
    }

    if (NavDataCollector->isData(Index, "rx"))
    {
        NavDataMsg->rotX = std::atof(NavDataCollector->getData(Index, "rx").c_str());
    }
    if (NavDataCollector->isData(Index, "ry"))
    {
        NavDataMsg->rotY = std::atof(NavDataCollector->getData(Index, "ry").c_str());
    }
    if (NavDataCollector->isData(Index, "rz"))
    {
        NavDataMsg->rotZ = std::atof(NavDataCollector->getData(Index, "rz").c_str());
    }

    if (NavDataCollector->isData(Index, "h"))
    {
        NavDataMsg->altd = std::atol(NavDataCollector->getData(Index, "h").c_str());
    }

    if (NavDataCollector->isData(Index, "Rotors"))
    {
        NavDataMsg->motor1 = std::atol(NavDataCollector->getData(Index, "Rotors").c_str());
    }
}

void addDataset(DataCollector* Collector, IMUState State)
{
    Collector->addDataset();
    Collector->addEntry("Time", std::to_string(State.getTimestamp().getTime().getValue()));

    Collector->addEntry("ax", std::to_string(State.getLinear().getX().getValue()));
    Collector->addEntry("ay", std::to_string(State.getLinear().getY().getValue()));
    Collector->addEntry("az", std::to_string(State.getLinear().getZ().getValue()));

    Collector->addEntry("rx", std::to_string(State.getRotational().getX().getValue()));
    Collector->addEntry("ry", std::to_string(State.getRotational().getY().getValue()));
    Collector->addEntry("rz", std::to_string(State.getRotational().getZ().getValue()));

    Collector->addEntry("Height", std::to_string(State.getGroundClearance().getValue().getValue()));
}

void addDataset(DataCollector* Collector, Pose Pose, Vector3D Velocity)
{
    Collector->addDataset();
    Collector->addEntry("Time", std::to_string(Pose.getTime().getTime().getValue()));

    Collector->addEntry("px", std::to_string(Pose.getPosition().getX().getValue()));
    Collector->addEntry("py", std::to_string(Pose.getPosition().getY().getValue()));
    Collector->addEntry("pz", std::to_string(Pose.getPosition().getZ().getValue()));

    Collector->addEntry("vx", std::to_string(Velocity.getX().getValue()));
    Collector->addEntry("vy", std::to_string(Velocity.getY().getValue()));
    Collector->addEntry("vz", std::to_string(Velocity.getZ().getValue()));

    Collector->addEntry("rx", std::to_string(Pose.getOrientation().getX().getValue()));
    Collector->addEntry("ry", std::to_string(Pose.getOrientation().getY().getValue()));
    Collector->addEntry("rz", std::to_string(Pose.getOrientation().getZ().getValue()));
}

void addDataset(DataCollector* Collector, parrotStatus* Status, parrotIMU* IMU, StateBuilder* StateBuild, PoseBuilder* PoseBuild)
{
    Collector->addDataset();
    Collector->addEntry("Time", std::to_string(Status->getTime().getTime().getValue()));
    Collector->addEntry("Status_StatusID", std::to_string(Status->getStatusID()));
    Collector->addEntry("Status_Ground", std::to_string(Status->isGrounded()));
    Collector->addEntry("Status_Flight", std::to_string(Status->isFlying()));

    Collector->addEntry("IMU_Valíd", std::to_string(IMU->getValidFlag()));

    Collector->addEntry("State_Valid", std::to_string(StateBuild->getValidFlag()));
    Collector->addEntry("State_Offsetting", std::to_string(StateBuild->getOffsettingFlag()));

    Collector->addEntry("Pose_Valid", std::to_string(PoseBuild->getValidFlag()));
    Collector->addEntry("Pose_Calibration", std::to_string(PoseBuild->getCalibrationFlag()));
    Collector->addEntry("Pose_Calculation", std::to_string(PoseBuild->getCalculationFlag()));
}



std::string getString(ardrone_autonomy::Navdata* NavDataMsg)
{
    std::string ReturnString;


    ReturnString.append("Time=").append(std::to_string(NavDataMsg->header.stamp.toSec())).append(";");
    
    ReturnString.append("State=").append(std::to_string(NavDataMsg->state)).append(";");

    ReturnString.append("ax=").append(std::to_string(NavDataMsg->ax)).append(";");
    ReturnString.append("ay=").append(std::to_string(NavDataMsg->ay)).append(";");
    ReturnString.append("az=").append(std::to_string(NavDataMsg->az)).append(";");
    
    ReturnString.append("rx=").append(std::to_string(NavDataMsg->rotX)).append(";");
    ReturnString.append("ry=").append(std::to_string(NavDataMsg->rotY)).append(";");
    ReturnString.append("rz=").append(std::to_string(NavDataMsg->rotZ)).append(";");
    
    ReturnString.append("Height=").append(std::to_string(NavDataMsg->altd)).append(";");

    return ReturnString;
}










int main()
{
    std::cout << "Hello World!\n";

    std::string FilePath = "C:\\Users\\maag\\Documents\\Maag\\Studium\\T3100\\Analyse\\Parrot\\";
    //std::string FileName = "Bag 220426_Flight_Backward_Forward";
    std::string FileName = "Bag 220423_Hover";
    std::string FilePath_Input = std::string(FilePath).append(FileName).append(".txt");
    std::string FilePath_Output_State = std::string(FilePath).append(FileName).append(" State.txt");
    std::string FilePath_Output_Pose = std::string(FilePath).append(FileName).append(" Pose.txt");
    std::string FilePath_Output_Flags = std::string(FilePath).append(FileName).append(" Flags.txt");
    DataCollector DataInput;
    DataCollector DataState;
    DataCollector DataPose;
    DataCollector DataFlags;

    
    parrotTransmitter Transmitter;
    PoseBuilder PoseBuild;
    PoseController PC(&Transmitter);
    parrotIMU IMU(&PoseBuild, &PC);
    parrotStatus Status(&IMU);

    {   // Init
        {   // Wire the Safety Stuff
            Status.addReceiver(&IMU);
            //IMU.addReceiver(&Status);
        }
        
        {   // Prepare DataState
            DataState.addKey("Time");
            DataState.addKey("ax");
            DataState.addKey("ay");
            DataState.addKey("az");
            DataState.addKey("rx");
            DataState.addKey("ry");
            DataState.addKey("rz");
            DataState.addKey("Height");
        }

        {   // Prepare DataPose
            DataPose.addKey("Time");
            DataPose.addKey("px");
            DataPose.addKey("py");
            DataPose.addKey("pz");
            DataPose.addKey("vx");
            DataPose.addKey("vy");
            DataPose.addKey("vz");
            DataPose.addKey("rx");
            DataPose.addKey("ry");
            DataPose.addKey("rz");
        }

        {   // Prepare DataFlags
            DataFlags.addKey("Time");
            DataFlags.addKey("Status_StatusID");
            DataFlags.addKey("Status_Ground");
            DataFlags.addKey("Status_Flight");
            DataFlags.addKey("IMU_Valíd");
            DataFlags.addKey("State_Valid");
            DataFlags.addKey("State_Offsetting");
            DataFlags.addKey("Pose_Valid");
            DataFlags.addKey("Pose_Calibration");
            DataFlags.addKey("Pose_Calculation");
        }

        {   // Load DataInput
            DataLoader Loader(&DataInput, FilePath_Input);
        }

        IMU.setFlightState(false);
    }

    {   // Simulation
        for (int i = 0; i < DataInput.getSize(); i++)
        {
            //std::cout << "Working on Dataset " << i << std::endl;

            if (i == DataInput.getSize() - 5)
            {
                //IMU.setFlightState(true);
            }

            if ((i == 957 && FileName == "Bag 220426_Flight_Backward_Forward") ||
                (i == 1415 && FileName == "Bag 220423_Hover"))
            {
                IMU.calibrate();
            }


            {   // Build NavData-Message and push to IMU
                ardrone_autonomy::Navdata NavDataMsg;


                createNavData(&DataInput, i, &NavDataMsg);

                Status.callbackNavdata(&NavDataMsg);
                IMU.callbackNavdata(&NavDataMsg);
            }

            {   // Get IMU-Data
                addDataset(&DataState, IMU.getState());
                addDataset(&DataPose, IMU.getPose(), PoseBuild.getVelocity());
                addDataset(&DataFlags, &Status, &IMU, IMU.getStatebuilder(), &PoseBuild);
            }
        }
    }

    {   // Persist
        std::cout << DataInput.getString(0, 1, true) << "..." << std::endl;
        std::cout << DataInput.getString(DataInput.getSize()-2, DataInput.getSize(), false) << std::endl;
        
        DataPersister::persist(&DataState, FilePath_Output_State);
        DataPersister::persist(&DataPose, FilePath_Output_Pose);
        DataPersister::persist(&DataFlags, FilePath_Output_Flags);
    }

    {   // Analysis
        std::cout << "OffsetState: " << IMU.getStateOffset().getString() << std::endl;
        std::cout << "OffsetPose: " << IMU.getPoseOffsetAcceleration().getString() << std::endl;

    }
}