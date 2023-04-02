// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "set_eda.h"

template <typename T>
class set_plus : public set<T> {
    using Link = typename set<T>::Link;

protected:
    std::pair<bool, T> lower_bound(T const& e, Link const& a, bool found, T const& res) const {
        if (a == nullptr) {
            return { found, res };
        }
        else if (set<T>::menor(a->elem, e)) {
            return lower_bound(e, a->dr, found, res);
        }
        else if (set<T>::menor(e, a->elem)) {
            return lower_bound(e, a->iz, true, a->elem);
        }
        else
            return { true, e };
    }

public:
    std::pair<bool, T> lower_bound(T const& e) const {
        return lower_bound(e, this->raiz, false, e);
    }

};

// función que resuelve el problema
void resolver(set_plus<int> const& set, std::vector<int> const& v) {
    for (int i = 0; i < v.size(); i++) {
        std::pair<bool, int> sol = set.lower_bound(v[i]);
        if (sol.first)
            std::cout << sol.second << std::endl;
        else
            std::cout << "NO HAY" << std::endl;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, x;
    std::cin >> num;

    if (num == 0)
        return false;

    set_plus<int> set;
    for (int i = 0; i < num; i++) {
        std::cin >> x;
        set.insert(x);
    }

    std::cin >> num;
    std::vector<int> v(num);
    for (int i = 0; i < num; i++) {
        std::cin >> v[i];
    }

    resolver(set, v);

    // escribir sol
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
