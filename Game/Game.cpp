#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Game.h"

using namespace std;

Game::Game():wynik(0) {
	plansza.wypelnijLosowo();
    cout << "Podaj nick: ";
    cin >> nick;
}

void Game::zapiszDoPliku() {
    ofstream plik("wyniki.txt", ios::app);
    if (plik.is_open()) {
        plik << "Nick gracza: " << nick << ", Wynik: " << wynik << endl;
        plik.close(); 
    }
    else {
        cout << "B³¹d otwarcia pliku wyniki.txt" << endl;
    }
    cout << "Zapisuje do pliku wyniki.txt" << endl;
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
        system("cls");
        if (plansza.getPole(startRow, startCol)->getCzy_wolne() == false) {
            if (plansza.czyMozliweRuchy(startRow, startCol, endRow, endCol)) {
                // Perform the move and update the score
                // Implement your move logic here
                // ...
                plansza.przestawKulke(startRow, startCol, endRow, endCol);
                if(plansza.czyPiecKulek()){
                    cout << "Zbito piec Kulek!" << endl;
                    wynik += 5;
                    continue;
                }
                if (!plansza.czyTrzyMiejsca()) {
                    cout << "Koniec gry! Plansza jest pelna." << endl;
                    zapiszDoPliku();
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
            zapiszDoPliku();
            break;
        }
    }
}
