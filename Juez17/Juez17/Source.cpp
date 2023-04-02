// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "stack_eda.h"

// función que resuelve el problema
bool resolver(std::string str) {
    stack<char> sta;

    for (long unsigned int i = 0; i < str.size(); i++) {

        switch (str[i]) {
        case '(':
            sta.push(')');
            break;
        case '[':
            sta.push(']');
            break;
        case '{':
            sta.push('}');
            break;
        case ')':
            if (sta.empty() || str[i] != sta.top()) return false;
            else sta.pop();
            break;
        case ']':
            if (sta.empty() || str[i] != sta.top()) return false;
            else sta.pop();
            break;
        case '}':
            if (sta.empty() || str[i] != sta.top()) return false;
            else sta.pop();
            break;
        }
    }

    return sta.empty();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string str;
    getline(std::cin, str);

    if (!std::cin)
        return false;

    bool sol = resolver(str);

    // escribir sol
    if (sol) std::cout << "SI" << std::endl;
    else std::cout << "NO" << std::endl;

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