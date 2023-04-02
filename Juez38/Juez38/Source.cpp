// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"


// función que resuelve el problema
bintree<int> resolver(bintree<int> tree) {
	if (tree.empty())
		return {};

	bintree<int> izq = resolver(tree.left());
	bintree<int> der = resolver(tree.right());

	if(izq.empty() && der.empty())
		return { izq, tree.root(), der};

	int left = 0, right = 0;
	if (!izq.empty())
		left = izq.root();
	if (!der.empty())
		right = der.root();

	return { izq, left + right, der};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> tree;

	tree = leerArbol(-1);

	auto sol = resolver(tree).preorder();

	// escribir sol
	for(int i : sol)
		std::cout << i << " ";
	std::cout << std::endl;
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