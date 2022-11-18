#pragma once
#include "Header.h"

template<class T>
class Cuenta_Operaciones_Pila {

	struct Nodo;
	Nodo* pila;
	int longitud;

public:
	Cuenta_Operaciones_Pila() :pila(nullptr), longitud(NULL) {  }

	struct Nodo {
		T dato;
		Nodo* next;
	};

	void push_Pila(T dato) {
		Nodo* nodo = new Nodo();
		nodo->dato = dato;
		nodo->next = pila;
		pila = nodo;
		longitud++;
	}

	T obtener_Position(int pos) {
		Nodo* aux = pila;
		for (int i = 0; i < pos; i++) {
			aux = aux->next;
		}
		return aux->dato;
	}

	void Erase_Position(int pos) {
		Nodo* aux = pila;
		if (pos == 0) pila = pila->next;
		for (int i = 0; i < pos; i++) {
			aux = aux->next;
		}
		delete aux; longitud--;
	}

	size_t Get_Longitud() { return longitud; }

	~Cuenta_Operaciones_Pila() {  }
};