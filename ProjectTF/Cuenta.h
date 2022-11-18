#pragma once
#include "Header.h"

class Cuenta
{
public:
	Cuenta(char tipo) : tipo(tipo), cant_Dinero(0.0) { nro_Cuenta = 100000000 + rand() % (INT_MAX - 1000000000 + 1); }

	void retirar_Dinero(float monto, bool& op_realizada)
	{
		if (monto > cant_Dinero)
		{
			cout << "\n\20\tERROR. El dinero ingresado es mayor al que hay en la cuenta..."; op_realizada = false;
			_getch(); return;
		}
		else { cant_Dinero -= monto; cout << "\n\n\20\tRetirando..."; Sleep(500); op_realizada = true; }
	}

	void depositar_Dinero(float monto, bool& op_realizada)
	{
		if (monto < 0)
		{
			cout << "\n\20\tERROR. No se puede ingresar monto negativo..."; op_realizada = false;
			_getch(); return;
		}
		else { cant_Dinero += monto; cout << "\n\n\20\tDepositando..."; Sleep(500); op_realizada = true; }
	}

	void recibir_Dinero(float monto, bool& op_realizada) {
		cant_Dinero += monto; Sleep(500); op_realizada = true;
	}

	void set_Cant_Dinero(float cant_Dinero) { this->cant_Dinero = cant_Dinero; }
	void set_Nro_Cuenta(int nro_Cuenta) { this->nro_Cuenta = nro_Cuenta; }
	void set_Tipo(char tipo) { this->tipo = tipo; }

	char get_Tipo() { return tipo; }
	int get_Nro_Cuenta() { return nro_Cuenta; }
	float get_Cant_Dinero() { return cant_Dinero; }

	~Cuenta() {  }

private:
	char tipo;
	int nro_Cuenta;
	float cant_Dinero;
};