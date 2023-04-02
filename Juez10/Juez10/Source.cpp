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
    void insertar(linked_list_ed_plus<T>& lista) {
        Nodo* tmp = this->prim, * ante = nullptr;
        while (tmp != nullptr && lista.prim != nullptr) {
            if (lista.prim->elem < tmp->elem) {
                Nodo* lista_sig = lista.prim->sig;
                if (ante != nullptr) ante->sig = lista.prim;
                else this->prim = lista.prim;
                ante = lista.prim;
                lista.prim->sig = tmp;
                lista.prim = lista_sig;
            }
            else {
                ante = tmp;
                tmp = tmp->sig;
            }
        }

        if (lista.prim != nullptr) {
            if (this->ult != nullptr) this->ult->sig = lista.prim;
            else this->prim = lista.prim;
            this->ult = lista.ult;
            lista.prim = nullptr;
        }
        lista.ult = nullptr;
    }

    void mostrar() {
        Nodo* tmp = this->prim;
        while (tmp != nullptr) {
            std::cout << tmp->elem << " ";
            tmp = tmp->sig;
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    linked_list_ed_plus<int> lista, lista2;
    int x;
    std::cin >> x;
    while (x != 0) {
        lista.push_back(x);
        std::cin >> x;
    }

    std::cin >> x;
    while (x != 0) {
        lista2.push_back(x);
        std::cin >> x;
    }

    lista.insertar(lista2);

    // escribir sol
    lista.mostrar();
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


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
