#pragma once
#include "Header.h"

template<class T>
class OperacionesCola {

	struct Nodo;
	Nodo* inicio;
	Nodo* fin;
	int longitud;

public:
	OperacionesCola() :inicio(nullptr), fin(nullptr), longitud(NULL) {  }

	struct Nodo {
		T dato;
		Nodo* next;
	};

	void Add_OperacionesCola(T dato) {
		Nodo* nodo = new Nodo();
		nodo->dato = dato;
		nodo->next = nullptr;
		(OperacionesCola_Vacia(inicio)) ? inicio = nodo : fin->next = nodo;
		fin = nodo;
		longitud++;
	}

	T ToShow_OperacionesCola() {
		Nodo* aux = inicio;
		T elemento = aux->dato;
		inicio = aux->next;
		delete aux;
		return elemento;
	}

	bool OperacionesCola_Vacia(Nodo* inicio) { return (inicio == nullptr) ? true : false; }
	int Get_Longitud() { return longitud; }

	~OperacionesCola() {  }
};