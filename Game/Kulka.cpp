#include "Kulka.h"
#include <cstddef>

Kulka::Kulka():czy_wolne(true) {
	this->kolor = {NULL};
}

Kulka::Kulka(char kolor):czy_wolne(false) {
	this->kolor = kolor;
}

char Kulka::getKolor() const {
	return kolor;
}

void Kulka::setKolor(char _kolor) {
	this->kolor = _kolor;
}

bool Kulka::getCzy_wolne() {
	return czy_wolne;
}

void Kulka::setCzy_wolne(bool t) {
	this->czy_wolne = t;
}
