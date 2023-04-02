// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>


// función que resuelve el problema
void resolver(std::map<std::string, std::vector<int>>& datos, int index) {
    std::string str, palabra;
    getline(std::cin, str);
    std::stringstream ss(str);
    while (ss >> palabra) {
        if (palabra.length() < 3)
            continue;

        transform(palabra.begin(), palabra.end(), palabra.begin(), tolower);

        auto it = datos.find(palabra);
        if (it == datos.end()) {
            std::vector<int> v;
            v.push_back(index);
            datos.emplace(palabra, v);
        }
        else {
            if(*(it->second.end() - 1) != index)
                it->second.push_back(index);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    std::cin.ignore();
    if (num == 0)
        return false;

    std::map<std::string, std::vector<int>> datos;

    for (int i = 0; i < num; i++)
        resolver(datos, i + 1);

    // escribir sol
    for (auto& i : datos) {
        std::cout << i.first;
        for (int j : i.second)
            std::cout << " " << j;
        std::cout << std::endl;
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
