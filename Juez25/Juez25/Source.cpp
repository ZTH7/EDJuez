// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

#include <list>
#include "Header.h"

void eliminar(std::list<Hora>& lista) {
    for (auto it = lista.begin(); it != lista.end();) {
        ++it;
        if (it != lista.end()) lista.erase(it++);
    }
}

void mostrar(const std::list<Hora>& lista) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        std::cout << *it << " ";
    }
}

// función que resuelve el problema
void resolver(std::list<Hora>& lista) {
    eliminar(lista);
    mostrar(lista);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    if (num == 0)
        return false;

    Hora hora;
    std::list<Hora> lista;

    for (int i = 0; i < num; i++) {
        std::cin >> hora;
        lista.push_back(hora);
    }

    resolver(lista);

    // escribir sol
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
