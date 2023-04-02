// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


class Hora {
public:
    Hora() {}
    Hora(int h, int m, int s) {
        if (h < 0 || h >= NumHora) throw std::invalid_argument("ERROR");
        else if (m < 0 || m >= NumMin) throw std::invalid_argument("ERROR");
        else if (s < 0 || s >= NumSeg) throw std::invalid_argument("ERROR");
        else {
            hora = h;
            minuto = m;
            segundo = s;
        }
    }

    int get_hora() const { return hora; }
    int get_minuto() const { return minuto; }
    int get_segundo() const { return segundo; }


    Hora& operator= (Hora const& other) {
        if (this != &other) {
            this->hora = other.get_hora();
            this->minuto = other.get_minuto();
            this->segundo = other.get_segundo();
        }
        return *this;
    }


    bool operator< (Hora const& f) const {
        if (this->hora < f.hora) return true;
        else if (this->hora == f.hora && this->minuto < f.minuto) return true;
        else if (this->hora == f.hora && this->minuto == f.minuto && this->segundo < f.segundo) return true;
        else return false;
    }

private:
    const int NumSeg = 60;
    const int NumMin = 60;
    const int NumHora = 24;
    int segundo;
    int minuto;
    int hora;
};


std::istream& operator>> (std::istream& in, Hora& time) {
    int h = 0, m = 0, s = 0;
    char tmp;
    in >> h >> tmp >> m >> tmp >> s;
    time = Hora(h, m, s);
    return in;
}

std::ostream& operator<< (std::ostream& out, Hora& time) {
    out << std::setw(2) << std::setfill('0') << time.get_hora() << ":" << std::setw(2) << std::setfill('0') << time.get_minuto() << ":" << std::setw(2) << std::setfill('0') << time.get_segundo();
    return out;
}


// función que resuelve el problema
Hora* resolver(std::vector<Hora>& v, const Hora& time, int ini, int fin) {
    if(fin - ini <= 1) {
        if (!(v[ini] < time)) return &v[ini];
        else if (!(v[fin] < time)) return &v[fin];
        return nullptr;
    }
    
    int m = (ini + fin) / 2;

    if (v[m] < time) return resolver(v, time, m, fin);
    else return resolver(v, time, ini, m);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num_tren, num_query;
    Hora query;
    Hora* sol;
    std::cin >> num_tren >> num_query;

    if (num_tren == 0 && num_query == 0)
        return false;

    std::vector<Hora> v(num_tren);

    for (int i = 0; i < num_tren; i++) std::cin >> v[i];

    for (int i = 0; i < num_query; i++) {
        try {
            std::cin >> query;
            sol = resolver(v, query, 0, num_tren - 1);
            if (sol) std::cout << *sol << std::endl;
            else std::cout << "NO" << std::endl;
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "---" << std::endl;

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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
