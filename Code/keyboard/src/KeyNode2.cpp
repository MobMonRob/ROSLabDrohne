#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>
#include <termios.h>


#define Key_Enter	0x00
#define Key_ESC	0x1B
#define Key_Q		0x71



#define Key_ArrowUp	0x41
#define Key_ArrowDown	0x44
#define Key_ArrowLeft	0x42
#define Key_ArrowRight	0x43
#define Key_W		0x77
#define Key_S		0x73
#define Key_A		0x61
#define Key_D		0x64

#define Key_Y		0x79
#define Key_N		0x6E
#define Key_C		0x63


class KeyReader
{
public:
  KeyReader();
  void keyLoop();
  
private:
  ros::NodeHandle nh_;
  ros::Publisher PubKey_;
};








int kfd = 0;
struct termios cooked, raw;


void quit()
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}



KeyReader::KeyReader()
{
  
  
  this->PubKey_ = nh_.advertise<std_msgs::String>("KeyReader", 50);
}


void KeyReader::keyLoop()
{
  char c;
  bool dirty=false;


  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading Keys from keyboard");
  puts("---------------------------");


  for(;;)
  {
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
    
    switch(c)
    {
      case 'q':
      case Key_ESC:
        quit();
        break;
        
      default:
        if(dirty ==true)
        {
          std_msgs::String msg;
          std::stringstream ss;
          
          ss << c;
          msg.data = ss.str();
          
          
          
          
          PubKey_.publish(msg);    
          dirty=false;
        }
        
        break;
    }
  }

  return;
}














int main(int argc, char** argv)
{
  ros::init(argc, argv, "KeyReader");
  KeyReader Reader;
  
  Reader.keyLoop();

  return 0;
}


