#include <ros/ros.h>

#include <keyboard/KeyReader.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>
#include <termios.h>



int FileDescriptor = 0;
struct termios original, adapted;






KeyReader::KeyReader()
	: Loop_(10)
{
	this->PubKey_ = nh_.advertise<std_msgs::Char>("KeyReader", 50);
	
	this->initReader();
}

KeyReader::~KeyReader()
{
	this->close();
}


void KeyReader::sendKey(char Key)
{
	std_msgs::Char msg;
	std::string Sending = "Send Key: ";
	
	msg.data = Key;
	Sending.push_back(Key);
	
	switch(Key)
	{
	case 'q':
	case Key_ESC:
		this->close();
		break;
		
	case 0:
		break;
		
	default:
		this->PubKey_.publish(msg);
		
		puts(Sending.c_str());
		
		ros::spinOnce();
		break;
	}
	
	return;
}



void KeyReader::readingLoop()
{
	char ReadBuffer;
	
	
	while(ros::ok())
	{
		ssize_t ReadSize = read(FileDescriptor, &ReadBuffer, 1);	// get the next event from the keyboard  
		
		if(ReadSize == 0)
		{
			puts("Nothing to read.");
		}
		if(ReadSize > 0)
		{
			this->sendKey(ReadBuffer);
		}
		if(ReadSize < 0)
		{
			puts("An Error occurs while reading File.");	
			
			perror("read():");
			exit(-1);
		}
		
		Loop_.sleep();
	}
	
	return;
}



int KeyReader::initReader()
{
	int ReturnValue = 0;
	
	
	// get the console in raw mode                                                              
	if (tcgetattr(FileDescriptor, &original) == 0)
	{
		memcpy(&adapted, &original, sizeof(struct termios));
		adapted.c_lflag &=~ (ICANON | ECHO);
		
		// Setting a new line, then end of file                     
		adapted.c_cc[VEOL] = 1;
		adapted.c_cc[VEOF] = 2;
		
		// Setting Attributes
		if (tcsetattr(FileDescriptor, TCSANOW, &adapted) == 0)
		{
			puts("Reading Keys from keyboard");
			puts("---------------------------");
		}
		else
		{
			puts("An Error occured while setting TERMIOS-Attributes.");
			
			perror("tcsetattr() error");
			
			ReturnValue = -2;
		}
	}
	else
	{
		puts("An Error occured while getting TERMIOS-Attributes.");
		
		perror("tcgetattr() error");
		
		ReturnValue = -1;
	}

	return ReturnValue;
}


void KeyReader::close()
{
	puts("Closeing Reader...");

	tcsetattr(FileDescriptor, TCSANOW, &original);
	ros::shutdown();
	exit(0);
}


