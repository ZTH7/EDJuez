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
bintree<int> resolver(std::vector<int>& preorden, std::vector<int>& inorden, int preIni, int preFin, int inIni, int inFin) {
    if (preIni > preFin || inIni > inFin)
        return {};

    int raiz = preorden[preIni], inSep = inIni;

    for (; inSep <= inFin && inorden[inSep] != raiz; inSep++);

    int preSep = preIni + (inSep - inIni);

    bintree<int> izq = resolver(preorden, inorden, preIni + 1, preSep, inIni, inSep - 1);

    bintree<int> der = resolver(preorden, inorden, preSep + 1, preFin, inSep + 1, inFin);

    return { izq, raiz, der };

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::vector<int> preorden, inorden;
    std::string str;
    std::getline(std::cin, str);

    if (!std::cin)
        return false;

    int x;
    std::stringstream preor(str);
    while (preor >> x)
        preorden.push_back(x);

    std::getline(std::cin, str);
    std::stringstream inor(str);
    while (inor >> x)
        inorden.push_back(x);

    int prepos = 0;
    std::vector<int> sol = resolver(preorden, inorden, 0, preorden.size() - 1, 0, inorden.size() - 1).postorder();

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