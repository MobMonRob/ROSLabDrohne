// Domain.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

#include "Controller_Input.h"
#include "Controller_P.h"
#include "Controller_I.h"
#include "Controller_D.h"
#include "Controller_PT.h"

#include "Ringbuffer.h"


int main()
{
    std::cout << "Hello World!\n";

    Unit Unit1("m/s");
    Unit Unit2("m");

    Controller_Input I1(Unit1);
    Controller_PT C1(Unit1, Unit1, 1.0, 1.0, &I1);


    for (double t = 0; t < 5.0; t += 0.05)
    {
        I1.setInput(Value(Unit1, 1.0, t));

        std::cout << t << " >> " << C1.getOutputValue().getValue() << std::endl;
        std::cout << t << " >> " << C1.getOutputValue().getValue() << std::endl;
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
