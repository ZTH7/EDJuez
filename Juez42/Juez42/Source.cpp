// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bintree_eda.h"

template <typename T>
class bintree_plus : public bintree<T> {
    using Link = typename bintree<T>::Link;
    using TreeNode = typename bintree<T>::TreeNode;
public:
    // árbol vacío
    bintree_plus() : bintree<T>(nullptr) {}

    // árbol con dos hijos
    bintree_plus(bintree_plus<T> const& l, T const& e, bintree_plus<T> const& r) : bintree<T>(l, e, r) {}

    std::vector<T> perfil(T vacio) {
        std::vector<T> res;

        if (!bintree<int>::empty()) {
            std::queue<Link> pendientes;
            pendientes.push(this->raiz);
            pendientes.push(std::make_shared<TreeNode>(nullptr, vacio, nullptr));

            T aux;
            while (!pendientes.empty()) {
                if (pendientes.front()->elem == vacio) {
                    pendientes.pop();
                    res.push_back(aux);

                    if (pendientes.empty())
                        return res;

                    pendientes.push(std::make_shared<TreeNode>(nullptr, vacio, nullptr));
                }

                aux = pendientes.front()->elem;
                Link sig = pendientes.front();

                if (sig->left != nullptr)
                    pendientes.push(sig->left);
                if (sig->right != nullptr)
                    pendientes.push(sig->right);

                pendientes.pop();

            }
        }

        return res;
    }
};

// lee un árbol binario de la entrada estándar
template <typename T>
inline bintree_plus<T> leerArbol_plus(T vacio) {
    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un árbol vacío
        return {};
    }
    else { // leer recursivamente los hijos
        auto iz = leerArbol_plus(vacio);
        auto dr = leerArbol_plus(vacio);
        return { iz, raiz, dr };
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
    bintree_plus<int> tree;

	tree = leerArbol_plus(-1);

	auto sol = tree.perfil(-1);

	// escribir sol
    for (int i : sol)
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