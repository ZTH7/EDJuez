// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

template <typename T>
class bintree_plus : public bintree<T> {
    using Link = typename bintree<T>::Link;
    using TreeNode = typename bintree<T>::TreeNode;
public:
    // árbol vacío
    bintree_plus() : bintree<T>(nullptr) {}

    // árbol hoja
    bintree_plus(T const& e) : bintree<T>(e) {}

    // árbol con dos hijos
    bintree_plus(bintree_plus<T> const& l, T const& e, bintree_plus<T> const& r) : bintree<T>(l, e, r) {}

    int level(T target, T vacio) {
        int levelActual = 1;
        int contador = 0;
        if (!bintree<T>::empty()) {
            std::queue<Link> pendientes;
            pendientes.push(this->raiz);
            pendientes.push(std::make_shared<TreeNode>(nullptr, vacio, nullptr));
            while (!pendientes.empty() && contador <= 1) {
                Link sig = pendientes.front();
                pendientes.pop();
                if (sig->elem == vacio) {
                    levelActual++;
                    contador = 0;
                    pendientes.push(std::make_shared<TreeNode>(nullptr, vacio, nullptr));
                    sig = pendientes.front();
                    pendientes.pop();
                }

                if (sig->elem == target)
                    contador++;

                if (sig->left != nullptr)
                    pendientes.push(sig->left);
                if (sig->right != nullptr)
                    pendientes.push(sig->right);
            }
        }

        return contador > 1 ? levelActual : 0;
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
    int sol = 0;
    char option;
    std::cin >> option;
    bintree_plus<int> Ntree;
    bintree_plus<char> Ctree;

    if (option == 'N') {
        int target;
        std::cin >> target;
        Ntree = leerArbol_plus(-1);
        sol = Ntree.level(target, -1);
    }
    else if (option == 'C') {
        char target;
        std::cin >> target;
        Ctree = leerArbol_plus('.');
        sol = Ctree.level(target, '.');
    }

   
    // escribir sol
    if(sol == 0)
        std::cout << "NO EXISTE" << std::endl;
    else
        std::cout << sol << std::endl;

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