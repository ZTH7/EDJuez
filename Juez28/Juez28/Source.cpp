// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>


template <class T, class Predicate>
void remove_if(std::list<T>& lista, Predicate pred) {
    for (auto it = lista.begin(); it != lista.end();) {
        if (pred(it->first)) lista.erase(it++);
        else it++;
    }
}

// función que resuelve el problema
void resolver(std::list<std::pair<int, std::string>>& lista, int min, int max) {
    remove_if(lista, [min, max](int edad) -> bool {
        return edad < min || edad > max;
        });
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int num, min, max;
    std::cin >> num >> min >> max;

    if (num == 0 && min == 0 && max == 0)
        return false;

    std::list<std::pair<int, std::string>> lista;
    std::pair<int, std::string> tmp;

    for (int i = 0; i < num; i++) {
        std::cin >> tmp.first;
        std::cin.ignore();
        getline(std::cin, tmp.second);
        lista.push_back(tmp);
    }

    resolver(lista, min, max);

    // escribir sol
    for (auto it = lista.begin(); it != lista.end(); it++) {
        std::cout << it->second << std::endl;
    }
    std::cout << "---" << std::endl;

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
