#pragma once
#ifndef KULKA_H
#define KULKA_H

class Kulka {
private:
	char kolor;
	bool czy_wolne;
public:
	Kulka();
	Kulka(char kolor);
	char getKolor() const;
	void setKolor(char kolor);
	bool getCzy_wolne();
	void setCzy_wolne(bool t);
};

#endif

