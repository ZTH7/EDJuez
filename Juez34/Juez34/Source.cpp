// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"


// función que resuelve el problema
std::pair<int, int> resolver(bintree<char> tree) {
	if (tree.empty())
		return { 0, 0 };

	std::pair<int, int> izq = resolver(tree.left());
	std::pair<int, int> der = resolver(tree.right());

	int max = izq.first + der.first + 1;
	max = izq.second > max ? izq.second : max;
	max = der.second > max ? der.second : max;

	return { (izq.first > der.first ? izq.first : der.first) + 1, max };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<char> tree;

	tree = leerArbol('.');

	std::pair<int, int> sol = resolver(tree);

	// escribir sol
	std::cout << sol.second << std::endl;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}