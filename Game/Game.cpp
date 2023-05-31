#include <iostream>
#include <cstdlib>
#include "Game.h"

using namespace std;

Game::Game():wynik(0) {
	plansza.wypelnijLosowo();
}

void Game::graj() {
    while (true) {
        cout << "Aktualny wynik: " << wynik << endl;
        plansza.wyswietl();

        int startRow, startCol, endRow, endCol;
        cout << "Podaj kulke do przesuniecia (row col): ";
        cin >> startRow >> startCol;
        startRow--;
        startCol--;
        cout << "W ktore miejsce (row col): ";
        cin >> endRow >> endCol;
        endRow--;
        endCol--;
        if (plansza.pole[startRow][startCol]->czy_wolne == false) {
            if (plansza.czyMozliweRuchy(startRow, startCol, endRow, endCol)) {
                // Perform the move and update the score
                // Implement your move logic here
                // ...
                plansza.przestawKulke(startRow, startCol, endRow, endCol);
                if(plansza.czyPiecKulek()){
                    cout << "Zbito piec Kulek !" << endl;
                    wynik += 1;
                    continue;
                }
                if (!plansza.czyTrzyMiejsca()) {
                    cout << "Koniec gry! Plansza jest pelna." << endl;
                    break;
                }
                plansza.wypelnijLosowo();
            }
            else {
                cout << "Niepoprawny ruch. Sprobuj ponownie." << endl;
            }
        }
        else {
            cout << "Niepoprawny ruch. Sprobuj ponownie." << endl;
        }
        
        if (plansza.czyPelna()) {
            cout << "Koniec gry! Plansza jest pelna." << endl;
            break;
        }
    }
}
