// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
#include <string>

// función que resuelve el problema
std::deque<char> resolver(std::deque<char>& datos) {
    std::deque<char> res, tmp;
    bool turno = datos.size() % 2 != 0;

    while(!datos.empty()){
        if (turno) res.push_front(datos.back());
        else res.push_back(datos.back());
        datos.pop_back();
        turno ^= true;
    }

    for (long unsigned int i = 0; i < res.size(); i++) {
        if (res[i] != 'a' && res[i] != 'e' && res[i] != 'i' && res[i] != 'o' && res[i] != 'u' && 
            res[i] != 'A' && res[i] != 'E' && res[i] != 'I' && res[i] != 'O' && res[i] != 'U') {
            tmp.push_back(res[i]);
        }
        else {
            while (!tmp.empty()) {
                res[i - tmp.size()] = tmp.back();
                tmp.pop_back();
            }
        }
    }

    while (!tmp.empty()) {
        res[res.size() - tmp.size()] = tmp.back();
        tmp.pop_back();
    }

    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string str;
    getline(std::cin, str);

    if (!std::cin)
        return false;

    std::deque<char> datos;
    for (long unsigned int i = 0; i < str.length(); ++i) {
        datos.push_back(str[i]);
    }

    std::deque<char> sol = resolver(datos);

    // escribir sol
    for (char c : sol) {
        std::cout << c;
    }
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