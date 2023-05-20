// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>

class carnet_puntos {
    std::unordered_map<std::string, int> tabla_dni;
    std::unordered_map<int, int> tabla_punto;
public:
    void nuevo(std::string const& dni) {
        if (tabla_dni.find(dni) != tabla_dni.end())
            throw std::domain_error("Conductor duplicado");

        tabla_dni.insert({ dni,15 });

        auto it = tabla_punto.find(15);
        if (it == tabla_punto.end())
            tabla_punto.insert({ 15, 1 });
        else
            it->second++;
    }
    void quitar(std::string const& dni, int p) {
        auto itd = tabla_dni.find(dni);
        if (itd == tabla_dni.end())
            throw std::domain_error("Conductor inexistente");

        int tmp = itd->second - p;
        tabla_punto[itd->second]--;
        itd->second = tmp > 0 ? tmp : 0;

        if (tabla_punto.find(itd->second) == tabla_punto.end())
            tabla_punto.insert({ itd->second, 1 });
        else
            tabla_punto[itd->second]++;

    }
    int consultar(std::string const& dni) {
        auto it = tabla_dni.find(dni);
        if(it == tabla_dni.end())
            throw std::domain_error("Conductor inexistente");

        return it->second;
    }
    int cuantos_con_puntos(int p) {
        if (p > 15 || p < 0)
            throw std::domain_error("Puntos no validos");

        auto it = tabla_punto.find(p);
        if (it == tabla_punto.end())
            return 0;

        return it->second;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                std::cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                std::cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                std::cin >> dni;
                punt = dgt.consultar(dni);
                std::cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                std::cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                std::cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
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