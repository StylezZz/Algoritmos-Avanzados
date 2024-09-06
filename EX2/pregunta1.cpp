#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <limits>
using namespace std;

struct Punto {
    int id;
    int x;
    int y;
};

double distanciaEntreDosPuntos(Punto a, Punto b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double tiempoRuta(double distancia, bool esViaRapida) {
    return distancia / (esViaRapida ? 80.0 : 40.0);
}

bool esSegmentoProhibido(int a, int b, const vector<pair<int, int>>& segmentosProhibidos) {
    for (const auto& seg : segmentosProhibidos) {
        if (seg.first == a && seg.second == b) {
            return true;
        }
    }
    return false;
}

bool esViaRapida(int a, int b, const vector<pair<int, int>>& segmentosRapidos) {
    for (const auto& seg : segmentosRapidos) {
        if (seg.first == a && seg.second == b) {
            return true;
        }
    }
    return false;
}

// Función de construcción del recorrido utilizando el algoritmo GRASP
void Construction(vector<Punto>& puntos, const vector<pair<int, int>>& segmentosProhibidos, const vector<pair<int, int>>& segmentosRapidos, vector<int>& recorrido) {
    int n = puntos.size();
    vector<bool> visitado(n, false);
    recorrido.clear();
    recorrido.push_back(0);  // Empezamos desde el punto inicial (almacén)
    visitado[0] = true;

    while (recorrido.size() < n) {
        int actual = recorrido.back();  // Último punto visitado
        vector<pair<int, double>> aux;  // Vector auxiliar para almacenar candidatos válidos

        // Construir lista de candidatos válidos
        for (int i = 0; i < n; ++i) {
            if (!visitado[i] && !esSegmentoProhibido(actual, i, segmentosProhibidos)) {
                double distancia = distanciaEntreDosPuntos(puntos[actual], puntos[i]);
                bool rapido = esViaRapida(actual, i, segmentosRapidos);
                double tiempo = tiempoRuta(distancia, rapido);
                pair<int, double> temp(i, tiempo);
                aux.push_back(temp);
            }
        }

        if (aux.empty()) {
            // Si no hay candidatos válidos, salir del bucle
            break;
        }

        // Ordenar candidatos por tiempo de ruta (menor primero)
        sort(aux.begin(), aux.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.second < b.second;
        });

        // 50% de los candidatos válidos
        int limiteRCL = max(1, int(aux.size() * 0.5));

        if (limiteRCL > 0) {
            // Seleccionar aleatoriamente un candidato de la RCL y añadirlo al recorrido
            int siguiente = aux[rand() % limiteRCL].first;
            recorrido.push_back(siguiente);
            visitado[siguiente] = true;
        }
    }
}

// Función para evaluar el tiempo total de un recorrido dado
double evaluarRecorrido(const vector<Punto>& puntos, const vector<int>& recorrido, const vector<pair<int, int>>& segmentosRapidos) {
    double tiempoTotal = 0.0;
    int n = recorrido.size();

    // Calcular el tiempo total sumando el tiempo de ruta entre cada par de puntos consecutivos en el recorrido
    for (int i = 0; i < n; ++i) {
        int a = recorrido[i];
        int b = recorrido[(i + 1) % n];  // Considerar conexión del último al primer punto
        double distancia = distanciaEntreDosPuntos(puntos[a], puntos[b]);
        bool rapido = esViaRapida(a, b, segmentosRapidos);
        tiempoTotal += tiempoRuta(distancia, rapido);
    }

    return tiempoTotal;
}

void grasp(vector<Punto>& puntos, const vector<pair<int, int>>& segmentosProhibidos, const vector<pair<int, int>>& segmentosRapidos, vector<int>& mejorRecorrido, int totalIteraciones) {
    double mejorTiempo = numeric_limits<double>::max();
    vector<int> recorrido;

    srand(time(0));
    for (int iter = 0; iter < totalIteraciones; ++iter) {
        Construction(puntos, segmentosProhibidos, segmentosRapidos, recorrido);
        double tiempoTotal = evaluarRecorrido(puntos, recorrido, segmentosRapidos);

        // Actualizar mejor recorrido encontrado
        if (tiempoTotal < mejorTiempo) {
            mejorTiempo = tiempoTotal;
            mejorRecorrido = recorrido;
        }
    }
}

void ImprimirRecorrido(const vector<int>& recorrido) {
    cout << "Recorrido encontrado: ";
    for (int p : recorrido) {
        cout << p << " ";
    }
    cout << endl;
}

int main() {
    vector<Punto> puntos = {
        {0, 5, 10}, {1, 40, 18}, {2, 100, 54}, {3, 60, 100},
        {4, 58, 78}, {5, 4, 54}, {6, 70, 45}, {7, 90, 90},
        {8, 93, 3}, {9, 30, 95}
    };

    vector<pair<int, int>> segmentosProhibidos = {
        {0, 1}, {2, 3}, {3, 2}, {5, 2}, {8, 2}, {8, 6}
    };

    vector<pair<int, int>> segmentosRapidos = {
        {0, 4}, {4, 0}, {2, 7}, {7, 2}, {2, 8}, {9, 3}
    };

    vector<int> mejorRecorrido;
    int totalIteraciones = 1000;

    grasp(puntos, segmentosProhibidos, segmentosRapidos, mejorRecorrido, totalIteraciones);

    ImprimirRecorrido(mejorRecorrido);
    cout << "Tiempo total: " << evaluarRecorrido(puntos, mejorRecorrido, segmentosRapidos) << " horas" << endl;

    return 0;
}
