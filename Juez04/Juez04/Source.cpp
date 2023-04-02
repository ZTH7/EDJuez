// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

#include "Header.h"


bool operator< (const std::pair<int, int>& f, const std::pair<int, int>& s) {
    return f.second < s.second;
}

std::istream& operator>> (std::istream& in, polinomio& poli) {
    std::pair<int, int> monomio;
    in >> monomio.first >> monomio.second;

    while (monomio.first != 0 || monomio.second != 0) {
        poli.insert(monomio);
        in >> monomio.first >> monomio.second;
    }
    return in;
}

int polinomio::find(const std::pair<int, int>& elem, int ini, int fin, bool& found) const {
    if (fin == ini) return ini;

    int m = (fin + ini) / 2;

    if (v[m] < elem) return find(elem, m + 1, fin, found);
    else if(elem < v[m]) return find(elem, ini, m, found);
    else {
        found = true;
        return m;
    }
}

void polinomio::insert(std::pair<int, int> elem) {
    bool found = false;
    int pos = find(elem, 0, v.size(), found);
    if (found) v[pos].first += elem.first;
    else v.insert(v.begin() + pos, elem);
}

int polinomio::calculate(int x) const {
    int mono_ante = 1;

    for (int i = 0; i < v[0].second; i++) mono_ante *= x;

    int res = v[0].first * mono_ante, eleva_ante = v[0].second;

    for (int i = 1; i < v.size(); i++) {
        int tmp = 1, diff = v[i].second - eleva_ante;
        eleva_ante = v[i].second;
        
        for (int j = 0; j < diff; j++) tmp *= x;

        mono_ante *= tmp;
        res += v[i].first * mono_ante;
    }

    return res;
}

// función que resuelve el problema
int resolver(polinomio poli, int x) {
    return poli.calculate(x);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num, x;
    polinomio poli;

    std::cin >> poli;
    if (!std::cin)
        return false;

    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::cin >> x;
        std::cout << resolver(poli, x) << " ";
    }

    // escribir sol
    std::cout << std::endl;

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