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
std::vector<std::pair<std::string, std::pair<int, int>>> resolver(const std::unordered_map<std::string, std::pair<int, int>>& datos) {
    std::vector<std::pair<std::string, std::pair<int, int>>> v(datos.begin(), datos.end());

    std::sort(v.begin(), v.end(), [](const std::pair<std::string, std::pair<int, int>>& a, const std::pair<std::string, std::pair<int, int>>& b) {
        if (a.second.first != b.second.first)
            return a.second.first > b.second.first;
        if (a.second.second != b.second.second)
            return a.second.second < b.second.second;
        return a.first < b.first;
        });

    return v;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::unordered_map<std::string, std::pair<int, int>> datos;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> aux;
    
    std::string grupo, pregunta, resulta;
    int tiempo;
    std::cin >> grupo;
    while (grupo != "FIN") {
        std::cin >> pregunta >> tiempo >> resulta;
        auto it_aux = aux.find(grupo);

        if (it_aux == aux.end())
            aux.insert({ grupo, {{pregunta,0}} });
        else if (it_aux->second.find(pregunta) == it_aux->second.end())
            it_aux->second.insert({ pregunta, 0 });

        if (datos.find(grupo) == datos.end())
            datos.insert({ grupo, {0, 0} });
        
        if (resulta != "AC") {
            if(aux[grupo][pregunta] != -1)
                aux[grupo][pregunta] += 20;
        }
        else {
            if (aux[grupo][pregunta] != -1) {
                datos[grupo].first++;
                datos[grupo].second += aux[grupo][pregunta] + tiempo;
                aux[grupo][pregunta] = -1;
            }
        }
        std::cin >> grupo;
    }

    auto v = resolver(datos);

    // escribir sol
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << it->first << " " << it->second.first << " " << it->second.second << std::endl;
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
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}