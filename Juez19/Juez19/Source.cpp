// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>


// función que resuelve el problema
int resolver(std::queue<int>& datos, int num) {
    int contador = 0;

    while (datos.size() > 1) {
        if (contador < num) {
            datos.push(datos.front());
            contador++;
        }
        else contador = 0;

        datos.pop();
    }

    return datos.front();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int ini, num;
    std::cin >> ini >> num;

    if (ini == 0 && num == 0)
        return false;

    std::queue<int> datos;
    for (int i = 1; i <= ini; i++) {
        datos.push(i);
    }

    int sol = resolver(datos, num);

    // escribir sol
    std::cout << sol << std::endl;

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
