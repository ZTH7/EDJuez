
// Programa para probar la implementación de una cola

#include <iostream> 
#include <fstream> 
#include <string>


//
//  queue_eda.h
//
//  Implementación del TAD cola con dos pilas
//
//  Estructuras de Datos y Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2016-2018 Isabel
//

#ifndef queue_eda_h
#define queue_eda_h

#include <stdexcept>  // std::domain_error
#include <stack> 

template <class T>
class queue {
protected:

    std::stack<T> first, second;

public:

    // constructor: cola vacía
    queue() {}


    // añadir un elemento al final de la cola
    void push(T const& elem) {
        first.push(elem);
    }

    // consultar el primero de la cola
    T const& front() {
        if (first.empty() && second.empty())
            throw std::domain_error("La cola esta vacia.");

        if (!second.empty())
            return second.top();

        while (!first.empty()) {
            second.push(first.top());
            first.pop();
        }

        return second.top();
    }

    // eliminar el primero de la cola
    void pop() {
        if (first.empty() && second.empty())
            throw std::domain_error("La cola esta vacia.");

        if (!second.empty())
            return second.pop();

        while (!first.empty()) {
            second.push(first.top());
            first.pop();
        }

        return second.pop();
    }

    // consultar si la cola está vacía
    bool empty() const {
        return first.size() == 0 && second.size() == 0;
    }

    // consultar el tamaño de la cola
    size_t size() const {
        return first.size() + second.size();
    }


};

#endif // queue_eda_h


bool resuelveCaso() {
    std::string str;
    getline(std::cin, str);
    if (str == ".") return false;
    // lee los datos de entrada en la cola
    queue<char> cola;
    for (int i = 0; i < str.length(); ++i) {
        cola.push(str[i]);
    }
    // Rota los datos de la cola
    for (int i = 0; i < cola.size(); ++i) {
        cola.push(cola.front());
        cola.pop();
    }
    // Duplica los elementos de la cola
    int numElem = (int)cola.size();
    for (int i = 0; i < numElem; ++i) {
        cola.push(cola.front());
        cola.push(cola.front());
        cola.pop();
    }
    // Muestra los elementos de la cola y la deshace
    numElem = (int)cola.size();
    for (int i = 0; i < numElem; i += 2) {
        std::cout << cola.front();
        cola.pop(); cola.pop();
    }
    if (!cola.empty()) std::cout << "ERROR\n";
    std::cout << '\n';
    return true;
}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
