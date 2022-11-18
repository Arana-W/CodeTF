#pragma once
#include "Header.h"

template <class T>
class Nodo {
public:
	Nodo<T>* izq;
	T elemento;
	Nodo<T>* der;
	Nodo(T e) {
		elemento = e;
		izq = nullptr;
		der = nullptr;
	}
};

template <class T>
class ListaDoblementeEnlazada {
	Nodo<T>* inicio;
	Nodo<T>* fin;
	size_t cantidad;

public:
	ListaDoblementeEnlazada() {
		inicio = nullptr;
		fin = nullptr;
		cantidad = 0;
	}

	~ListaDoblementeEnlazada() {
		Nodo<T>* temp;
		while (inicio != nullptr) {
			temp = inicio;
			inicio = inicio->der;
			delete temp;
			temp = nullptr;
		}
		delete inicio;
		inicio = nullptr;
	}

	void agregarAlFinal(T valor) {
		Nodo<T>* nuevo = new Nodo<T>(valor);
		if (inicio == nullptr) {
			inicio = nuevo;
			fin = nuevo;
			nuevo->izq = nullptr;
			nuevo->der = nullptr;
		}
		else {
			nuevo->izq = fin;
			fin->der = nuevo;
			fin = fin->der;
			fin = nuevo;
			fin->der = nullptr;
		}
		cantidad++;
	}

	void mostrarLista(function<void(T)>imprimir) {
		Nodo<T>* aux = inicio;
		while (aux != nullptr) {
			imprimir(aux->elemento);
			aux = aux->der;
		}
	}

	void ordenarListaBurbuja(function<int(T)>retornarValor) {
		Nodo<T>* aux = inicio;
		Nodo<T>* aux2 = nullptr;
		T aux3;
		while (aux->der != nullptr)
		{
			aux2 = aux->der;
			while (aux2 != nullptr)
			{
				if (retornarValor(aux->elemento) > retornarValor(aux2->elemento)) {
					aux3 = aux2->elemento;
					aux2->elemento = aux->elemento;
					aux->elemento = aux3;
				}
				aux2 = aux2->der;
			}
			aux = aux->der;
		}
	}

	size_t get_cantidad() { return cantidad; }

	T obtener_Pos(size_t pos) {
		if (pos >= 0 && pos < cantidad) {
			Nodo<T>* aux = ini;
			for (size_t i = 0; i < pos; i++) {
				aux = aux->der;
			}
			return aux->elemento;
		}
		else {
			return 0;
		}
	}
};