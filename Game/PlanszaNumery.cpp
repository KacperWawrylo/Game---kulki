#include "PlanszaNumery.h"
#include <ctime>
#include <stdlib.h>

void PlanszaNumery::wypelnijLosowo(){
    srand(time(NULL));

    for (int z = 0; z < 3; z++) {
        int i, j;
        char kolor = '1' + rand() % 6;
        do {
            i = rand() % getRozmiar();
            j = rand() % getRozmiar();
        } while (getPole(i,j)->getCzy_wolne() == false);

        getPole(i, j)->setCzy_wolne(false);
        getPole(i, j)->setKolor(kolor);
    }
}