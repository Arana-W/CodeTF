#pragma once
#include "Lista_Generica.h"
#include "Usuario.h"
#include "Cuenta_Op_Pila.h"
#include "Favorito.h"
#include "Lista_Doble_Enlazada.h"

string NOMBRE[18] = { "Hugo","Lucas","Martin","Daniel","Pablo","Mateo","Alex","Leo","Alvaro","Manuel","Adrian", "David", "Mario", "Diego","Enzo", "Marco","Javier", "Izan" };

class Controlador {

private:
	Lista<Usuario*>* list_Usuario;
	vector<string> op_cuenta;
	ofstream escritura_txt;
	ifstream lectura_txt;
	string nombre;
	int dni;
	int contra;
	int deudas;

public:
	Controlador() :nombre(""), dni(0), contra(0) {
		list_Usuario = new Lista<Usuario*>();
	}

	void Leer_Datos_Usuarios()
	{
		lectura_txt.open("list_Usuarios.csv", ios::in);
		if (!lectura_txt) { cout << "\n\n\20\tERROR -- DE ARCHIVO..."; Sleep(1000); exit(1); }
		else {
			string line;
			while (getline(lectura_txt, line, '\n')) {

				stringstream s(line);
				string aux;
				string nombre;
				int dni, contra;

				getline(s, aux, ';');
				nombre = aux;

				getline(s, aux, ';');
				dni = stoi(aux);

				getline(s, aux, ';');
				contra = stoi(aux);

				list_Usuario->push_Back_List(new Usuario(nombre, dni, contra));
			}
		}
		lectura_txt.close();
		lectura_txt.open("list_Cuentas.csv", ios::in);
		if (!lectura_txt) { cout << "\n\n\20\tERROR -- DE ARCHIVO..."; Sleep(1000); exit(1); }
		else {
			string line;
			while (getline(lectura_txt, line, '\n')) {

				stringstream s(line);
				string aux;
				string nombre;
				int dni, contra;

				getline(s, aux, ';');
				nombre = aux;

				getline(s, aux, ';');
				dni = stoi(aux);

				getline(s, aux, ';');
				contra = stoi(aux);

				list_Usuario->push_Back_List(new Usuario(nombre, dni, contra));
			}
		}
		lectura_txt.close();
	}

	void Generar_Datos_Usuarios(size_t cantidad) 
	{
		escritura_txt.open("list_Usuarios.csv");
		if (!escritura_txt) { cout << "\n\n\20\tERROR -- DE ARCHIVO..."; Sleep(1000); exit(1); }
		else {
			for (int i = 0; i < cantidad; i++) {
				int DNI = (71234567 + rand() % (99999999 - 71234567 + 1));
				int CONTRA = (50000 + rand() % (99999 - 50000 + 1));
				string NAME = NOMBRE[rand() % 18];
				escritura_txt << NAME << ";" << DNI << ";" << CONTRA << endl;
				list_Usuario->push_Back_List(new Usuario(NAME, DNI, CONTRA));
			}
			escritura_txt.close();
		}
	}

	void anadir_Usuario(string nombre, int dni, int contra)
	{
		list_Usuario->push_Back_List(new Usuario(nombre, dni, contra));
		escritura_txt.open("list_Cuentas.csv", ios::app);
		escritura_txt << nombre << ";" << dni << ";" << contra << endl;
		escritura_txt.close();
	}

	void Mostrar_Listas_Usuarios(size_t cantidad)
	{
		cout << "\n--------------------------------------[ PERSONAS  REGISTRADAS ]--------------------------------------" << endl << endl;
		int x = 0, registro = 1;
		for (size_t i = 0; i < list_Usuario->longitud(); i++) {
			if (i % (cantidad / 100) == 0) {
				Console::SetCursorPosition((0 + x), 29); cout << char(219);
				Console::SetCursorPosition(42, 27); cout << "COMPLETADO " << char(175) << " " << x << " %"; x++;
				//alt 218 = ┌                                                  ┐ = alt 191
				//alt 179 = │██████████████████████████████████████████████████│ = alt 179
				//alt 192 = └                                                  ┘ = alt 217
				//							 COMPLETADO → 100 %
			}
			Console::SetCursorPosition(0, 2);
			cout << "\n\20\tREGISTROS: " << registro << endl << endl; registro++;
			cout << "\20\tNombre: " << list_Usuario->obtener_Pos(i)->get_Nombre() << "          " << endl;
			cout << "\20\tDNI: " << list_Usuario->obtener_Pos(i)->get_Dni() << endl;
			cout << "\20\tContrasena: " << list_Usuario->obtener_Pos(i)->get_Contrasena() << endl;
			cout << "-----------------------------------------------------------------------------------------------------" << endl;
		}
		Console::SetCursorPosition(100, 29); cout << char(219);
		Console::SetCursorPosition(42, 27); cout << "COMPLETADO " << char(175) << " 100 %";
		Console::SetCursorPosition(0, 9);
		cout << "\n\20\t"; system("pause");
	}

