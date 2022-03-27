
#include <stdlib.h>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>


/*
 * https://ardrone-autonomy.readthedocs.io/en/latest/reading.html
 */


ros::Time TimeStamp;
ros::Time TimeMessage;
int Counter;
ros::Time UpdateMessage;
std::fstream OutputFile;


void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr)
{
	if (TimeStamp == ros::Time())
	{
		TimeStamp = navdataPtr->header.stamp;
	}

	TimeMessage = navdataPtr->header.stamp;

	if (OutputFile.is_open())
	{
		OutputFile << std::to_string((TimeMessage - TimeStamp).toSec()) << ";";

		OutputFile << std::to_string(navdataPtr->state) << ";";

		OutputFile << std::to_string(navdataPtr->ax) << ";";
		OutputFile << std::to_string(navdataPtr->ay) << ";";
		OutputFile << std::to_string(navdataPtr->az) << ";";

		OutputFile << std::to_string(navdataPtr->vx) << ";";
		OutputFile << std::to_string(navdataPtr->vy) << ";";
		OutputFile << std::to_string(navdataPtr->vz) << ";";

		OutputFile << std::to_string(navdataPtr->altd) << ";";

		OutputFile << "\n";

		Counter++;

		UpdateMessage = ros::Time::now();
	}
}






int main(int argc, char** argv)
{
	ROS_INFO("Started New Node: Bagfile Plotter");
	
	std::string FilePath = "/home/Documents/BagOutput.txt";


	OutputFile.open(FilePath.c_str(), std::fstream::out);
	Counter = 0;


	if (OutputFile.is_open())
	{
		OutputFile << "Time [s];State;ax [m/s²];ay [m/s²];az [m/s²];vx [m/s];vy [m/s];vz [m/s];h [m]\n";

		ros::init(argc, argv, "BagPlotter");
		ros::NodeHandle nh_;
		ros::Subscriber SubIMU_;
		ros::Subscriber SubNav_ = nh_.subscribe("ardrone/navdata", 1, callbackNavdata);

		ros::Time Update = ros::Time::now();
		ros::Duration DurationUpdate(1);
		ros::Duration DurationTimeout(10);
		UpdateMessage = ros::Time::now();


		while(ros::ok())
		{
			if (ros::Time::now() - Update >= DurationUpdate)
			{
				ROS_INFO("Wrote %d Entries into File with a Timespan of %d Seconds.", Counter, (TimeMessage - TimeStamp).toSec());

				Update = ros::Time::now();

				if (ros::Time::now() - UpdateMessage >= DurationTimeout)
				{
					break;
				}
			}
			
			ros::spinOnce();
		}
		
		OutputFile.close();

		ROS_INFO("Wrote into >>%s<<", FilePath.c_str());
	}
	else
	{
		ROS_ERROR("File not opened. >>%s<<", FilePath.c_str());
	}

	
	ROS_INFO("Terminated Node: Bagfile Plotter");
	
	return 0;
}

