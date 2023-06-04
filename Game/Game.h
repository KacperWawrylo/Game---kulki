#pragma once
#include"Plansza.h"
#include <string>
#include "PlanszaNumery.h"

class Game {
private:
    std::string nick;
    Plansza plansza;
    PlanszaNumery plansza1;
    int wynik;
public:
    Game();
    void zapiszDoPliku();
    void graj();
    void grajNumery();
};
