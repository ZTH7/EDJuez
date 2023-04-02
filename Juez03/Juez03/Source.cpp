// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

class Complejo {
public:
    Complejo() {
        Complejo(0, 0);
    }
    Complejo(float r, float i) {
        this->real = r;
        this->imag = i;
    }

    float get_real() const { return real; }
    float get_imag() const { return imag; }


    Complejo& operator= (Complejo const& other) {
        if (this != &other) {
            this->real = other.get_real();
            this->imag = other.get_imag();
        }
        return *this;
    }

    Complejo operator+ (Complejo const& other) const {
        Complejo res(0,0);
        res.real = this->real + other.real;
        res.imag = this->imag + other.imag;
        return res;
    }

    Complejo operator* (Complejo const& other) const {
        Complejo res;
        res.real = this->real * other.real - this->imag * other.imag;
        res.imag = this->imag * other.real + this->real * other.imag;
        return res;
    }

private:
    float real;
    float imag;
};

float mod(Complejo& num) {
    return sqrt(num.get_imag() * num.get_imag() + num.get_real() * num.get_real());
}

// función que resuelve el problema
bool resolver(Complejo number, int num) {
    Complejo res(0,0);
    for (int i = 0; i < num; i++) if (mod(res = res * res + number) > 2) return false;
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    float real, imag;
    int num;
    std::cin >> real >> imag >> num;
    Complejo number(real, imag);

    bool sol = resolver(number, num);

    // escribir sol
    if (sol) std::cout << "SI" << std::endl;
    else std::cout << "NO" << std::endl;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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