
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <stdexcept>

using namespace std;

class ColegioElectoral {
private:
    unordered_map<string, pair<int, string>> estados;
    unordered_map <string, pair<unordered_map<string, int>, map<int, string, greater<int>>>> votos;
    map<string, int> partidos;
public:
    ColegioElectoral() {}

    void nuevo_estado(const string& nombre, int num_compromisarios) {
        auto it = estados.find(nombre);
        if (it != estados.end())
            throw std::domain_error("Estado ya existente");

        estados[nombre] = { num_compromisarios,"" };
        votos[nombre] = { {}, {}};
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        auto it = estados.find(estado);
        if (it == estados.end())
            throw std::domain_error("Estado no encontrado");

        if (it->second.second != "") {
            int aux_num = partidos[it->second.second] - it->second.first;
            if (aux_num == 0)
                partidos.erase(it->second.second);
            else
                partidos[it->second.second] = aux_num;
        }

        int aux = (votos[estado].first[partido] += num_votos);

        votos[estado].second[aux] = partido;

        const string& tmp = votos[estado].second.begin()->second;
        partidos[tmp] += it->second.first;
        it->second.second = tmp;
    }

    string ganador_en(const string& estado) const {
        auto it = estados.find(estado);
        if (it == estados.end())
            throw std::domain_error("Estado no encontrado");

        return it->second.second;
    }

    vector<pair<string, int>> resultados() const {
        return vector<pair<string, int>>(partidos.begin(), partidos.end());
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    std::string orden, nombre, estado, partido;
    int num;
    std::cin >> orden;
    if (!std::cin)
        return false;

    ColegioElectoral colegioelec;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_estado") {
                cin >> nombre >> num;
                colegioelec.nuevo_estado(nombre, num);
            }
            else if (orden == "sumar_votos") {
                cin >> estado >> partido >> num;
                colegioelec.sumar_votos(estado, partido, num);
            }
            else if (orden == "ganador_en") {
                cin >> estado;
                auto res = colegioelec.ganador_en(estado);
                cout << "Ganador en Nevada: " << res << "\n";
            }
            else if (orden == "resultados") {
                auto res = colegioelec.resultados();
                for (auto& tmp : res) {
                    cout << tmp.first << " " << tmp.second << "\n";
                }
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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