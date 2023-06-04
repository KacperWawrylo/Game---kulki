#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    cout << "Jako reprezentacje kolorow, wybierasz liczby czy litery? (l-litery, c-cyfry)" << endl;
    char c;
    cin >> c;
    if (c != 'l' && c != 'c') {
        cout << "Bledne dane. Wybierz l lub c." << endl;
        return 0;
    }

    if (c == 'l') {
        cout << "Wybrales litery." << endl;
        Game game;
        game.graj();
    }
    else {
        cout << "Wybrales cyfry." << endl;
        Game game;
        game.grajNumery();
    }

    return 0;
}