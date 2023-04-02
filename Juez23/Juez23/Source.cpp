// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>

// función que resuelve el problema
std::deque<int> resolver(std::deque<int>& datos, int caso) {
    std::deque<int> res, tmp;

    for (int i = 0; i < datos.size(); i++) {
        if (!tmp.empty() && tmp.front() <= i - caso) {
            tmp.pop_front();
        }

        while (!tmp.empty() && datos[tmp.back()] < datos[i]) {
            tmp.pop_back();
        }
        tmp.push_back(i);

        if (i >= caso - 1) res.push_back(datos[tmp.front()]);
    }

    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, caso, x;
    std::deque<int> datos;
    std::cin >> num >> caso;

    if (num == 0 && caso == 0)
        return false;

    for (int i = 0; i < num; i++) {
        std::cin >> x;
        datos.push_back(x);
    }

    std::deque<int> sol = resolver(datos, caso);

    // escribir sol
    for(int i : sol){
        std::cout << i << " ";
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
