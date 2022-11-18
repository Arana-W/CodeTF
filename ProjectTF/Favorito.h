#pragma once
#include "Usuario.h"
#include "Cuenta.h"
#include "Cuenta_Op_Pila.h"

class favorito {

	string nombre;
	int dni;

public:

	favorito(string nombre = " ", int dni = 0) :nombre(nombre), dni(dni) {  }

	string get_Nombre() { return nombre; }
	int get_Dni() { return dni; }

	string toString() {
		cout << endl << endl;
		return "Nombre: " + nombre + " -- Dni: " + to_string(dni);
	}

	~favorito() {  }
};