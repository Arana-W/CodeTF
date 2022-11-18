#pragma once
#include "Cuenta.h"
#include "Cuenta_Op_Pila.h"
#include "Favorito.h"
#include "Lista_Doble_Enlazada.h"
#include "Beneficios.h"
#include "HashTable_Beneficios.h"

class Usuario {

protected:
	Cuenta_Operaciones_Pila<Cuenta*>* pila_Cuenta;
	ListaDoblementeEnlazada<favorito>* list_favoritos;
	vector<Beneficio*> beneficiosUsuario;
	HashTableBeneficio<Beneficio*>* datos;
	string nombre;
	int dni;
	int contra;

public:

	Usuario(string nombre, int dni, int contra) :nombre(nombre), dni(dni), contra(contra)
	{
		pila_Cuenta = new Cuenta_Operaciones_Pila<Cuenta*>();
		list_favoritos = new ListaDoblementeEnlazada<favorito>();
		datos = new HashTableBeneficio<Beneficio*>(101);
	}

	void visualizar_Cuentas()
	{
		if (pila_Cuenta->Get_Longitud() == 0)
		{
			Pos; cout << "...NO HAY NINGUNA CUENTA...";
			_getch(); return;
		}
		else {
			Cls;
			cout << "\n\n=======================================[ CUENTAS DISPONIBLES ]=======================================\n" << endl;
			Ordenamiento_Cuentas();
			for (size_t i = 0; i < pila_Cuenta->Get_Longitud(); i++) {
				char cash = pila_Cuenta->obtener_Position(i)->get_Tipo();
				cout << "\n\20\t[" << i << "] //// Cuenta Nro. [" << pila_Cuenta->obtener_Position(i)->get_Nro_Cuenta() << "]  ////  Tipo: " << cash << " -- Monto: ";
				if (cash == 'S') cout << "S/ ";
				else cout << "$/ ";
				cout << pila_Cuenta->obtener_Position(i)->get_Cant_Dinero() << endl;
			}
			cout << "\n-----------------------------------------------------------------------------------------------------" << endl;
		}
	}

	void Ordenamiento_Cuentas() {
		for (size_t i = 0; i < pila_Cuenta->Get_Longitud(); i++) {
			bool ordenado = true;
			for (size_t i = 0; i < pila_Cuenta->Get_Longitud() - (i + 1); i++) {
				if (pila_Cuenta->obtener_Position(i)->get_Cant_Dinero() < pila_Cuenta->obtener_Position(i + 1)->get_Cant_Dinero()) {
					int aux3, aux4;
					aux3 = pila_Cuenta->obtener_Position(i)->get_Nro_Cuenta();
					aux4 = pila_Cuenta->obtener_Position(i + 1)->get_Nro_Cuenta();
					pila_Cuenta->obtener_Position(i + 1)->set_Nro_Cuenta(aux3);
					pila_Cuenta->obtener_Position(i)->set_Nro_Cuenta(aux4);
					char aux5, aux6;
					aux5 = pila_Cuenta->obtener_Position(i)->get_Tipo();
					aux6 = pila_Cuenta->obtener_Position(i + 1)->get_Tipo();
					pila_Cuenta->obtener_Position(i + 1)->set_Tipo(aux5);
					pila_Cuenta->obtener_Position(i)->set_Tipo(aux6);
					float aux1, aux2;
					aux1 = pila_Cuenta->obtener_Position(i)->get_Cant_Dinero();
					aux2 = pila_Cuenta->obtener_Position(i + 1)->get_Cant_Dinero();
					pila_Cuenta->obtener_Position(i + 1)->set_Cant_Dinero(aux1);
					pila_Cuenta->obtener_Position(i)->set_Cant_Dinero(aux2);
					ordenado = false;
				}
			}
			if (ordenado) break;
		}
	}

	void anadir_listaContactos() {
		Cls;
		int dniParaIngresar;
		do {
			Console::SetCursorPosition(87, 0); cout << "<== VOLVER(0)|\n";
			cout << "\n================================[ CAJERO AUTOMATICO -- AGREGAR CONTACTO FAVORITO ]================================\n\n";
			cout << "\n\20\tIngrese su numero de DNI: "; cin >> dniParaIngresar;
			if (dniParaIngresar == 0) return;
		} while (dniParaIngresar < 0);
		string nombreParaIngresar;
		cout << "\n\20\tIngrese su nombre: "; cin >> nombreParaIngresar;
		if (nombreParaIngresar == "0") return;
		list_favoritos->agregarAlFinal(favorito(nombreParaIngresar, dniParaIngresar));
		Pos; cout << "...CONTACTO AGREGADO..."; _getch();
	}

	void ordenar_listaContactos() { list_favoritos->ordenarListaBurbuja([](favorito f) { return f.get_Dni(); }); }

