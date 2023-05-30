#pragma once
#ifndef KULKA_H
#define KULKA_H

class Kulka {
public:
	char kolor;
	bool czy_wolne;
public:
	Kulka();
	Kulka(char kolor);
	char getKolor() const;
	void setKolor(char kolor);
};

#endif

