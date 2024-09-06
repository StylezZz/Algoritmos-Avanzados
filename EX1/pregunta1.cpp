/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 17 de mayo de 2024, 08:04 AM
 */
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//Nombre: Christian Carrillo Aburto
//Codigo: 20202692
//Pregunta 1 (Backtracking)

const int N = 5;  // Limite mapa
int mapa[N][N] = {
    {1, 2, 0, 1, 0},
    {3, 2, 3, 1, 1},
    {0, 1, 2, 0, 0},
    {3, 1, 1, 2, 3},
    {0, 1, 3, 1, 1}
};

int costoMin = INT_MAX;
vector<vector<int>> mejorCamino;
vector<vector<int>> camino(N, vector<int>(N, 0));

int posX[] = {1, -1, 0, 0}; // Movimientos en el eje X 
int posY[] = {0, 0, 1, -1}; // Movimientos en el eje Y 

bool esMovimientoValido(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && mapa[x][y] != 0);
}

void encontrarCostoMin(int x, int y, int costo) {
    // Si llegamos a la celda de destino, actualizamos el mínimo costo y la mejor ruta
    if (x == N-1 && y == N-1) {
        if (costo < costoMin) {
            costoMin = costo;
            mejorCamino = camino;
        }
        return;
    }
    
    // Exploramos todas las direcciones posibles
    for (int i = 0; i < N; i++) {
        int nuevoX = x + posX[i];
        int nuevoY = y + posY[i];
        
        if (esMovimientoValido(nuevoX, nuevoY) && camino[nuevoX][nuevoY] == 0) { // Movimiento válido y no visitado
            camino[nuevoX][nuevoY] = 1; // Marcamos la celda como visitada
            encontrarCostoMin(nuevoX, nuevoY, costo + mapa[nuevoX][nuevoY]);
            camino[nuevoX][nuevoY] = 0; // (backtracking)
        }
    }
}

int main() {
    camino[0][0] = 1; // Marcamos la celda de inicio
    encontrarCostoMin(0, 0, mapa[0][0]);

    cout << "El costo mínimo es: " << costoMin << endl;
    cout << "El mejor camino es:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mejorCamino[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}