	void ordenarBeneficios()
	{
		int i, j, k, intervalo = beneficiosUsuario.size() / 2;
		Beneficio* temp;
		float aux1, aux2;

		while (intervalo > 0)
		{
			for (int i = intervalo; i < beneficiosUsuario.size(); i++)
			{
				j = i - intervalo;
				while (j >= 0)
				{
					k = j + intervalo;
					if (beneficiosUsuario.at(j)->getMonto() <= beneficiosUsuario.at(k)->getMonto())j = -1;
					else
					{
						temp = beneficiosUsuario.at(j);
						beneficiosUsuario.at(j) = beneficiosUsuario.at(k);
						beneficiosUsuario.at(k) = temp;
						j -= intervalo;
					}
				}
			}
			intervalo /= 2;
		}
	}

	void ver_listaFavoritos()
	{
		list_favoritos->mostrarLista([](favorito f) {cout << "\20\t" << f.toString() << endl; });
		cout << "\n\n\20\t";
	}

	void anadir_Cuentas()
	{
		char tipo;
		do {
			cout << "\n\n\n\20\tQue tipo de cuenta desea abrir? (S: soles | D: dolares | C: cancelar): "; cin >> tipo;
			tipo = toupper(tipo);
		} while (tipo != 'S' && tipo != 'D' && tipo != 'C');

		if (tipo == 'C')
		{
			cout << endl << endl << "\20\tSaliendo...";
			return;
		}
		Pos; cout << "...Cuenta anadida...";
		_getch(); pila_Cuenta->push_Pila(new Cuenta(tipo));
	}

	void eliminar_Cuentas()
	{
		size_t cuentaElegida;
		do {
			Cls; cout << "\n\20\tHa elegido la opcion ELIMINAR CUENTA." << endl; visualizar_Cuentas();
			cout << "\n\20\tIngrese la cuenta que desea eliminar (99: Retroceder): "; cin >> cuentaElegida;
		} while ((cuentaElegida < 0 || cuentaElegida > pila_Cuenta->Get_Longitud()) && cuentaElegida != 99);
		if (cuentaElegida == 99)
		{
			cout << "\n\20\tHa elegido retroceder...";
			_getch(); return;
		}
		if (pila_Cuenta->obtener_Position(cuentaElegida)->get_Cant_Dinero() > 0)
		{
			cout << "\n\20\tLa cuenta no debe contener dinero para poder ser eliminado...";
			_getch(); return;
		}
		else pila_Cuenta->Erase_Position(cuentaElegida);
	}

	void retirarDinero()
	{
		size_t cuentaElegida;
		do {
			Cls; cout << "\n\20Ha elegido la opcion REALIZAR RETIRO..."; visualizar_Cuentas();
			cout << "\nIngrese la cuenta en la que desea hacer el retiro (99: Retroceder): "; cin >> cuentaElegida;
		} while ((cuentaElegida < 0 || cuentaElegida > pila_Cuenta->Get_Longitud()) && cuentaElegida != 99);
		if (cuentaElegida == 99)
		{
			cout << "\n\20\tHa elegido retroceder";
			_getch(); return;
		}
		float monto; bool op_realizada;
		do
		{
			cout << "\n\20\tIngrese el monto a retirar: "; cin >> monto;
		} while (monto < 0 || monto > pila_Cuenta->obtener_Position(cuentaElegida)->get_Cant_Dinero());
		pila_Cuenta->obtener_Position(cuentaElegida)->retirar_Dinero(monto, op_realizada);
	}

	void depositar_Dinero()
	{
		size_t cuentaElegida;
		do {
			Cls; cout << "\n\20\tHa elegido la opcion REALIZAR DEPOSITO..."; visualizar_Cuentas();
			cout << "\nIngrese la cuenta en la que desea hacer el deposito (99: Retroceder): "; cin >> cuentaElegida;
		} while ((cuentaElegida < 0 || cuentaElegida > pila_Cuenta->Get_Longitud()) && cuentaElegida != 99);
		if (cuentaElegida == 99)
		{
			cout << "\n\20\tHa elegido retroceder";
			_getch(); return;
		}
		float monto; bool op_realizada;
		do {
			cout << "\n\20\tIngrese el monto a depositar: "; cin >> monto;
		} while (monto < 0);
		pila_Cuenta->obtener_Position(cuentaElegida)->depositar_Dinero(monto, op_realizada);
	}

	void anadirBeneficio(float monto) { datos->insert(new Beneficio(monto)); }

	void retornarBeneficios()//........!!!
	{
		Cls;
		//ordenarBeneficios();
		cout << "\n===============================[ USTED CUENTA CON LOS SGTES. BENEFICIOS ]===========================================" << endl << endl;
		if (datos->empty()) cout << "\20\tPor el momento no cuenta con ningun beneficio." << endl << endl;
		else {
			//cout << "--------------[ Los beneficios se han ordedano de menor a mayor]--------------" << endl << endl;
			datos->all_Display();
		}
		cout << "====================================================================================================================" << endl << endl;
		cout << "\n\20\tPresiona cualquier tecla para volver al menu anterior...";
		_getch();
	}

	string get_Nombre() { return nombre; }
	int get_Dni() { return dni; }
	int get_Contrasena() { return contra; }
	int get_CantDeCuentas() { return pila_Cuenta->Get_Longitud(); }
	Cuenta_Operaciones_Pila<Cuenta*>* get_Stack_Cuentas() { return pila_Cuenta; }

	~Usuario() {  }
};