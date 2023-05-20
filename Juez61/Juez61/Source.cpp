
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>
#include <stdexcept>
#include "fecha_h.h"

using namespace std;

class gestion_tienda {
private:
    unordered_map<string, queue<string>> espera;
    unordered_map<string, pair<int, map<fecha, int>>> almacen;
public:

    gestion_tienda() {}

    vector<string> adquirir(string cod, fecha f, int cant) { //O(n) lineal con respecto al numero de clientes en la cola de espera
        auto it = espera.find(cod);
        vector<string> v;
        if (it != espera.end()) { // Hay clientes en espera
            if (cant == it->second.size()) { // Quitamos todos los clientes de la lista
                while (!it->second.empty()) {
                    v.push_back(it->second.front());
                    it->second.pop();
                }
            }
            else if (cant > it->second.size()) { // Quitamos los clientes de la cola y ponemos los restantes productos en el alamcen
                int restantes = cant - it->second.size();
                while (!it->second.empty()) {
                    v.push_back(it->second.front());
                    it->second.pop();
                }
                almacen[cod].second[f] += restantes;
                almacen[cod].first += restantes;
            }
            else { // Quitamos los clientes que puedan ser servidos
                for (int i = 0; i < cant; ++i) {
                    v.push_back(it->second.front());
                    it->second.pop();
                }
            }
        }
        else {
            almacen[cod].second.emplace(f, cant);
            almacen[cod].first += cant;
        }

        return v;
    }

    pair<bool, fecha> vender(string cod, string nombre) {
        auto it = almacen.find(cod);
        fecha f;
        if (it != almacen.end() /*&& it->second.first > 0*/) { // Hay existencias
            it->second.second.begin()->second--;
            f = it->second.second.begin()->first;

            if (it->second.second.begin()->second == 0) {
                it->second.second.erase(it->second.second.begin()); // Borramos una determinada cantidad de productos
            }

            it->second.first--;

            if (it->second.first == 0) { // Borramos el producto
                almacen.erase(it);
            }

            return { true,  f };

        }
        else { // No hay existencias
            espera[cod].push(nombre);
            return { false, f };
        }
    }

    int cuantos(string cod) {
        auto it = almacen.find(cod);
        if (it != almacen.end()) {
            return almacen[cod].first; // CUIDADO AQUÍ SE VUELVE A CREAR
        }
        else {
            return 0;
        }
    }

    bool hay_esperando(string cod) {
        return !espera[cod].empty(); // CUIDADO AQUÍ SE VUELVE A CREAR, aunque aquí da igual ya que se pregunta si esta llena la cola o no
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    fecha f;
    std::string orden, cod, nombre;
    int cant;
    std::cin >> orden;
    if (!std::cin)
        return false;

    gestion_tienda gestion;

    while (orden != "FIN") {
        try {
            if (orden == "adquirir") {
                cin >> cod >> f >> cant;
                vector<string> v = gestion.adquirir(cod, f, cant);
                cout << "PRODUCTO ADQUIRIDO ";
                for (string s : v) {
                    cout << s << " ";
                }
            }
            else if (orden == "vender") {
                cin >> cod >> nombre;
                pair<bool, fecha> par = gestion.vender(cod, nombre);
                if (par.first) {
                    cout << "VENDIDO " << par.second;
                }
                else {
                    cout << "EN ESPERA";
                }
            }
            else if (orden == "cuantos") {
                cin >> cod;
                int valor = gestion.cuantos(cod);
                cout << valor;
            }
            else if (orden == "hay_esperando") {
                cin >> cod;
                bool hay = gestion.hay_esperando(cod);
                if (hay) {
                    cout << "SI";
                }
                else {
                    cout << "NO";
                }
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        cout << "\n";
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