// Domain.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "Controller_Input.h"
#include "Controller_P.h"
#include "Controller_I.h"
#include "Controller_D.h"
#include "Controller_PT.h"
#include "Controller_PID.h"
#include "ControllerSystem.h"

#include "Ringbuffer.h"
#include "Vector3D.h"


int main()
{
    std::cout << "Hello World!\n";

    Unit U0("m/s²");
    Unit U1("m/s");
    Unit U2("m");

    ControllerSystem CS1(U0);

    CS1.addControllerI(U1, 1.0);
    CS1.addControllerI(U2, 1.0);


    double a = 1.0;
    double tmax = 1.0;

    CS1.setSetpointValue(Value(U0, a));

    for (double t = 0.0; t <= tmax; t += 0.001)
    {
        bool Result = CS1.setFeedbackValue(Value(U0, 0.0, t));


        Value Out = CS1.getOutputValue();


        if (false)
        {
            double Calc = 0.5 * a * t * t;
            double Diff = Out.getValue() - Calc;

            std::cout << "t = " << t << std::endl;
            std::cout << "CS1.Out = " << Out.getValue() << std::endl;
            std::cout << "calc = " << Calc << std::endl;
            std::cout << "CS1.Diff = " << Diff << " (" << 100 * Diff / Calc << "%)" << std::endl;
        }

    }


    Value Out = CS1.getOutputValue();
    double Calc = 0.5 * a * tmax * tmax;
    double Diff = Out.getValue() - Calc;

    std::cout << "t = " << tmax << std::endl;
    std::cout << "CS1.Out = " << Out.getValue() << std::endl;
    std::cout << "calc = " << Calc << std::endl;
    std::cout << "CS1.Diff = " << Diff << " (" << 100 * Diff / Calc << "%)" << std::endl;


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
