// Problema El regreso de los enanos

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba


#include <iostream>
#include <fstream>
#include <string>
#include "bintree_eda.h"

// Explicación del algoritmo



// Coste de la función. Para justificar el coste se debe indicar la recurrencia utilizada para calcularlo. Indicar el coste para árboles equilibrados y para árboles degenerados




// Aqui las funciones del alumno
int resolver(const bintree<int>& tree) {
    if (tree.empty())
        return 0;

    int izq = resolver(tree.left());
    if (izq == -1)
        return -1;
    int der = resolver(tree.right());
    if (der == -1)
        return -1;
    
    int aux = izq - der;
    if (aux < -1 || aux > 1)
        return -1;

    if (tree.root() == 0)
        return izq + der + 1;
    else
        return izq + der;
}



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> arbol = leerArbol(-1);
    // LLamada a la función ue resuelve el problema
    int sol = resolver(arbol);


    // Escribir los resultados
    std::cout << (sol == -1 ? "NO" : "SI") << std::endl;



}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

