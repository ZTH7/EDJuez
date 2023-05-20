
#include <iostream>
#include <fstream>
#include <stack>

template <typename T>
class stack {
    std::stack<T> stk, aux;
public:
    stack(){}

    void pop() {
        if (!stk.empty()) { // Si la pila no es vacía
            if (stk.top() == aux.top()) // Si el elemento es el valor mínimo de la pila
                aux.pop();

            return stk.pop();
        }

        throw std::domain_error("ERROR: Pila vacia");
    }

    void push(T elem) {
        // Si el elemento que va a poner es el valor mínimo de la pila actual
        if (aux.empty() || elem <= aux.top())
            aux.push(elem);

        stk.push(elem);
    }

    T top() {
        if (!stk.empty())
            return stk.top();

        throw std::domain_error("ERROR: Pila vacia");
    }

    T minimo() {
        // El valor mínimo es la arriba de la pila auxiliar
        if (!aux.empty())
            return aux.top();

        throw std::domain_error("ERROR: Pila vacia");
    }
};

bool resuelveCaso() {
    int ops; std::cin >> ops;
    if (ops == 0) return false;
    char tipo; std::cin >> tipo;
    if (tipo == 'I') {
        stack<int> p;
        for (int i = 0; i < ops; ++i) {
            try {
                char x; int n;
                std::cin >> x;
                if (x == 'A') { std::cin >> n; p.push(n); }
                else if (x == 'D') p.pop();
                else if (x == 'C') std::cout << p.top() << '\n';
                else if (x == 'M') std::cout << p.minimo() << '\n';
            }
            catch (std::domain_error& e) {
                std::cout << e.what() << '\n';
            }
        }
    }
    else {
        stack<char> p;
        for (int i = 0; i < ops; ++i) {
            try {
                char x; char n;
                std::cin >> x;
                if (x == 'A') { std::cin >> n; p.push(n); }
                else if (x == 'D') p.pop();
                else if (x == 'C') std::cout << p.top() << '\n';
                else if (x == 'M') std::cout << p.minimo() << '\n';
            }
            catch (std::domain_error& e) {
                std::cout << e.what() << '\n';
            }
        }
    }
    std::cout << "---\n";
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


