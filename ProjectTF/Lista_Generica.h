#pragma once
#include "Header.h"

template <typename T>
class Lista
{
private:
    struct Nodo;
    typedef function<int(T, T)> Comp;
    Nodo* ini;
    size_t lon;
    Comp comparar;

public:
    Lista() : ini(nullptr), lon(0), comparar([](T a, T b) {return a - b; }) {  }
    Lista(Comp comparar) : ini(nullptr), lon(0), comparar(comparar) {  }
    ~Lista();

    size_t longitud();
    bool esVacia();
    void push_Back_List(T dato);
    T obtener_Pos(size_t pos);
};

template <typename T>
struct Lista<T>::Nodo {
    T dato;
    Nodo* next;
    Nodo(T dato = 0, Nodo* next = nullptr) : dato(dato), next(next) {}
};

template <typename T>
Lista<T>::~Lista() {
    Nodo* aux = ini;
    while (aux != nullptr) {
        aux = ini;
        ini = ini->next;
        delete aux;
    }
}
template <typename T>
size_t Lista<T>::longitud() {
    return lon;
}

template <typename T>
bool Lista<T>::esVacia() {
    return lon == 0;
}

template <typename T>
void Lista<T>::push_Back_List(T dato) {
    Nodo* nuevo = new Nodo(dato, ini);
    if (nuevo != nullptr) {
        ini = nuevo;
        lon++;
    }
}

template <typename T>
T Lista<T>::obtener_Pos(size_t pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (size_t i = 0; i < pos; i++) {
            aux = aux->next;
        }
        return aux->dato;
    }
    else {
        return 0;
    }
}