// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"


// función que resuelve el problema
template <typename T>
T resolver(bintree<T> tree) {
    T min = *tree.begin();
    for (auto it = ++tree.begin(); it != tree.end(); ++it) {
        if (min > *it) min = *it;
    }
    return min;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char option;
    std::cin >> option;
    bintree<int> Ntree;
    bintree<std::string> Ptree;

    if (!std::cin)
        return false;

    if (option == 'N') {
        Ntree = leerArbol(-1);
        int sol = resolver(Ntree);
        std::cout << sol << std::endl;
    }
    else if (option == 'P') {
        Ptree = leerArbol(static_cast<std::string>("#"));
        std::string sol = resolver(Ptree);
        std::cout << sol << std::endl;
    }

    // escribir sol

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}