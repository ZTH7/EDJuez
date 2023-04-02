// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "deque_eda.h"
#include "list_eda.h"

template <class T>
class list_plus : public list<T> {
protected:
    using Nodo = typename list<T>::Nodo;

    template <class Apuntado>
    class reverse_iterator {
        // puntero al nodo actual del recorrido
        Nodo* act;
        // puntero al nodo fantasma (para saber cuándo estamos fuera)
        Nodo* fan;
    public:

        reverse_iterator() : act(nullptr), fan(nullptr) {}

        // para acceder al elemento apuntado
        Apuntado& elem() const {
            if (act == fan) throw std::out_of_range("fuera de la lista");
            return act->elem;
        }

        reverse_iterator& advance() { // ++ prefijo (recomendado)
            if (act == fan) throw std::out_of_range("fuera de la lista");
            act = act->ant;
            return *this;
        }

        bool operator==(reverse_iterator const& that) const {
            return act == that.act && fan == that.fan;
        }

        bool operator!=(reverse_iterator const& that) const {
            return !(*this == that);
        }


    private:
        // para que list pueda construir objetos del tipo iterador
        friend class list_plus;

        // constructora privada
        reverse_iterator(Nodo* ac, Nodo* fa) : act(ac), fan(fa) {}
    };

public:
    /*
     Iteradores que permiten recorrer la lista pero no cambiar sus elementos.
     */
    using const_iterator = reverse_iterator<T const>;

    // devuelven un iterador constante al principio de la lista
    const_iterator rbegin() const {
        return const_iterator(this->fantasma->ant, this->fantasma);
    }

    // devuelven un iterador constante al final del recorrido y fuera de este
    const_iterator rend() const {
        return const_iterator(this->fantasma, this->fantasma);
    }
};

// función que resuelve el problema
void resolver(list_plus<int> datos) {
    for (auto it = datos.rbegin(); it != datos.rend(); it.advance()) {
        std::cout << it.elem() << " ";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int x;
    list_plus<int> datos;

    std::cin >> x;
    while (x != 0) {
        datos.push_back(x);
        std::cin >> x;
    }

    resolver(datos);
    // escribir sol
    std::cout << std::endl;

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