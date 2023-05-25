// Problema interseccion de dos listas ordenadas

// IMPORTANTE

// Nombre y apellidos del alumno
// Usuario del juez de clase
// Usuario que has utilizado en esta prueba


#include <iostream>               
#include <fstream>               

#include "deque_eda.h"


// Explicación del algoritmo empleado






class InterseccionListas : public deque<int> {
    using Nodo = deque<int>::Nodo;
public:
    void print(std::ostream& o = std::cout) const {
        // rellenar
        Nodo* act = this->fantasma->sig;

        while (act != this->fantasma) {
            o << act->elem << " ";
            act = act->sig;
        }
    }

    void interseccion(int pos, int num) {
        // rellenar
        Nodo* act = this->fantasma->sig;
        for (int i = 0; i < pos; i++)
            act = act->sig;

        act->elem += num;
        Nodo* next = act->sig;
        act->ant->sig = act->sig;
        act->sig->ant = act->ant;
        while (next != this->fantasma && next->elem < act->elem)
            next = next->sig;

        act->sig = next;
        act->ant = next->ant;
        next->ant->sig = act;
        next->ant = act;
    }
};



/////////////////////////////////////////////////////////
// desde aquí NO se puede modificar nada

inline std::ostream& operator<<(std::ostream& o, InterseccionListas const& a) {
    a.print(o);
    return o;
}

InterseccionListas leerLista(int N) {
    InterseccionListas lista;
    int n;
    for (int i = 0; i < N; i++) {
        std::cin >> n;
        lista.push_back(n);
    }
    return lista;
}

bool resuelveCaso() {
    int N, pos, num;
    std::cin >> N >> pos >> num;
    InterseccionListas lista1 = leerLista(N);
    lista1.interseccion(pos, num);

    std::cout << lista1 << '\n';

    return true;
}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; std::cin >> numCasos; std::cin.ignore();
    for (int i = 0; i < numCasos; ++i) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
