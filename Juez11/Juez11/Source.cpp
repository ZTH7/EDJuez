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
    void duplicar() {
        Nodo* tmp = this->fantasma->sig;
        Nodo* nuevo = this->fantasma->sig;
        while (tmp != this->fantasma) {
            nuevo = new Nodo(tmp->elem, tmp, tmp->sig);
            tmp->sig = nuevo;
            nuevo->sig->ant = nuevo;
            tmp = nuevo->sig;
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

    void mostrarinv() const {
        Nodo* tmp = this->fantasma->ant;
        while (tmp != this->fantasma) {
            std::cout << tmp->elem << " ";
            tmp = tmp->ant;
        }
        std::cout << std::endl;
    }
};

// función que resuelve el problema
void resolver(double_linked_list_ed_plus<int>& datos) {
    datos.duplicar();
    datos.mostrar();
    datos.mostrarinv();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int x;
    std::cin >> x;

    if (!std::cin)
        return false;

    double_linked_list_ed_plus<int> datos;

    while (x != 0) {
        datos.push_back(x);
        std::cin >> x;
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