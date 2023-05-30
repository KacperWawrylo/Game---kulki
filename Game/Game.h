#pragma once
#ifndef GAME_H
#define GAME_H

#include"Plansza.h"

class Game {
public:
    Plansza plansza;
    int wynik;

public:
    Game();

    void graj();

};

#endif