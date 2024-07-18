// SchachDartenhaltungArray.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <array>

#include "consolenfarbe.h"

std::array<std::array<char, 8>, 8> spielstand; // 2 dim 
int zugNr = 1;

void figurBewegen(std::string bewegung) // a2a4
{
    int vonZeile = '8' - bewegung[1];   //die 2 in a2a4    oder bewegung.at(1)
    int vonSpalte = bewegung[0] - 'a';   // das vordere a in a2a4 
    int hinZeile = '8' - bewegung[3];
    int hinSpalte = bewegung[2] - 'a';

    spielstand[hinZeile][hinSpalte] = spielstand[vonZeile][vonSpalte]; // achtung kopie
    spielstand[vonZeile][vonSpalte] = ' ';


}

// zeigt den Spielstand auf dem Bildschirm
void darstellen()
{
    int startx = 2;
    int starty = 2;
    dkremer::concolinit();
    setCursorPosition(startx, starty);
    int zeileNr = 8;
    std::cout << " ABCDEFGH \n";
    for (auto zeile : spielstand) // foreach 
    {
        setCursorPosition(startx, ++starty);
        dkremer::setbackcolor(dkremer::black);
        std::cout << zeileNr;
        int spalteNr = 0;
        for (auto feld : zeile)
        {
            dkremer::setcolor(dkremer::black, (zeileNr + spalteNr++) % 2 ? dkremer::grey : dkremer::white);
            std::cout << feld; // jedes Zeichen auf jedem Feld einzel
        }
        dkremer::setcolor(dkremer::green,dkremer::black);
        std::cout << zeileNr--;
        std::cout << "\n";
    }
    setCursorPosition(startx, ++starty);
    dkremer::setcolor(dkremer::green, dkremer::black);
    std::cout << " ABCDEFGH \n";
}

// füllt die Elemente des Array mit Zeichen ( Figuren oder leere Felder )
void grundstellung_erzeugen()
{
    //char hell = 219;
    //char dunkel = 255;
    std::string offz = "TSLDKLST";
    for (int zeile = 0; zeile < 8; zeile++)
    {
        for (int spalte = 0; spalte < 8; spalte++)
        {
            switch (zeile)
            {
            case 1:                          // 66 +   0        * 32  == 66  B
                // 66 +   1        * 32  == 98  b
            case 6: spielstand[zeile][spalte] = 'B' + !(zeile % 2) * 32;
                break;
            case 0:
            case 7: spielstand[zeile][spalte] = offz[spalte] + (zeile % 2) * 32;
                break;
            default:
                spielstand[zeile][spalte] = ' '; // (zeile + spalte) % 2 ? hell : dunkel;
            }
        }
    }



}

char bewegteFigur(std::string bewegung)
{
    return spielstand['8' - bewegung[1]][bewegung[0] - 'a']; // gibt die Figur zurück
    //  die bewegt werden soll
 }

char zielFeld(std::string bewegung)
{
    return spielstand['8' - bewegung[3]][bewegung[2] - 'a']; // gibt den Inhalt 
    // des Zielfeldes zurück
}

bool leeresFeld(std::string bewegung)
{
    return spielstand['8' - bewegung[3]][bewegung[2] - 'a'] == ' '; // gibt an ob Feld leer
}

bool zugOK(std::string bewegung)
{
    return (
        // passende Länge der Eingabe
        bewegung.size() == 4 &&
        // erlaubte Koordinaten
        bewegung[1] <= '8' && bewegung[1] >= '1' &&
        bewegung[3] <= '8' && bewegung[3] >= '1' &&
        bewegung[0] <= 'h' && bewegung[0] >= 'a' &&
        bewegung[2] <= 'h' && bewegung[2] >= 'a' &&
        // nur eigene Figuren und kein Leerfeld
        ( zugNr%2==1 ? islower(bewegteFigur(bewegung))
                     : isupper(bewegteFigur(bewegung))) &&
        // keine eigene Figur schlagen 
        // bewegteFigur und Figur auf Zielfeld dürfen nicht von gleicher Farbe sein
        // oder da ist garkeine Figur 
        islower(bewegteFigur(bewegung)) != islower(zielFeld(bewegung)) || leeresFeld(bewegung)
        );
}

int main()
{
    setlocale(LC_ALL, "de_DE.UTF-8");
    bool nochWeiter = true;
    bool zugNichtKorrekt = true;
    std::string bewegung;
    grundstellung_erzeugen();

    
    do
    {
        do
        {
            system("CLS");
            std::cout << "Es zieht der Spieler " << (zugNr % 2 ? "weiß" : "schwarz") << "\n";
            darstellen();
            zugNichtKorrekt = true;
            setCursorPosition(5, 15);
            std::cout << "Bitte geben Sie Ihren Zug ein :";
            std::cin >> bewegung; // z.B: a2a4
            if (zugOK(bewegung))
            {
                figurBewegen(bewegung);
                darstellen();
                zugNichtKorrekt = false;
                zugNr++;
            }
            else
            {
                std::cout << "Diese Bewegung ist nicht erlaubt\n";
                system("Pause");
            }

        } while (zugNichtKorrekt);
        
       

    } while (nochWeiter);
}

