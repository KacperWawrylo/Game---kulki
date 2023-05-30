#pragma once
#ifndef PLANSZA_H
#define PLANSZA_H

#include "Kulka.h"

class Plansza {
public:
	static const int ROZMIAR_PLANSZY = 9;
	Kulka* pole[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY];

public:
	Plansza();
	~Plansza();
	void wypelnijLosowo();
	void wyswietl();
	bool czyMozliweRuchy(int row, int col, int new_row, int new_col);
	bool czyPelna();
	bool czyLinia(int x1, int y1, int x2, int y2);
	void usunLinie(int x1, int y1, int x2, int y2);
	void przestawKulke(int x1, int y1, int x2, int y2);
	bool czyTrzyMiejsca();
};

#endif


