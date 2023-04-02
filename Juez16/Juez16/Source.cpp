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
    void suma(const linked_list_ed_plus<int>& other) {
        Nodo* tmp = this->prim, * aux = other.prim, * ante = nullptr;
        while (tmp != nullptr) {
            tmp->elem += aux->elem;
            if (tmp->elem == 0) {
                Nodo* sig = tmp->sig;
                delete tmp;
                tmp = sig;

                if (sig == nullptr) this->ult = ante;

                if (ante == nullptr) this->prim = sig;
                else ante->sig = sig;
            }
            else {
                ante = tmp;
                tmp = tmp->sig;
            }
            aux = aux->sig;
        }
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
void resolver(linked_list_ed_plus<int>& lista, const linked_list_ed_plus<int>& other) {
    lista.suma(other);
    lista.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    if (num == -1)
        return false;

    int x;
    linked_list_ed_plus<int> lista, other;

    for (int i = 0; i < num; i++) {
        std::cin >> x;
        lista.push_back(x);
    }

    for (int i = 0; i < num; i++) {
        std::cin >> x;
        other.push_back(x);
    }

    resolver(lista, other);

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
