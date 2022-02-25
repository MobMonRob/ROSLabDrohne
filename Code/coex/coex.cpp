// coex.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#define DEBUG
#include <iostream>

#include "mavros_msgs/ManualControl.h"
#include "coex/JoystickAxis.h"
#include "coex/Joystick.h"



int main()
{
    std::cout << "Hello World!\n";
    JoystickAxis Axis(1000, 2000, 1500);
    Joystick Stick(1027, 2003, 1500,
        1024, 2003, 1500,
        1031, 2003, 1500,
        1024, 2003, 1500);

    mavros_msgs::ManualControl Msg;

    for (double i = -1.0; i <= 1.0; i += 0.1)
    {
        std::cout << i << " => " << Axis.denormalize(i) << std::endl;
    }



}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
