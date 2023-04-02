// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>


template <class T>
T Mysearch(T const& ini1, T const& fin1, T const& ini2, T const& fin2) {
	auto it1 = ini1; auto it2 = ini2;
	while (it1 != fin1 && it2 != fin2) {
		if (*it1 == *ini2) { // recorre el subrango
			auto aux1 = it1; it2 = ini2;
			while (aux1 != fin1 && it2 != fin2 && *aux1 == *it2) {
				++aux1;
				++it2;
			}
			if (it2 != fin2) ++it1;
		}
		else ++it1;
	}
	return it1;
}

// función que resuelve el problema
void resolver(std::list<int>& lista1, std::list<int>& lista2) {
	auto it = lista1.begin();
	while (it != lista1.end()) {
		it = Mysearch(it, lista1.end(), lista2.begin(), lista2.end());
		if (it != lista1.end()) {
			for (int i = 0; i < lista2.size(); ++i) {
				it = lista1.erase(it);
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int num1, num2, x;
	std::cin >> num1 >> num2;

	if (num1 == 0 && num2 == 0)
		return false;

	std::list<int> lista1, lista2;
	for (int i = 0; i < num1; i++) {
		std::cin >> x;
		lista1.push_back(x);
	}

	for (int i = 0; i < num2; i++) {
		std::cin >> x;
		lista2.push_back(x);
	}

	resolver(lista1, lista2);

	// escribir sol
	auto it = lista1.begin();
	if (it != lista1.end()) {
		std::cout << *it;
		++it;
	}
	for (; it != lista1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
