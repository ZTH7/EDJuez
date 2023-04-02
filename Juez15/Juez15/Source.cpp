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
    void particion(int pivote) {
        Nodo* aux = this->fantasma->sig,* media = this->fantasma;
        while (aux != this->fantasma) {
            if (aux->elem <= pivote) {
                Nodo* next = aux->sig;
                aux->ant->sig = aux->sig;
                aux->sig->ant = aux->ant;
                aux->ant = media;
                aux->sig = media->sig;
                media->sig = aux;
                aux->sig->ant = aux;
                media = aux;
                aux = next;
            }
            else aux = aux->sig;
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
void resolver(double_linked_list_ed_plus<int>& datos, int pivote) {
    datos.particion(pivote);
    datos.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, pivote, x;
    std::cin >> num >> pivote;

    if (!std::cin)
        return false;

    double_linked_list_ed_plus<int> datos;

    for (int i = 0; i < num; i++) {
        std::cin >> x;
        datos.push_back(x);
    }

    resolver(datos, pivote);

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