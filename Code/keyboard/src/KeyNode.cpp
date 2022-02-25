#include <keyboard/KeyReader.h>


int main(int argc, char** argv)
{
	ros::init(argc, argv, "KeyReader");
	KeyReader Reader;
	
	Reader.readingLoop();
	
	return 0;
}


