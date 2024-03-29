// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>


// función que resuelve el problema
int resolver(const std::vector<int>& v) {
    int max = 0, ind = 0;
    std::map<int, int> aux;

    for (int i = 0; i < v.size(); i++) {
        auto it = aux.find(v[i]);

        if (it == aux.end()) {
            aux.emplace(v[i], i);
        }
        else {
            max = max > aux.size() ? max : aux.size();

            int fin = it->second;
            for (; ind <= fin; ind++)
                aux.erase(v[ind]);

            aux.emplace(v[i], i);
        }
    }
    max = max > aux.size() ? max : aux.size();

    return max;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;

    std::vector<int> v(num);
    for (int i = 0; i < num; i++)
        std::cin >> v[i];

    int sol = resolver(v);

    // escribir sol
    std::cout << sol << std::endl;

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