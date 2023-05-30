#include "Kulka.h"
#include <cstddef>

Kulka::Kulka() {
	this->kolor = {NULL};
	this->czy_wolne = true;
}

Kulka::Kulka(char kolor) {
	this->kolor = kolor;
	this->czy_wolne = false;
}

char Kulka::getKolor() const {
	return kolor;
}

void Kulka::setKolor(char kolor) {
	kolor = kolor;
}


