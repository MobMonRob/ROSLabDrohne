// threading.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "mavros_msgs/ManualControl.h"

#include "threading/AutoPublisher.h"
#include "threading/AutoClient.h"

#define DEBUG

int main()
{
    std::cout << "Hello World!\n";

    AutoPublisher<mavros_msgs::ManualControl> APub("", 10, 10, true);

    for (int i = 0; i < 5000000; i++)
    {

    }

    APub.stop();

}

