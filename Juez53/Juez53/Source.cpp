// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>

// función que resuelve el problema
int resolver(const std::unordered_map<int, std::vector<int>>& map, int caso, int numero) {
    auto it = map.find(numero);

    if (it == map.end() || it->second.size() < caso)
        return -1;

    return it->second[caso - 1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numLista, numCaso;
    std::cin >> numLista >> numCaso;

    if (!std::cin)
        return false;

    std::unordered_map<int, std::vector<int>> map;
    for (int i = 1; i <= numLista; i++) {
        int x;
        std::cin >> x;
        auto it = map.find(x);
        if (it == map.end()) {
            map.insert({ x, {i} });
        }
        else {
            it->second.push_back(i);
        }
    }

    for (int i = 0; i < numCaso; i++) {
        int caso, numero;
        std::cin >> caso >> numero;

        int sol = resolver(map, caso, numero);

        // escribir sol
        if (sol == -1)
            std::cout << "NO HAY" << std::endl;
        else
            std::cout << sol << std::endl;
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