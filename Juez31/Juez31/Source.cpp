// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tInfo {
	bool isEmpty = false;
	int nodo = 0;
	int hoja = 0;
	int altura = 0;
};

// función que resuelve el problema
tInfo resolver(bintree<char> tree) {
	if (tree.empty())
		return { true, 0, 0, 0 };

	tInfo izq = resolver(tree.left());
	tInfo der = resolver(tree.right());

	tInfo res;
	res.isEmpty = false;
	res.nodo = izq.nodo + der.nodo + 1;
	res.altura = (izq.altura > der.altura ? izq.altura : der.altura) + 1;
	res.hoja = izq.hoja + der.hoja;

	if (izq.isEmpty && der.isEmpty)
		res.hoja++;

	return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<char> tree;
	tree = leerArbol('.');

	tInfo sol = resolver(tree);

	// escribir sol
	std::cout << sol.nodo << " " << sol.hoja << " " << sol.altura << std::endl;

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