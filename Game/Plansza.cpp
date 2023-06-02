#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plansza.h"
#include <vector>

using namespace std;

struct koordynaty {
    int x;
    int y;
    koordynaty(int x = 0, int y = 0): x(x), y(y){
    }
    bool operator==(const koordynaty& left) const {
        return (x == left.x && y == left.y);
    }
};

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
    return pole[row][col];
}

const int Plansza::getRozmiar() {
    return ROZMIAR_PLANSZY;
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
    
    vector<koordynaty> sprawdzonePola;
    vector<koordynaty> polaDoSprawdzenia;

    koordynaty kierunki[4] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
    vector<koordynaty> wolnePola;
    for (int i = 0; i < 4; ++i) {
        if (row + kierunki[i].x < 0 || row + kierunki[i].x >= ROZMIAR_PLANSZY || col + kierunki[i].y < 0 || col + kierunki[i].y >= ROZMIAR_PLANSZY)
            continue;
        if (pole[row + kierunki[i].x][col + kierunki[i].y]->getCzy_wolne())
            wolnePola.push_back({ row + kierunki[i].x , col + kierunki[i].y });
    }

    //c++ nie oferuje prostej metody dodania dwoch wektorow do siebie, wiec trzeba zrobic to w ten sposób.
    polaDoSprawdzenia.insert(polaDoSprawdzenia.end(), wolnePola.begin(), wolnePola.end());
    wolnePola.clear();

    //dopóki nam pozosta³y pola do sprawdzenia
    while (polaDoSprawdzenia.size() > 0) {
        //sprawdzenie czy to jest pole do którego chcemy dotrzeæ
        if (polaDoSprawdzenia[0].x == new_row && polaDoSprawdzenia[0].y == new_col) {
            return true;
        }
        //w innym wypadku sprawdŸmy pola doko³a obecnie sprawdzonego pola
        for (int i = 0; i < 4; ++i) {
            if (polaDoSprawdzenia[0].x + kierunki[i].x < 0 || polaDoSprawdzenia[0].x + kierunki[i].x >= ROZMIAR_PLANSZY || polaDoSprawdzenia[0].y + kierunki[i].y < 0 || polaDoSprawdzenia[0].y + kierunki[i].y >= ROZMIAR_PLANSZY)
                continue;
            if (pole[polaDoSprawdzenia[0].x + kierunki[i].x][polaDoSprawdzenia[0].y + kierunki[i].y]->getCzy_wolne()) {
                wolnePola.push_back({ polaDoSprawdzenia[0].x + kierunki[i].x , polaDoSprawdzenia[0].y + kierunki[i].y });
            }
        }

        //i dodajmy je do pól do sprawdzenia
        polaDoSprawdzenia.insert(polaDoSprawdzenia.end(), wolnePola.begin(), wolnePola.end());
        wolnePola.clear();

        //dodajmy obecne pole do sprawdzonych pol
        sprawdzonePola.push_back(polaDoSprawdzenia[0]);

        //usunmy z pól do sprawdzenia wszystkie sprawdzone pola.
        for (int i = 0; i < sprawdzonePola.size(); ++i) {
            for (int j = 0; j < polaDoSprawdzenia.size(); ++j) {
                if (sprawdzonePola[i] == polaDoSprawdzenia[j]) {
                    polaDoSprawdzenia.erase(polaDoSprawdzenia.begin() + j);
                    --j;
                }
            }
        }
    }

    return false;
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

void Plansza::przestawKulke(int x1, int y1, int x2, int y2) {
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

