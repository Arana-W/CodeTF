#pragma once
#include "Header.h"

class Beneficio {

	float monto;
	string textoBeneficio;

public:
	Beneficio(float _monto);

	void generarMonto(float _monto)
	{
		if (_monto < 700) monto = rand() % 21 + 10;
		else if (_monto >= 700 && _monto < 1000) monto = rand() % 21 + 30;
		else if (_monto >= 1000) monto = rand() % 21 + 70;
	}

	void generarTexto()
	{
		int aux = rand() % 4;
		switch (aux)
		{
		case 0:
			textoBeneficio = "Tiene un descuento de " + to_string(monto) + " soles en compras mayores a " + to_string((rand() % 30 + 10) * 10)
				+ " en tiendas TayLoy.";
			break;
		case 1:
			textoBeneficio = "Tiene un descuento de " + to_string(monto) + " soles en compras mayores a " + to_string((rand() % 30 + 10) * 10)
				+ " en Popeyes.";
			break;
		case 2:
			textoBeneficio = "Tiene un descuento de " + to_string(monto) + " soles en compras mayores a " + to_string((rand() % 30 + 10) * 10)
				+ " en KFC.";
			break;
		case 3:
			textoBeneficio = "Tiene un descuento de " + to_string(monto) + " soles en compras mayores a " + to_string((rand() % 30 + 10) * 10)
				+ " en Burger King.";
			break;
		case 4:
			textoBeneficio = "holaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			break;
		}
	}

	float getMonto() { return monto; }
	string getTexto() { return textoBeneficio; }

	~Beneficio() {  }
};

Beneficio::Beneficio(float _monto) {
	monto = 100;
	textoBeneficio = "hola";
	generarMonto(_monto);
	generarTexto();
}
