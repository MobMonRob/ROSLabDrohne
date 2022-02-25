#include "termios.h"


int tcsetattr(int i, int j, termios* Ptr)
{
	return -1;
}

int tcgetattr(int i, termios* Ptr)
{
	return -1;
}

ssize_t read(int i, char* ch, int j)
{
	*ch = 'O';
	return -1;
}

