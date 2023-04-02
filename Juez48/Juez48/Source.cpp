// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tInfo
{
	int actual = 0;
	int max = 0;
};

// función que resuelve el problema
tInfo resolver(bintree<int> const& tree) {
	if (tree.empty())
		return { 0, 0 };

	tInfo izq = resolver(tree.left());
	tInfo der = resolver(tree.right());

	int max = izq.max > der.max ? izq.max : der.max;

	if (tree.root() % 2 != 0)
		return { 0, max };

	int aux = 1 + (izq.actual > der.actual ? izq.actual : der.actual);
	
	int tmp = izq.actual + der.actual + 1;

	return { aux, max > tmp ? max : tmp };

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> tree;

	tree = leerArbol(-1);

	auto sol = resolver(tree);

	// escribir sol
	std::cout << sol.max << std::endl;
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