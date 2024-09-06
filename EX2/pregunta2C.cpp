#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 6;  
const int P = 200;  
const int GENERACIONES = 1000;
const double MUTACION = 0.8;
const int POBLACION_INICIAL = 10;

int mapa[N][N]={
    {4,  3, 8,10, 5,20}, 
    {6,  3, 4, 3, 8,10}, 
    {2,  1, 2, 4, 3,20},
    {10, 4, 9, 2, 1, 4},
    {10, 5,40, 1, 3,10},
    {2, 15,40,10, 1,10}};

struct Individuo {
    vector<bool> genes;
    int pesoTransportado;
};

vector<Individuo> inicializarPoblacion() {
    vector<Individuo> poblacion(POBLACION_INICIAL);
    for (int i = 0; i < POBLACION_INICIAL; ++i) {
        Individuo ind;
        ind.genes.resize((N - 1) * 2);
        
        fill(ind.genes.begin(), ind.genes.begin() + (N - 1), 1);
        fill(ind.genes.begin() + (N - 1), ind.genes.end(), 0);
        
        random_shuffle(ind.genes.begin(), ind.genes.end());

        ind.pesoTransportado = 0;  
        poblacion[i] = ind;
    }
    return poblacion;
}

int calcularPesoTransportado(const vector<bool>& genes) {
    int pesoTotal = 0;
    int pos_x = 0, pos_y = 0;  // Posición inicial (0, 0)

    for (int i = 0; i < genes.size(); ++i) {
        if (genes[i] == 0) {
            // Mover hacia la derecha
            pos_y++;
        } else {
            // Mover hacia abajo
            pos_x++;
        }
        
        // Verificar límites del almacén
        if (pos_x >= N || pos_y >= N) {
            break;  // Salir si el robot se sale de los límites
        }
        
        pesoTotal += mapa[pos_x][pos_y];
        if (pesoTotal > P) {
            return 0;  // Si se excede el peso máximo, retornar 0
        }
    }

    // Verificar si llegó a (N-1, N-1)
    if (pos_x == N-1 && pos_y == N-1) {
        return pesoTotal;
    } else {
        return 0;  // No llegó a la posición final
    }
}

void evaluarPoblacion(vector<Individuo>& poblacion) {
    for (Individuo& ind : poblacion) {
        ind.pesoTransportado = calcularPesoTransportado(ind.genes);
    }
}

Individuo seleccionarPadre(const vector<Individuo>& poblacion) {
    int totalFitness = 0;
    for (const Individuo& ind : poblacion) {
        totalFitness += ind.pesoTransportado;
    }

    if (totalFitness == 0) {
        return poblacion[rand() % POBLACION_INICIAL];
    }

    int punto = rand() % totalFitness;
    int acumulado = 0;
    for (const Individuo& ind : poblacion) {
        acumulado += ind.pesoTransportado;
        if (acumulado > punto) {
            return ind;
        }
    }
    return poblacion[0];
}

Individuo cruzamiento(const Individuo& padre1, const Individuo& padre2) {
    Individuo hijo;
    hijo.genes.resize((N - 1) * 2);

    int puntoCorte = rand() % ((N - 1) * 2);
    for (int i = 0; i < puntoCorte; ++i) {
        hijo.genes[i] = padre1.genes[i];
    }
    for (int i = puntoCorte; i < (N - 1) * 2; ++i) {
        hijo.genes[i] = padre2.genes[i];
    }

    return hijo;
}

void mutar(Individuo& individuo, double tasaMutacion) {
    for (int i = 0; i < individuo.genes.size(); ++i) {
        if ((double)rand() / RAND_MAX < tasaMutacion) {
            individuo.genes[i] = !individuo.genes[i];  
        }
    }
}

void controlarPoblacion(vector<Individuo>& poblacion) {
    sort(poblacion.begin(), poblacion.end(), [](const Individuo& a, const Individuo& b) {
        return a.pesoTransportado > b.pesoTransportado;
    });

    if (poblacion.size() > POBLACION_INICIAL) {
        poblacion.resize(POBLACION_INICIAL);
    }
}



int main() {
    srand(time(NULL));
    vector<Individuo> poblacion = inicializarPoblacion();

    for (int generacion = 0; generacion < GENERACIONES; ++generacion) {
        evaluarPoblacion(poblacion);

        vector<Individuo> nuevaPoblacion;
        while (nuevaPoblacion.size() < POBLACION_INICIAL) {
            Individuo padre1 = seleccionarPadre(poblacion);
            Individuo padre2 = seleccionarPadre(poblacion);
            Individuo hijo = cruzamiento(padre1, padre2);
            mutar(hijo, MUTACION);
            nuevaPoblacion.push_back(hijo);
        }

        poblacion = nuevaPoblacion;

        controlarPoblacion(poblacion);
    }

    evaluarPoblacion(poblacion);

    Individuo mejorIndividuo;
    int mejorPeso = 0;
    for (const Individuo& ind : poblacion) {
        if (ind.pesoTransportado > mejorPeso) {
            mejorPeso = ind.pesoTransportado;
            mejorIndividuo = ind;
        }
    }

    cout << "Peso máximo transportado: " << mejorPeso << " kg" << endl;
    return 0;
}
