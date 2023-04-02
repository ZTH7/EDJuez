// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

struct tInfo {
    std::vector<std::string> nueva;
    std::vector<std::string> eliminado;
    std::vector<std::string> modificado;
};

// función que resuelve el problema
tInfo resolver(std::map<std::string, std::string>& preMap, std::map<std::string, std::string>& posMap) {
    tInfo res;
    for (auto i : posMap) {
        auto it = preMap.find(i.first);
        if (it == preMap.end()) {
            res.nueva.push_back(i.first);
        }
        else {
            if (it->second != i.second)
                res.modificado.push_back(it->first);
            preMap.erase(it);
        }
    }

    for (auto i : preMap)
        res.eliminado.push_back(i.first);

    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::string preStr, posStr, str1, str2;
    getline(std::cin, preStr);
    getline(std::cin, posStr);

    std::map<std::string, std::string> preMap, posMap;
    std::stringstream pres(preStr);
    while (pres >> str1 >> str2)
        preMap.emplace(str1, str2);

    std::stringstream poss(posStr);
    while (poss >> str1 >> str2)
        posMap.emplace(str1, str2);

    tInfo sol = resolver(preMap, posMap);
    // escribir sol
    if (sol.nueva.size() == 0 && sol.eliminado.size() == 0 && sol.modificado.size() == 0) {
        std::cout << "Sin cambios" << std::endl;
    }
    else {
        if (sol.nueva.size() != 0) {
            std::cout << "+";
            for (auto i : sol.nueva)
                std::cout << " " << i;
            std::cout << std::endl;
        }

        if (sol.eliminado.size() != 0) {
            std::cout << "-";
            for (auto i : sol.eliminado)
                std::cout << " " << i;
            std::cout << std::endl;
        }

        if (sol.modificado.size() != 0) {
            std::cout << "*";
            for (auto i : sol.modificado)
                std::cout << " " << i;
            std::cout << std::endl;
        }
    }

    std::cout << "---" << std::endl;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    std::cin.ignore();
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}