	void Mostrar_Deuda_Pendiente(bool& pagar_cuenta, char& tipo_cuenta)
	{
		deudas = 1000 + rand() % (2000 - 1000 + 1);
		pagar_cuenta = true;
		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		if (deudas > 0) {
			cout << "\n\20\tUsted tiene una deuda de " << deudas;
			if (tipo_cuenta == 'S') cout << " soles.";
			else cout << " dolares.";
			char decision;
			cout << "\n\n\20\tDesea pagar la deuda...? (S:si | N:no): "; cin >> decision;
			decision = toupper(decision);
			if (decision == 'N') pagar_cuenta = false;
		}
		else { cout << "\n\20\t...USTED NO TIENE NINGUNA DEUDA PENDIENTE...\n\20\t"; system("pause"); pagar_cuenta = false; }
	}

	void Mostrar_Historial_Operaciones()
	{
		Cls;
		cout << "\n====================================[ HISTORIAL --- OPERACIONES ]====================================" << endl;
		vector<string>::iterator it;
		for (it = op_cuenta.end() - 1; it != op_cuenta.begin(); it--)
		{
			cout << *it << endl;
		}
		it = op_cuenta.begin();
		cout << *it << endl;
		cout << "\n-----------------------------------------------------------------------------------------------------" << endl;
		cout << "\n\20\t"; system("pause");
	}

	void Eliminar_Historial_Max()
	{
		if (op_cuenta.size() > 5)
		{
			vector<string>::iterator it;
			it = op_cuenta.begin();
			op_cuenta.erase(it);
		}
	}

	void Operaciones_Cuenta(int pos, float monto, char tipo_cuenta)
	{
		string s = "";
		stringstream s1;
		s1 << fixed << setprecision(2) << monto;
		string cash = s1.str();
		switch (pos) {
		case 1:
			s = Fecha_Actual() + " -- Deposito de " + cash;
			if (tipo_cuenta == 'S') s += " soles.";
			else s += " dolares.";
			op_cuenta.push_back(s);
			break;
		case 2:
			s = Fecha_Actual() + " -- Retiro de " + cash;
			if (tipo_cuenta == 'S') s += " soles.";
			else s += " dolares.";
			op_cuenta.push_back(s);
			break;
		case 3:
			s = Fecha_Actual() + " -- Deuda de " + cash;
			if (tipo_cuenta == 'S') s += " soles.";
			else s += " dolares.";
			op_cuenta.push_back(s);
			break;
		}
	}

	bool comprobar_Dni(int dni, int& pos)
	{
		bool dniExiste = false;
		for (size_t i = 0; i < list_Usuario->longitud(); i++) {
			if (list_Usuario->obtener_Pos(i)->get_Dni() == dni) { dniExiste = true; pos = i; }
		}
		return dniExiste;
	}

	bool comprobar_Contra(int contra, int& pos)
	{
		bool contraCorrecta = false;
		if (list_Usuario->obtener_Pos(pos)->get_Contrasena() == contra) contraCorrecta = true;
		return contraCorrecta;
	}

	float recursividad_Dinero_Total(int& pos, int pos_i)
	{
		if (list_Usuario->esVacia() == false && list_Usuario->obtener_Pos(pos)->get_CantDeCuentas() > 0)
		{
			if (pos_i >= list_Usuario->obtener_Pos(pos)->get_CantDeCuentas()) return 0;

			char tipo = list_Usuario->obtener_Pos(pos)->get_Stack_Cuentas()->obtener_Position(pos_i)->get_Tipo();
			float sum = list_Usuario->obtener_Pos(pos)->get_Stack_Cuentas()->obtener_Position(pos_i)->get_Cant_Dinero();

			if (tipo == 'D') sum *= 3.78;
			return sum + recursividad_Dinero_Total(pos, pos_i + 1);
		}
		else return 0;
	}

	Usuario* get_Usuario(int& pos) { return list_Usuario->obtener_Pos(pos); }

	string Fecha_Actual()
	{
		int hours, minutes, seconds, day, month, year;
		time_t now = time(NULL);
		struct tm* local;
		local = localtime(&now);

		hours = local->tm_hour;      // obtener horas desde la medianoche (0-23)
		minutes = local->tm_min;     // obtener minutos pasados después de la hora (0-59)
		seconds = local->tm_sec;     // obtener segundos pasados después de un minuto (0-59)

		day = local->tm_mday;        // obtener el día del mes (1 a 31)
		month = local->tm_mon + 1;   // obtener el mes del año (0 a 11)
		year = local->tm_year + 1900;// obtener el año desde 1900

		string fecha = "\n\t\20 [" + to_string(day) + "/" + to_string(month) + "/" + to_string(year), hora = " | ";
		if (hours < 12) {// antes del mediodia
			hora += to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds) + "]";
		}
		else {// Después de mediodía
			hora += to_string(hours - 12) + ":" + to_string(minutes) + ":" + to_string(seconds) + "]";
		}
		fecha += hora;
		return fecha;
	}

	int get_Deuda() { return deudas; }
	int getCantUsuario() {
		int convertdata = static_cast<int>(list_Usuario->longitud());
		return convertdata;
	}

	~Controlador() {  }
};