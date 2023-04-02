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
    void interseccion(double_linked_list_ed_plus<int>& other) {
        Nodo* actual = this->fantasma->sig, * aux = other.fantasma->sig;
        while (actual != this->fantasma && aux != other.fantasma) {
            if (actual->elem < aux->elem) {
                Nodo* next = actual->sig;
                actual->ant->sig = next;
                next->ant = actual->ant;
                delete actual;
                actual = next;
            }
            else if (actual->elem > aux->elem) {
                Nodo* next = aux->sig;
                aux->ant->sig = next;
                next->ant = aux->ant;
                delete aux;
                aux = next;
            }
            else {
                Nodo* next = aux->sig;
                aux->ant->sig = next;
                next->ant = aux->ant;
                delete aux;
                aux = next;
                actual = actual->sig;
            }
        }

        while (actual != this->fantasma) {
            Nodo* next = actual->sig;
            actual->ant->sig = next;
            next->ant = actual->ant;
            delete actual;
            actual = next;
        }

        while (aux != other.fantasma) {
            Nodo* next = aux->sig;
            aux->ant->sig = next;
            next->ant = aux->ant;
            delete aux;
            aux = next;
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
void resolver(double_linked_list_ed_plus<int>& datos, double_linked_list_ed_plus<int>& other) {
    datos.interseccion(other);
    datos.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int x;
    double_linked_list_ed_plus<int> datos, other;

    std::cin >> x;
    while (x != 0) {
        datos.push_back(x);
        std::cin >> x;
    }

    std::cin >> x;
    while (x != 0) {
        other.push_back(x);
        std::cin >> x;
    }

    resolver(datos, other);
    // escribir sol

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