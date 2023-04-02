// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

#include "Header.h"

// función que resuelve el problema
std::string resolver(const linked_list_ed<std::string>& lista, char c) {
    return lista.search(c, 0);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char c;
    std::cin >> c;
    if (!std::cin) return false;
    linked_list_ed <std::string> lista;
    std::string str;
    getline(std::cin, str); // para saltar el final de linea
    getline(std::cin, str); // lee la linea del caso
    std::stringstream ss(str); // construye el objeto ss de tipo stringstream
    while (ss) {
        std::string aux;
        ss >> aux;
        lista.push_back(aux);
    }

    std::string sol = resolver(lista, c);

    // escribir sol
    std::cout << sol << std::endl;

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