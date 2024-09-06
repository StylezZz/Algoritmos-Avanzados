#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

//Christian Carrillo Aburto
//20202692

using namespace std;

struct Ciudad {
    char nombre;
    map<char, int> destinos;
};

int encontrarMinimo(map<char, int>& distancias, map<char, bool>& visitado) {
    int minimo = 99999;
    char minNodo = '\0';

    for (auto& par : distancias) {
        if (!visitado[par.first] && par.second < minimo) {
            minimo = par.second;
            minNodo = par.first;
        }
    }

    return minNodo;
}

int rutaMenor(map<char, Ciudad>& grafo, char inicio, char destino) {
    map<char, int> distancias;
    map<char, bool> visitado;
    for (auto& par : grafo) {
        distancias[par.first] = 99999;
        visitado[par.first] = false;
    }

    distancias[inicio] = 0;
    cout<<"Ruta:"<<endl;
    while (true) {
        char nodoActual = encontrarMinimo(distancias, visitado);
        cout<<nodoActual<<"-";
        if (nodoActual == '\0') break;
        cout<<distancias[nodoActual]<<endl;
        if (nodoActual == destino) return distancias[nodoActual];

        visitado[nodoActual] = true;

        for (auto& vecino : grafo[nodoActual].destinos) {
            if (!visitado[vecino.first]) {
                int nuevaDistancia = max(distancias[nodoActual], vecino.second);
                distancias[vecino.first] = min(distancias[vecino.first], nuevaDistancia);
            }
        }
    }

    return -1;
}

int main() { 
     map<char, Ciudad> ciudades = {
        {'A', {'A', {{'B', 4}, {'C', 5}, {'D', 6}}}},
        {'B', {'B', {{'E', 2}}}},
        {'C', {'C', {{'H', 3}}}},
        {'D', {'D', {{'F', 3}}}},
        {'E', {'E', {{'G', 10}}}},
        {'F', {'F', {{'G', 2}}}}
    };

    char inicio, destino;
    cout << "Ingrese el punto de partida: ";
    cin >> inicio;
    cout << "Ingrese el punto de llegada: ";
    cin >> destino;
    
    //Mi ruta es correcta pero el problema es que la suma de distancias no se aplica 
    //no se porque :(
    int suma=0;
    int tiempo = rutaMenor(ciudades, inicio, destino);

    if (tiempo == -1) {
        cout << "No se encontró una solución\n";
    } else {
        cout << "Tiempo de viaje " << tiempo << " min\n";
    }

    return 0;
}