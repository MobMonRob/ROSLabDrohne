

#include <iostream>

#include "PosControl/ControllerSystem.h"

#include "PosControl/Ringbuffer.h"
#include "PosControl/Vector3D.h"

#include "PosControl/ActionAdapter.h"


int main()
{
    std::cout << "Hello World!\n";

    
    ControllerSystem CS1(Unit_Acceleration);

    
    CS1.addController(Unit_Velocity, 1.0, ControllerType::I);
    CS1.addController(Unit_Length, 1.0, ControllerType::I);

    
    double a = 1.0;
    double tmax = 0.1;
    

    
    CS1.setSetpoint(TimedValue(Unit_Acceleration, a));

    for (double t = 0.0; t <= tmax; t += 0.001)
    {
        bool Result = CS1.setFeedback(TimedValue(Unit_Acceleration, 0.0, t));


        TimedValue Out = CS1.getOutput();


        if (true)
        {
            double Calc = 0.5 * a * t * t;
            double Diff = Out.getValue() - Calc;

            std::cout << "t = " << t << std::endl;
            std::cout << "CS1.Out = " << Out.getValue() << std::endl;
            std::cout << "calc = " << Calc << std::endl;
            std::cout << "CS1.Diff = " << Diff << " (" << 100 * Diff / Calc << "%)" << std::endl;
        }

    }
    
    TimedValue Out = CS1.getOutput();


    double Calc = 0.5 * a * tmax * tmax;
    double Diff = Out.getValue() - Calc;

    std::cout << "t = " << tmax << std::endl;
    std::cout << "CS1.Out = " << Out.getValue() << std::endl;
    std::cout << "calc = " << Calc << std::endl;
    std::cout << "CS1.Diff = " << Diff << " (" << 100 * Diff / Calc << "%)" << std::endl;
    



    std::cout << std::endl << std::endl;
    std::cout << "ControllerSystem Info:" << std::endl;








    std::cout << "Destructor..." << std::endl;
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
