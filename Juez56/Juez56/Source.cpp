// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tInfo
{
	std::string lider;
	int num = 0;
};

// función que resuelve el problema
tInfo resolver(bintree<std::string> const& tree) {
	if (tree.empty())
		return { "", 0};

	if (tree.left().empty() && tree.right().empty())
		return { tree.root(), 1};

	tInfo izq = resolver(tree.left());
	tInfo der = resolver(tree.right());

	tInfo res;
	res.num = izq.num + der.num;
	if (tree.root() == "Orcos")
		res.num /= 2;

	if (res.num == 0)
		res.lider = "";
	else if (izq.num == der.num)
		res.lider = izq.lider < der.lider ? izq.lider : der.lider;
	else
		res.lider = izq.num > der.num ? izq.lider : der.lider;

	return res;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<std::string> tree;

	tree = leerArbol(std::string("."));

	auto sol = resolver(tree);

	// escribir sol
	if(sol.num > 0)
		std::cout << sol.lider << " " << sol.num << std::endl;
	else
		std::cout << "Ninguno" << std::endl;
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