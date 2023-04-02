// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

#include "linked_list_ed.h"

template <typename T>
class linked_list_ed_plus : public linked_list_ed<T> {
    using Nodo = typename linked_list_ed<T>::Nodo;
public:
    void invertir() {
        Nodo* tmp = this->prim, * ante = nullptr;
        while (tmp != nullptr) {
            Nodo* sig = tmp->sig;
            tmp->sig = ante;
            ante = tmp;
            tmp = sig;
        }
        tmp = this->prim;
        this->prim = this->ult;
        this->ult = tmp;
    }

    void mostrar() {
        Nodo* tmp = this->prim;
        while (tmp != nullptr) {
            std::cout << tmp->elem << " ";
            tmp = tmp->sig;
        }
    }
};

// función que resuelve el problema
void resolver(linked_list_ed_plus<int> lista) {
    lista.invertir();
    lista.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int x;
    std::cin >> x;

    if (!std::cin)
        return false;

    linked_list_ed_plus<int> lista;

    while (x != 0) {
        lista.push_back(x);
        std::cin >> x;
    }

    resolver(lista);

    // escribir sol
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
