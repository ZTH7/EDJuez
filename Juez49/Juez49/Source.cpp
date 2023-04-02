// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>


// función que resuelve el problema
void resolver(std::map<std::string, int>& datos) {
    std::string name, result;
    getline(std::cin, name);
    getline(std::cin, result);
    int note = result == "CORRECTO" ? 1 : -1;

    auto it = datos.find(name);
    if (it == datos.end()) {
        datos.emplace(name, note);
    }
    else {
        it->second += note;
        if (it->second == 0)
            datos.erase(it);
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

    std::map<std::string, int> datos;

    for (int i = 0; i < num; i++)
        resolver(datos);

    // escribir sol
    for (auto& i : datos)
        std::cout << i.first << ", " << i.second << std::endl;

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
