#ifndef KEYREADER_H
#define KEYREADER_H

#include <ros/ros.h>




#define Key_Enter		0x00
#define Key_ESC			0x1B
#define Key_Q			0x71



#define Key_ArrowUp		0x41
#define Key_ArrowDown	0x44
#define Key_ArrowLeft	0x42
#define Key_ArrowRight	0x43
#define Key_W			0x77
#define Key_S			0x73
#define Key_A			0x61
#define Key_D			0x64

#define Key_Y			0x79
#define Key_N			0x6E
#define Key_C			0x63


class KeyReader
{
public:
	KeyReader();
	~KeyReader();
	
	void sendKey(char Key);
	void readingLoop();
	
private:
	int initReader();
	void close();

	ros::NodeHandle nh_;
	ros::Publisher PubKey_;
	ros::Rate Loop_;
};

#endif // KEYREADER_H

