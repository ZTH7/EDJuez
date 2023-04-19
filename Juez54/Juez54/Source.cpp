// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>


// función que resuelve el problema
std::vector<std::pair<std::string, int>> resolver(const std::unordered_map<std::string, int>& datos) {
    std::vector<std::pair<std::string, int>> v(datos.begin(), datos.end());

    std::sort(v.begin(), v.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
        });

    return v;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string x, nombre;
    std::cin >> x;

    if (!std::cin)
        return false;
    
    std::unordered_map<std::string, int> datos;
    std::unordered_map<std::string, std::string> aux;
    while (x != "_FIN_") {
        if (std::isupper(x[0])) {
            datos.insert({ x, 0 });
            nombre = x;
        }
        else {
            auto it = aux.find(x);
            if (it == aux.end()) {
                datos[nombre]++;
                aux.insert({ x, nombre });
            }
            else {
                if (it->second != "" && it->second != nombre) {
                    datos[it->second]--;
                    it->second = "";
                }
            }
        }
        std::cin >> x;
    }

    auto v = resolver(datos);

    // escribir sol
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
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