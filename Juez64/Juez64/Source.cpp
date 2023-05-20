/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste de las operaciones
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1:
   Componente 2:
 */


 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>


using namespace std;


class ElGrande {
public:

    ElGrande() { }

    void anyadir_jugador(string& jugador) {
        auto it = jugadores.find(jugador);
        if (it != jugadores.end())
            throw domain_error("Jugador existente");

        jugadores[jugador] = 0;
    }

    void colocar_caballero(string& jugador, string& region) {
        auto it = jugadores.find(jugador);
        if (it == jugadores.end())
            throw domain_error("Jugador no existente");

        int max = regiones[region].first[regiones[region].second];
        int punto = ++regiones[region].first[jugador];

        if (punto > max) {
            if (region_disputa.find(region) == region_disputa.end()) {
                if (punto != 1) jugadores[regiones[region].second]--;
            }
            else {
                region_disputa.erase(region);
            }
            jugadores[jugador]++;
            regiones[region].second = jugador;
        }
        else if (punto == max) {
            if (region_disputa.find(region) == region_disputa.end()) {
                jugadores[regiones[region].second]--;
                region_disputa.emplace(region);
            }
        }
    }

    int puntuacion(string& jugador) {
        auto it = jugadores.find(jugador);
        if (it == jugadores.end())
            throw domain_error("Jugador no existente");

        return jugadores[jugador];
    }

    vector<string> regiones_en_disputa() {
        return vector<string>(region_disputa.begin(), region_disputa.end());
    }

    void expulsar_caballeros(string& region) {
        auto it = regiones.find(region);
        if (it == regiones.end())
            throw domain_error("Region vacia");

        if (region_disputa.find(region) == region_disputa.end())
            jugadores[regiones[region].second]--;
        regiones.erase(region);
    }


private:
    set<string> region_disputa;
    unordered_map<string, int> jugadores;
    unordered_map<string, pair<unordered_map<string, int>, string>> regiones;
};


bool tratar_caso() {
    std::string orden, jugador, region;
    std::cin >> orden;
    if (!std::cin)
        return false;

    ElGrande dgt;

    while (orden != "FIN") {
        try {
            if (orden == "anyadir_jugador") {
                std::cin >> jugador;
                dgt.anyadir_jugador(jugador);
            }
            else if (orden == "colocar_caballero") {
                std::cin >> jugador >> region;
                dgt.colocar_caballero(jugador, region);
            }
            else if (orden == "puntuacion") {
                std::cin >> jugador;
                int res = dgt.puntuacion(jugador);
                std::cout << "Puntuacion de " << jugador << ": " << res << '\n';
            }
            else if (orden == "regiones_en_disputa") {
                auto res = dgt.regiones_en_disputa();
                std::cout << "Regiones en disputa:\n";
                for(string& str : res)
                    std::cout << str << '\n';
            }
            else if (orden == "expulsar_caballeros") {
                std::cin >> region;
                dgt.expulsar_caballeros(region);
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
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}

