#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Game.h"

using namespace std;

Game::Game():wynik(0) {
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
    plansza.wypelnijLosowo();
    while (true) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Aktualny wynik: " << wynik << endl;
        plansza.wyswietl();
        int startRow, startCol, endRow, endCol;
        cout << "Podaj kulke do przesuniecia (row col): ";
        while (!(cin >> startRow >> startCol)) {
            cin.clear();  // Czyœci b³¹d w strumieniu wejœciowym
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruje pozosta³¹ liniê
            cout << "Niepoprawne dane. Podaj ponownie: ";
        }
        startRow--;
        startCol--;
        cout << "W ktore miejsce (row col): ";
        while (!(cin >> endRow >> endCol)) {
            cin.clear();  // Czyœci b³¹d w strumieniu wejœciowym
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruje pozosta³¹ liniê
            cout << "Niepoprawne dane. Podaj ponownie: ";
        }
        endRow--;
        endCol--;
        system("cls");
        if (startRow >= 0 && startRow < plansza.getRozmiar() && startCol >= 0 && startCol < plansza.getRozmiar()) {
            if (plansza.getPole(startRow, startCol)->getCzy_wolne() == false) {
                if (plansza.czyMozliweRuchy(startRow, startCol, endRow, endCol)) {
                    plansza.przestawKulke(startRow, startCol, endRow, endCol);
                    if (plansza.czyPiecKulek()) {
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

void Game::grajNumery() {
    plansza1.wypelnijLosowo();
    while (true) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Aktualny wynik: " << wynik << endl;
        plansza1.wyswietl();
        int startRow, startCol, endRow, endCol;
        cout << "Podaj kulke do przesuniecia (row col): ";
        while (!(cin >> startRow >> startCol)) {
            cin.clear();  // Czyœci b³¹d w strumieniu wejœciowym
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruje pozosta³¹ liniê
            cout << "Niepoprawne dane. Podaj ponownie: ";
        }
        startRow--;
        startCol--;
        cout << "W ktore miejsce (row col): ";
        while (!(cin >> endRow >> endCol)) {
            cin.clear();  // Czyœci b³¹d w strumieniu wejœciowym
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruje pozosta³¹ liniê
            cout << "Niepoprawne dane. Podaj ponownie: ";
        }
        endRow--;
        endCol--;
        system("cls");
        if (startRow >= 0 && startRow < plansza1.getRozmiar() && startCol >= 0 && startCol < plansza1.getRozmiar()) {
            if (plansza1.getPole(startRow, startCol)->getCzy_wolne() == false) {
                if (plansza1.czyMozliweRuchy(startRow, startCol, endRow, endCol)) {
                    plansza1.przestawKulke(startRow, startCol, endRow, endCol);
                    if (plansza1.czyPiecKulek()) {
                        cout << "Zbito piec Kulek!" << endl;
                        wynik += 5;
                        continue;
                    }
                    if (!plansza1.czyTrzyMiejsca()) {
                        cout << "Koniec gry! Plansza jest pelna." << endl;
                        zapiszDoPliku();
                        break;
                    }
                    plansza1.wypelnijLosowo();
                }
                else {
                    cout << "Niepoprawny ruch. Sprobuj ponownie." << endl;
                }
            }
            else {
                cout << "Niepoprawny ruch. Sprobuj ponownie." << endl;
            }
        }
        else {
            cout << "Niepoprawny ruch. Sprobuj ponownie." << endl;
        }
        if (plansza1.czyPelna()) {
            cout << "Koniec gry! Plansza jest pelna." << endl;
            zapiszDoPliku();
            break;
        }
    }
}