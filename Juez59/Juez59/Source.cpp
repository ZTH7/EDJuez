// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_map>

struct info
{
    std::string prof;
    int punto = 0;
};

class carnet_puntos {
    std::unordered_map<std::string, info> alumno;
    std::unordered_map<std::string, std::map<std::string, int>> profesor;
public:
    void alta(std::string const& alum, std::string const& profe) {
        int p = 0;
        auto ita = alumno.find(alum);
        if (ita == alumno.end())
            alumno.insert({ alum,{profe, 0} });
        else {
            profesor[ita->second.prof].erase(alum);
            ita->second.prof = profe;
            p = ita->second.punto;
        }

        auto itp = profesor.find(profe);
        if (itp == profesor.end())
            profesor.insert({ profe,{{alum, p}} });
        else {
            itp->second.insert({ alum, p });
        }
    }
    bool es_alumno(std::string const& alum, std::string const& profe) {
        auto ita = alumno.find(alum);
        if (ita == alumno.end())
            throw std::domain_error("El alumno " + alum + " no esta matriculado");
        else
            return ita->second.prof == profe;
    }
    int puntuacion(std::string const& alum) {
        auto ita = alumno.find(alum);
        if (ita == alumno.end())
            throw std::domain_error("El alumno " + alum + " no esta matriculado");
        
        return ita->second.punto;
    }
    void actualizar(std::string const& alum, int p) {
        auto ita = alumno.find(alum);
        if (ita == alumno.end())
            throw std::domain_error("El alumno " + alum + " no esta matriculado");
        
        ita->second.punto += p;
        profesor[ita->second.prof][alum] += p;
    }
    std::vector<std::string> examen(std::string const& profe, int p) {
        std::vector<std::string> v;
        for (auto& e : profesor[profe]) {
            if (e.second >= p)
                v.push_back(e.first);
        }
        return v;
    }
    void aprobar(std::string const& alum) {
        auto ita = alumno.find(alum);
        if (ita == alumno.end())
            throw std::domain_error("El alumno " + alum + " no esta matriculado");

        profesor[ita->second.prof].erase(alum);
        alumno.erase(ita);
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    std::string orden, alum, prof;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "alta") {
                std::cin >> alum >> prof;
                dgt.alta(alum, prof);
            }
            else if (orden == "es_alumno") {
                std::cin >> alum >> prof;
                bool res = dgt.es_alumno(alum, prof);
                std::cout << alum << (res ? "" : " no") << " es alumno de " << prof << '\n';
            }
            else if (orden == "puntuacion") {
                std::cin >> alum;
                punt = dgt.puntuacion(alum);
                std::cout << "Puntuacion de " << alum << ": " << punt << '\n';
            }
            else if (orden == "actualizar") {
                std::cin >> alum >> punt;
                dgt.actualizar(alum, punt);
            }
            else if (orden == "examen") {
                std::cin >> prof >> punt;
                auto alumnos = dgt.examen(prof, punt);
                std::cout << "Alumnos de " << prof << " a examen:" << '\n';
                for(std::string& nombre : alumnos)
                    std::cout << nombre << '\n';
            }
            else if (orden == "aprobar") {
                std::cin >> alum;
                dgt.aprobar(alum);
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR" << '\n';
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