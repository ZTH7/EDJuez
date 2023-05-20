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
#include <map>


using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

class Desierto {
public:

    Desierto() { }

    void anyadir_torre(const string& nombre, int x, int y) { // O(log n)
        if(torre.find(nombre) != torre.end())
            throw std::domain_error("Torre ya existente");

        auto itX = dirX.find(x);
        if (itX != dirX.end() && itX->second.find(y) != itX->second.end())
            throw std::domain_error("Posicion ocupada");

        torre[nombre] = { x , y };
        dirX[x][y] = nombre;
        dirY[y][x] = nombre;
    }

    void eliminar_torre(const string& nombre) { // O(log n)
        auto it = torre.find(nombre);
        if (it == torre.end())
            throw std::domain_error("Torre no existente");

        dirX[it->second.first].erase(it->second.second);
        dirY[it->second.second].erase(it->second.first);
        torre.erase(it);
    }

    pair<bool, string> torre_en_posicion(int x, int y) const { // O(log n)
        auto itX = dirX.find(x);
        if (itX != dirX.end()) {
            auto itY = itX->second.find(y);
            if (itY != itX->second.end())
                return { true, itY->second };
        }

        return{ false, "" };
    }

    pair<int, int> posicion(const string& nombre) const { // O(1)
        auto it = torre.find(nombre);
        if (it == torre.end())
            throw std::domain_error("Torre no existente");

        return it->second;
    }

    string torre_mas_cercana(const string& nombre, const Direccion& dir) const { // O(log n)
        auto it = torre.find(nombre);
        if (it == torre.end())
            throw std::domain_error("Torre no existente");

        int x = it->second.first, y = it->second.second;

        if (dir == Direccion::Norte) {
            auto itX = dirX.find(x);
            auto itY = itX->second.find(y);
            if (++itY != itX->second.end())
                return itY->second;
        }
        else if (dir == Direccion::Sur) {
            auto itX = dirX.find(x);
            auto itY = itX->second.find(y);
            if (itY != itX->second.begin())
                return (--itY)->second;
        }
        else if (dir == Direccion::Este) {
            auto itY = dirY.find(y);
            auto itX = itY->second.find(x);
            if (++itX != itY->second.end())
                return itX->second;
        }
        else if (dir == Direccion::Oeste) {
            auto itY = dirY.find(y);
            auto itX = itY->second.find(x);
            if (itX != itY->second.begin())
                return (--itX)->second;
        }

        throw std::domain_error("No hay torres en esa direccion");
    }


private:
    // Añade aquí los atributos que conforman la representación
    // interna del TAD
    //
    // También puedes añadir métodos auxiliares privados
    unordered_map<string, pair<int, int>> torre;
    map<int, map<int, string>> dirX;
    map<int, map<int, string>> dirY;
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
    // Implementar.
    Direccion dir;
    std::string orden, nombre;
    int x, y;
    std::cin >> orden;
    if (!std::cin)
        return false;

    Desierto dgt;

    while (orden != "FIN") {
        try {
            if (orden == "anyadir_torre") {
                std::cin >> nombre >> x >> y;
                dgt.anyadir_torre(nombre, x, y);
            }
            else if (orden == "eliminar_torre") {
                std::cin >> nombre;
                dgt.eliminar_torre(nombre);
            }
            else if (orden == "posicion") {
                std::cin >> nombre;
                auto res = dgt.posicion(nombre);
                std::cout << res.first << " " << res.second << '\n';
            }
            else if (orden == "torre_en_posicion") {
                std::cin >> x >> y;
                auto res = dgt.torre_en_posicion(x, y);
                if(res.first)
                    std::cout << "SI " << res.second << '\n';
                else
                    std::cout << "NO" << '\n';
            }
            else if (orden == "torre_mas_cercana") {
                std::cin >> nombre >> dir;
                auto res = dgt.torre_mas_cercana(nombre, dir);
                std::cout << res << '\n';
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << e.what() << '\n';
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

