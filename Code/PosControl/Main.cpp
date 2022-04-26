
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
        NavDataMsg->altd = std::atof(NavDataCollector->getData(Index, "h").c_str());
    }
}

void addDataset(DataCollector* StateCollector, IMUState State)
{
    StateCollector->addDataset();
    StateCollector->addEntry("Time", std::to_string(State.getTimestamp().getTime().getValue()));

    StateCollector->addEntry("ax", std::to_string(State.getLinear().getX().getValue()));
    StateCollector->addEntry("ay", std::to_string(State.getLinear().getY().getValue()));
    StateCollector->addEntry("az", std::to_string(State.getLinear().getZ().getValue()));

    StateCollector->addEntry("rx", std::to_string(State.getRotational().getX().getValue()));
    StateCollector->addEntry("ry", std::to_string(State.getRotational().getY().getValue()));
    StateCollector->addEntry("rz", std::to_string(State.getRotational().getZ().getValue()));

    StateCollector->addEntry("Height", std::to_string(State.getGroundClearance().getValue().getValue()));
}

void addDataset(DataCollector* PoseCollector, Pose Pose)
{
    PoseCollector->addDataset();
    PoseCollector->addEntry("Time", std::to_string(Pose.getTime().getTime().getValue()));

    PoseCollector->addEntry("px", std::to_string(Pose.getPosition().getX().getValue()));
    PoseCollector->addEntry("py", std::to_string(Pose.getPosition().getY().getValue()));
    PoseCollector->addEntry("pz", std::to_string(Pose.getPosition().getZ().getValue()));

    PoseCollector->addEntry("rx", std::to_string(Pose.getOrientation().getX().getValue()));
    PoseCollector->addEntry("ry", std::to_string(Pose.getOrientation().getY().getValue()));
    PoseCollector->addEntry("rz", std::to_string(Pose.getOrientation().getZ().getValue()));
}


std::string getString(ardrone_autonomy::Navdata* NavDataMsg)
{
    std::string ReturnString;


    ReturnString.append("Time=").append(std::to_string(NavDataMsg->header.stamp.toSec())).append(";");
    
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

    std::string FilePath_Input = "C:\\Users\\maag\\Documents\\Maag\\Studium\\T3100\\Analyse\\Parrot\\Bag 220423_Hover.txt";
    std::string FilePath_Output_State = "C:\\Users\\maag\\Documents\\Maag\\Studium\\T3100\\Analyse\\Parrot\\Bag 220423_Hover State.txt";
    std::string FilePath_Output_Pose = "C:\\Users\\maag\\Documents\\Maag\\Studium\\T3100\\Analyse\\Parrot\\Bag 220423_Hover Pose.txt";
    DataCollector DataInput;
    DataCollector DataState;
    DataCollector DataPose;

    parrotTransmitter Transmitter;
    PoseBuilder PoseBuild;
    PoseController PC(&Transmitter);
    parrotIMU IMU(&PoseBuild, &PC);


    {   // Init
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
            DataPose.addKey("rx");
            DataPose.addKey("ry");
            DataPose.addKey("rz");
        }

        {   // Load DataInput
            DataLoader Loader(&DataInput, FilePath_Input);
        }

        IMU.setFlightState(false);
    }

    {   // Simulation
        for (int i = 0; i < DataInput.getSize(); i++)
        {
            if (i > 10)
            {
                IMU.setFlightState(true);
            }


            {   // Build NavData-Message and push to IMU
                ardrone_autonomy::Navdata NavDataMsg;


                createNavData(&DataInput, i, &NavDataMsg);

                IMU.callbackNavdata(&NavDataMsg);
            }

            {   // Get IMU-Data
                addDataset(&DataState, IMU.getState());
                addDataset(&DataPose, IMU.getPose());
            }
        }
    }

    {   // Persist
        std::cout << DataInput.getString(0, 1, true) << "..." << std::endl;
        std::cout << DataInput.getString(DataInput.getSize()-2, DataInput.getSize(), false) << std::endl;
        
        DataPersister::persist(&DataState, FilePath_Output_State);
        std::cout << DataState.getString(0, 1, true) << "..." << std::endl;
        std::cout << DataState.getString(DataState.getSize() - 2, DataState.getSize(), false) << std::endl;

        DataPersister::persist(&DataPose, FilePath_Output_Pose);
        std::cout << DataPose.getString(0, 1, true) << "..." << std::endl;
        std::cout << DataPose.getString(DataPose.getSize() - 2, DataPose.getSize(), false) << std::endl;
    }

    {   // Analysis
        std::cout << "OffsetState: " << IMU.getStateOffset().getString() << std::endl;


    }
}