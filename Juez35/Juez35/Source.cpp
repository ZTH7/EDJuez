// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"


// función que resuelve el problema
std::pair<int, int> resolver(bintree<int> tree) {
	if (tree.empty())
		return { 0, 0 };

	std::pair<int, int> izq = resolver(tree.left());
	std::pair<int, int> der = resolver(tree.right());

	if (izq.first != 0 || der.first != 0)
		return { izq.first + der.first, (izq.second > der.second ? izq.second : der.second) + tree.root() };

	if (tree.root() != 0)
		return { 1, tree.root() };

	return { 0, 0 };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> tree;

	tree = leerArbol(-1);

	std::pair<int, int> sol = resolver(tree);

	// escribir sol
	std::cout << sol.first << " " << sol.second << std::endl;

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