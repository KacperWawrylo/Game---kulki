#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ctime>
#include "Plansza.h"
#include <queue>

using namespace std;

Plansza::Plansza() {
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            pole[i][j] = new Kulka;
        }
    }
}

Plansza::~Plansza() {
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            delete pole[i][j];
        }
    }
}

Kulka* Plansza::getPole(int row, int col) {
    if (row >= 0 && row < ROZMIAR_PLANSZY && col >= 0 && col < ROZMIAR_PLANSZY) {
        return pole[row][col];
    }
    else {
        return nullptr;
    }
}

void Plansza::wypelnijLosowo() {
    srand(time(NULL));

    for (int z = 0; z < 3; z++) {
        int i, j;
        char kolor = 'A' + rand() % 6;
        do {
            i = rand() % ROZMIAR_PLANSZY;
            j = rand() % ROZMIAR_PLANSZY;
        } while (pole[i][j]->getCzy_wolne() == false);

        pole[i][j]->setCzy_wolne(false);
        pole[i][j]->setKolor(kolor);
    }
}

void Plansza::wyswietl() {
    cout << "\n   ";
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;
    cout << "  ";
    for (int i = 0; i < ROZMIAR_PLANSZY * 2 + 1; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            if (pole[i][j]->getCzy_wolne()) {
                cout << " ";
            }
            else {
                cout << pole[i][j]->getKolor();
            }
            cout << "|";
        }
        cout << endl;
        cout << "  ";
        int n = ROZMIAR_PLANSZY;
        for (int i = 0; i < n * 2 + 1; i++) {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl << endl;
}

bool Plansza::czyMozliweRuchy(int row, int col, int new_row, int new_col) {
    // Sprawdzenie, czy istnieje mo¿liwoœæ wykonania ruchu
    // (czy istnieje linia piêciu lub wiêcej kulek do usuniêcia)
    // Zwraca true, jeœli mo¿liwe s¹ ruchy, w przeciwnym razie false.
    // Implementacja tego fragmentu nale¿y do Ciebie.
    
    if (new_row < 0 || new_row >= ROZMIAR_PLANSZY || new_col < 0 || new_col >= ROZMIAR_PLANSZY) {
        return false;
    }
    if (!pole[new_row][new_col]->getCzy_wolne()) {
        return false;
    }
   
    return true;
}

bool Plansza::czyPiecKulek() {
    //sprawdzenie w poziomie
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) { 
        for (int j = 0; j <= ROZMIAR_PLANSZY - 5; j++) {
            char kolor = pole[i][j]->getKolor();
            if (kolor != NULL) {
                bool wygrana = true;
                for (int k = 1; k < 5; k++) {
                    if (pole[i][j + k]->getKolor() != kolor) {
                        wygrana = false;
                        break;
                    }
                }
                if (wygrana) {
                    // Usuñ kule z planszy
                    for (int k = 0; k < 5; k++) {
                        pole[i][j + k] = new Kulka;
                    }
                    return true;
                }
            }
        }
    }
    //sprawdzenie w pionie
    for (int i = 0; i <= ROZMIAR_PLANSZY - 5; i++) { 
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            char kolor = pole[i][j]->getKolor();
            if (kolor != NULL) {
                bool wygrana = true;
                for (int k = 1; k < 5; k++) {
                    if (pole[i + k][j]->getKolor() != kolor) {
                        wygrana = false;
                        break;
                    }
                }
                if (wygrana) {
                    // Usuñ kule z planszy
                    for (int k = 0; k < 5; k++) {
                        pole[i+k][j] = new Kulka;
                    }
                    return true;
                }
            }
        }
    }

    // sprawdzenie ukosne kombinacje (w prawo-dol)
    for (int i = 0; i <= ROZMIAR_PLANSZY - 5; i++) {
        for (int j = 0; j <= ROZMIAR_PLANSZY - 5; j++) {
            char kolor = pole[i][j]->getKolor();
            if (kolor != NULL) {
                bool wygrana = true;
                for (int k = 1; k < 5; k++) {
                    if (pole[i + k][j + k]->getKolor() != kolor) {
                        wygrana = false;
                        break;
                    }
                }
                if (wygrana) {
                    for (int k = 0; k < 5; k++) {
                        pole[i + k][j + k] = new Kulka;
                    }
                    return true;
                }
            }
        }
    }

    // SprawdŸ ukosne kombinacje (w prawo-gora)
    for (int i = 4; i < ROZMIAR_PLANSZY; i++) {
        for (int j = 0; j <= ROZMIAR_PLANSZY - 5; j++) {
            char kolor = pole[i][j]->getKolor();
            if (kolor != NULL) {
                bool wygrana = true;
                for (int k = 1; k < 5; k++) {
                    if (pole[i - k][j + k]->getKolor() != kolor) {
                        wygrana = false;
                        break;
                    }
                }
                if (wygrana) {
                    for (int k = 0; k < 5; k++) {
                        pole[i - k][j + k] = new Kulka;
                    }
                    return true;
                }
            }
        }
    }

    return false;
}

bool Plansza::czyPelna() {
    // Sprawdzenie, czy plansza jest ju¿ pe³na (brak pustych pól)
    // Zwraca true, jeœli plansza jest pe³na, w przeciwnym razie false.
    // Implementacja tego fragmentu nale¿y do Ciebie.
    int n = 0;
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            if (pole[i][j]->getCzy_wolne()) {
                n++;
            }
        }
    }
    if (n == 0) {
        return true;
    }
    return false;
}

bool Plansza::czyLinia(int x1, int y1, int x2, int y2) {
    // Sprawdzenie, czy istnieje linia kulek o tym samym kolorze
    // pomiêdzy punktami (x1, y1) i (x2, y2)
    // Zwraca true, jeœli linia istnieje, w przeciwnym razie false.
    // Implementacja tego fragmentu nale¿y do Ciebie.
    return false;
}

void Plansza::usunLinie(int x1, int y1, int x2, int y2) {
    // Usuniêcie linii kulek o tym samym kolorze
    // pomiêdzy punktami (x1, y1) i (x2, y2)
    // Implementacja tego fragmentu nale¿y do Ciebie.
}

void Plansza::przestawKulke(int x1, int y1, int x2, int y2) {
    // Przestawienie kulki z pozycji (x1, y1) na pozycjê (x2, y2)
    // Implementacja tego fragmentu nale¿y do Ciebie.
    pole[x2][y2] = pole[x1][y1];
    pole[x1][y1] = new Kulka;
}

bool Plansza::czyTrzyMiejsca() {
    int n = 0;
    for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
        for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
            if (pole[i][j]->getCzy_wolne()) {
                n++;
            }
        }
    }
    if (n >= 3) {
        return true;
    }
    return false;
}

