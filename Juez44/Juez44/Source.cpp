// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "bintree_eda.h"


// función que resuelve el problema
bintree<int> resolver(std::vector<int>& preorden, int preIni, int preFin) {
    if (preIni > preFin)
        return {};

    int raiz = preorden[preIni], preSep = preIni + 1;

    for (; preSep <= preFin && preorden[preSep] < raiz; preSep++);

    bintree<int> izq = resolver(preorden, preIni + 1, preSep - 1);

    bintree<int> der = resolver(preorden, preSep, preFin);

    return { izq, raiz, der };

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::vector<int> preorden;
    std::string str;
    std::getline(std::cin, str);

    if (!std::cin)
        return false;

    int x;
    std::stringstream preor(str);
    while (preor >> x)
        preorden.push_back(x);

    std::vector<int> sol = resolver(preorden, 0, preorden.size() - 1).postorder();

    // escribir sol
    for (int i : sol)
        std::cout << i << " ";
    std::cout << std::endl;

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