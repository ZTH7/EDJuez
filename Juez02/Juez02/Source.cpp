// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class Hora {
public:
    Hora() {
        Hora(0, 0, 0);
    }
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

    Hora operator+ (Hora const& other) const {
        Hora res;
        res.segundo = this->segundo + other.get_segundo();
        if (res.segundo >= NumSeg) {
            res.segundo %= NumSeg;
            res.minuto = this->minuto + other.get_minuto() + 1;
        }
        else res.minuto = this->minuto + other.get_minuto();
        if (res.minuto >= NumMin) {
            res.minuto %= NumMin;
            res.hora = this->hora + other.get_hora() + 1;
        }
        else res.hora = this->hora + other.get_hora();
        if (res.hora >= NumHora) throw std::invalid_argument("ERROR");
        return res;
    }

    bool operator< (Hora const& f) const {
        if (this->hora < f.hora) return true;
        else if (this->hora == f.hora && this->minuto < f.minuto) return true;
        else if (this->hora == f.hora && this->minuto == f.minuto && this->segundo < f.segundo) return true;
        else return false;
    }

    bool operator== (Hora const& f) const {
        return this->hora == f.hora && this->minuto == f.minuto && this->segundo == f.segundo;
    }

private:
    const int NumSeg = 60;
    const int NumMin = 60;
    const int NumHora = 24;
    int segundo;
    int minuto;
    int hora;
};

struct Cine {
    Hora fin;
    std::string Nombre;
};

bool operator< (Cine const& x, Cine const& y) {
    bool res = x.fin < y.fin || (x.fin == y.fin && x.Nombre < y.Nombre);
    return res;
}

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
void resolver(std::vector<Cine>& v, const std::vector<Hora>& ini, const std::vector<Hora>& dura, int num) {
    try {
        for (int i = 0; i < num; i++) {
            Hora tmp = ini[i] + dura[i];
            v[i].fin = tmp;
        }
        std::sort(v.begin(), v.end());
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;

    if (num == 0)
        return false;

    std::vector<Cine> v(num);
    std::vector<Hora> ini(num);
    std::vector<Hora> dura(num);

    for (int i = 0; i < num; i++) {
        std::cin >> ini[i] >> dura[i];
        getline(std::cin, v[i].Nombre);
    }
    
    resolver(v, ini, dura, num);

    for (Cine& cine : v) std::cout << cine.fin << cine.Nombre << std::endl;

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
