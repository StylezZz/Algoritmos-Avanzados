#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <climits>

#define iteraciones 100000
#define alfa 0.3

using namespace std;

/*
 * Nombre: Christian Carrillo Aburto
 * Código: 20202692
 * Genera la primera solución, en la segunda se queda en 40IOP's 
 */

struct Tabla {
    int idTabla;
    int capacidad;
    int velocidad;
};

struct Disco {
    int idDisco;
    int capacidad;
    int velocidad;
    vector<int> tablas;  // Tablas asignadas al disco
};

bool comparaTablas(Tabla a, Tabla b) {
    return a.velocidad > b.velocidad;
}

bool comparaDiscos(Disco a, Disco b) {
    return a.velocidad > b.velocidad;
}

int evaluarGrasp(vector<Disco>& discos) {
    int minVel = INT_MAX;
    for (int i = 0; i < discos.size(); ++i) {
        if (discos[i].velocidad < minVel) {
            minVel = discos[i].velocidad;
        }
    }
    return minVel;
}

void funcionGrasp(vector<Tabla>& tablas, vector<Disco>& discos) {
    vector<Disco> bestDisco = discos;
    int mejorValor = 0;
    srand(time(0));
    
    for (int i = 0; i < iteraciones; i++) {
        //Ordenar aleatoriamente para tener una mejor aproximación al resultado
        random_shuffle(tablas.begin(), tablas.end());
        vector<Disco> auxDisco = discos;

        for (int j = 0; j < tablas.size(); ++j) {
            sort(auxDisco.begin(), auxDisco.end(), comparaDiscos);
            int beta = auxDisco[0].velocidad;
            int tauro = auxDisco.back().velocidad;
            int exp = beta - alfa * (beta - tauro);

            vector<Disco> candidatos;
            for (int k = 0; k < auxDisco.size(); ++k) {
                if (auxDisco[k].velocidad >= exp && auxDisco[k].capacidad >= tablas[j].capacidad) {
                    candidatos.push_back(auxDisco[k]);
                }
            }

            if (!candidatos.empty()) {
                int index = rand() % candidatos.size();
                for (int u = 0; u < auxDisco.size(); ++u) {
                    if (auxDisco[u].idDisco == candidatos[index].idDisco) {
                        auxDisco[u].velocidad -= tablas[j].velocidad;
                        auxDisco[u].capacidad -= tablas[j].capacidad;
                        auxDisco[u].tablas.push_back(tablas[j].idTabla);
                        break;
                    }
                }
            }
        }

        int actual = evaluarGrasp(auxDisco);
        if (actual > mejorValor) {
            mejorValor = actual;
            bestDisco = auxDisco;
        }
    }

    cout << "Mejor asignación encontrada: " << endl;
    for (int i = 0; i < bestDisco.size(); ++i) {
        cout << "Disco " << bestDisco[i].idDisco << ": velocidad " << bestDisco[i].velocidad << endl;
        cout << "Tablas asignadas: ";
        for (int tabla : bestDisco[i].tablas) {
            cout << tabla << " ";
        }
        cout << endl;
    }
    cout << "Velocidad mínima del grupo: " << mejorValor << endl;
}

int main(int argc, char** argv) {
    vector<Tabla> tablas = {
        {1, 20, 150}, {2, 10, 100}, {3, 15, 80},
        {4, 100, 50}, {5, 50, 120}, {6, 100, 10}
    };

    vector<Disco> discos = {
        {1, 800, 250}, {2, 750, 200}, {3, 850, 200}
    };
    
    funcionGrasp(tablas, discos);

    return 0;
}
