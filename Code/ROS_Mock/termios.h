#ifndef MOCK_TERMOIS_H
#define MOCK_TERMOIS_H

#include <sstream>

#define TCSANOW 1
#define ICANON 1
#define ECHO 3
#define VEOL 0
#define VEOF 0


typedef int ssize_t;

struct termios
{
	int c_lflag;
	int c_cc[2];
};

int tcsetattr(int i, int j, termios* Ptr);

int tcgetattr(int i, termios* Ptr);

ssize_t read(int i, char* ch, int j);

#endif // MOCK_TERMOIS_H
