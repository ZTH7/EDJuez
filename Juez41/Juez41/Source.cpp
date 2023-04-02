// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tInfo
{
	bool res = false;
	int nodo = -1;
	int min = -1;
	int max = -1;
};

// función que resuelve el problema
tInfo resolver(bintree<int> const& tree) {
	if (tree.empty())
		return { true, -1, -1, -1 };

	tInfo izq = resolver(tree.left());

	if (!izq.res)
		return { false, -1, -1, -1 };

	tInfo der = resolver(tree.right());

	if (!der.res)
		return { false, -1, -1, -1 };

	/*---------------------------------------------------------*/

	if(izq.nodo == -1 && der.nodo == -1)
		return { true, tree.root(), tree.root(), tree.root() };
	
	if (izq.nodo == -1) {
		if(der.nodo <= tree.root() || der.min <= tree.root())
			return { false, -1, -1, -1 };

		return { true, tree.root(), tree.root(), der.max };
	}

	if (der.nodo == -1) {
		if (izq.nodo >= tree.root() || izq.max >= tree.root())
			return { false, -1, -1, -1 };

		return { true, tree.root(), izq.min, tree.root() };
	}

	if(der.nodo <= tree.root() || izq.nodo >= tree.root())
		return { false, -1, -1, -1 };
	
	if (der.min <= tree.root() || izq.max >= tree.root())
		return { false, -1, -1, -1 };

	int min = izq.min < der.min ? izq.min : der.min;
	int max = izq.max > der.max ? izq.max : der.max;

	return { true, tree.root(), min, max };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> tree;
	tInfo sol;

	tree = leerArbol(-1);

	if (tree.empty() || tree.root() >= 0)
		sol = resolver(tree);
		
	// escribir sol
	std::cout << (sol.res ? "SI" : "NO") << std::endl;

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