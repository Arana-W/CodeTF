#pragma once
#include "Header.h"
#include "Beneficios.h"

template<class T>
class HashTableBeneficio {

	vector<list<T>> data;

public:
	HashTableBeneficio(size_t size)
	{
		data.resize(size);
	}

	void make_Empty()
	{
		return data.clear();
	}

	bool empty() 
	{
		for (auto& thisList : data) {
			if (thisList.size() != 0) return false;
		}
		return true;
	}

	bool insert(Beneficio* x)
	{
		data[my_Hash(x->getMonto())].push_back(x); //Obtenemos la lista de elementos según el hash obtenido
		return true;
	}

	void all_Display() 
	{
		int pos = 0;
		for (auto& thisList : data) {
			for (auto& it : data[pos]) {
				cout << "- Key: " + to_string(pos) << " | ";
				string aux = it->getTexto();
				cout << "\20\t" << aux << endl << endl;
			}
			pos++;
		}
	}

private:
	size_t my_Hash(size_t key) 
	{
		size_t hash_Value = 1;
		size_t cnt_r = NULL;
		while (key > 0) {
			if (key & 1) cnt_r++;
			key = (key >> 1);
		}
		for (int i = 1; i <= cnt_r; i++) {
			hash_Value += (hash_Value * (1 << i));
		}
		return (hash_Value % data.size());
	}
};