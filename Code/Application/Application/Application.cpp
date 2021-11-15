// Application.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

<<<<<<< HEAD
#include "Controller_Input.h"
#include "Controller_I.h"
//#include "AccelToPos.h"
=======
#include <Unit.h>
#include <Value.h>
#include <Controller_Input.h>
#include <Controller_I.h>
#include <ControllerSystem.h>
>>>>>>> devel_app



int main()
{
    std::cout << "Hello World!\n";

<<<<<<< HEAD
    Unit U("m/s²");



    //AccelToPos X;
    Controller_Input X(U);
    Controller_I I(U, Unit("m/s"), 1.0);


    for (double t = 0.0; t < 1.0; t += 0.1)
    {
        //X.setInput(Value(U, 1.0, t));



        //std::cout << "t=" << t << ", Value=" << I.getOutputValue().getValue() << std::endl;
    }
=======
    Unit U1("m");
    Value V1(U1);

    std::cout << U1.getUnit() << std::endl;
>>>>>>> devel_app


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
