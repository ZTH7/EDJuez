#pragma once

#include <iostream>
#include <iomanip>

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
