#pragma once
#ifndef PLANSZA_H
#define PLANSZA_H

#include "Kulka.h"

class Plansza {
private:
	static const int ROZMIAR_PLANSZY = 9;
	Kulka* pole[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY];
public:
	Kulka* getPole(int row, int col);
	const int getRozmiar();
	Plansza();
	~Plansza();
	void wypelnijLosowo();
	void wyswietl();
	bool czyMozliweRuchy(int row, int col, int new_row, int new_col);
	bool czyPiecKulek();
	bool czyPelna();
	void przestawKulke(int x1, int y1, int x2, int y2);
	bool czyTrzyMiejsca();
};

#endif


