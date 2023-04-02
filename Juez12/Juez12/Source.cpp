// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "double_linked_list_ed.h"

template <typename T>
class double_linked_list_ed_plus : public double_linked_list_ed<T> {
    using Nodo = typename double_linked_list_ed_plus<T>::Nodo;
public:
    void cambia() {
        Nodo* actual = this->fantasma->sig;
        Nodo* next = this->fantasma->sig->sig;
        while (actual != this->fantasma && next != this->fantasma) {
            actual->ant->sig = next;
            next->sig->ant = actual;
            actual->sig = next->sig;
            next->ant = actual->ant;
            actual->ant = next;
            next->sig = actual;
            actual = actual->sig;
            next = actual->sig;
        }
    }

    void mostrar() const {
        Nodo* tmp = this->fantasma->sig;
        while (tmp != this->fantasma) {
            std::cout << tmp->elem << " ";
            tmp = tmp->sig;
        }
        std::cout << std::endl;
    }
};

// función que resuelve el problema
void resolver(double_linked_list_ed_plus<int>& datos) {
    datos.cambia();
    datos.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int x, y;
    std::cin >> x;

    if (x == 0)
        return false;

    double_linked_list_ed_plus<int> datos;

    for (int i = 0; i < x; i++) {
        std::cin >> y;
        datos.push_back(y);
    }

    resolver(datos);

    // escribir sol


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