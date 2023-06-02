#pragma once
#ifndef GAME_H
#define GAME_H

#include"Plansza.h"
#include <string>

class Game {
private:
    std::string nick;
    Plansza plansza;
    int wynik;
public:
    Game();
    void zapiszDoPliku();
    void graj();
};

#endif