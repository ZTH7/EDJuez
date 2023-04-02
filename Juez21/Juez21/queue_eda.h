//
//  queue_eda.h
//
//  Implementación del TAD pila con array dinámico
//
//  Estructuras de Datos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef queue_eda_h
#define queue_eda_h

#include <stdexcept>  // std::domain_error
#include <utility>    // std::move

template <class T>
class queue {
protected:
    static const int TAM_INICIAL = 10; // tamaño inicial del array dinámico

    // número de elementos en la pila
    int nelems;

    // tamaño del array
    int capacidad;

    int ini;

    // puntero al array que contiene los datos (redimensionable)
    T* array;

public:

    // constructor: pila vacía
    queue() : ini(0), nelems(0), capacidad(TAM_INICIAL), array(new T[capacidad]) {}

    // destructor
    ~queue() {
        libera();
    }

    // constructor por copia
    queue(queue<T> const& other) {
        copia(other);
    }

    // operador de asignación
    queue<T>& operator=(queue<T> const& other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }

    // apilar un elemento
    void push(T const& elem) {
        array[(ini + nelems) % capacidad] = elem;
        ++nelems;
        if (nelems == capacidad)
            amplia();
    }

    // consultar la cima
    T const& front() const {
        if (empty())
            throw std::domain_error("la pila vacia no tiene cima");
        return array[ini];
    }

    // desapilar el elemento en la cima
    void pop() {
        if (empty())
            throw std::domain_error("desapilando de la pila vacia");
        ini = (ini + 1) % capacidad;
        --nelems;
    }

    // consultar si la pila está vacía
    bool empty() const {
        return nelems == 0;
    }

    // consultar el tamaño de la pila
    int size() const {
        return nelems;
    }

protected:

    void libera() {
        delete[] array;
    }

    // this está sin inicializar
    void copia(queue const& other) {
        capacidad = other.nelems + TAM_INICIAL;
        nelems = other.nelems;
        ini = other.ini;
        array = new T[capacidad];
        for (int i = 0; i < nelems; ++i)
            array[i] = other.array[i];
    }

    void amplia() {
        T* viejo = array;
        array = new T[capacidad * 2];
        for (int i = 0; i < nelems; ++i)
            array[i] = std::move(viejo[(ini + i) % capacidad]);
        delete[] viejo;
        capacidad *= 2;
        ini = 0;
    }
};

#endif // queue_eda_h
