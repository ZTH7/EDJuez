// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <sstream>
#include <string>

// función que resuelve el problema
void resolver(std::unordered_map<int, std::unordered_set<std::string>>& datos, std::unordered_set<int>& v, std::set<std::string>& nombres) {
    for (int x : v) {
        datos.erase(x);
    }

    std::set<std::string> aux = nombres;
    for (const std::string& str : aux) {
        for (auto& p : datos) {
            if (p.second.count(str) > 0) {
                nombres.erase(str);
                break;
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, x;
    std::cin >> num;
    if (num == 0)
        return false;

    std::string numEntrada;
    std::unordered_set<int> v;
    std::set<std::string> nombres;
    std::unordered_map<int, std::unordered_set<std::string>> datos;

    for (int i = 0; i < num; i++) {
        std::string name;
        std::cin >> name;
        nombres.emplace(name);
        std::cin >> x;
        while (x != 0) {
            datos[x].insert(name);
            std::cin >> x;
        }
    }

    std::cin.ignore();
    std::getline(std::cin, numEntrada);
    std::stringstream ss(numEntrada);
    int aux;
    while (ss >> aux) {
        v.emplace(aux);
    }

    resolver(datos, v, nombres);

    // escribir sol
    for (const std::string& str : nombres)
        std::cout << str << " ";
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
