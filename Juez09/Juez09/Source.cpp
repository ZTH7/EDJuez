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
    void eliminar() {
        Nodo* tmp = this->prim;
        while (tmp != nullptr) {
            if (tmp->sig != nullptr && tmp->elem == tmp->sig->elem) {
                Nodo* sig = tmp->sig;
                tmp->sig = tmp->sig->sig;
                delete sig;
            }
            else tmp = tmp->sig;
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
void resolver(linked_list_ed_plus<char> lista) {
    lista.eliminar();
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

    char x;
    linked_list_ed_plus<char> lista;

    for (int i = 0; i < num; i++) {
        std::cin >> x;
        lista.push_back(x);
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
