// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tInfo
{
	int agua = 0;
	int tramo = 0;
};

// función que resuelve el problema
tInfo resolver(bintree<int> const& tree) {
	if (tree.empty())
		return { 0, 0 };

	if (tree.left().empty() && tree.right().empty())
		return { 1, 0 };

	tInfo izq = resolver(tree.left());
	tInfo der = resolver(tree.right());

	if (izq.agua >= 3)
		izq.tramo++;

	if (der.agua >= 3)
		der.tramo++;

	int agua = izq.agua + der.agua - tree.root();

	return { agua > 0 ? agua : 0, izq.tramo + der.tramo };

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> tree;

	tree = leerArbol(-1);

	auto sol = resolver(tree);

	// escribir sol
	std::cout << sol.tramo << std::endl;
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