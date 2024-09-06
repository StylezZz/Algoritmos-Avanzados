/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Christian Carrillo Aburto 
 * Codigo: 20202692
 *
 * Created on 20 de abril de 2024, 08:31 AM
 */

#include <iostream>
using namespace std;

int minimizarTiempos(int tiempos[], int tareas, int robots) {
    //Puse tamaño grande debido a que la impresión mostraba números sin sentido
    int dp[100][100];
    int tiempoTotal[100];
    
    tiempoTotal[0] = 0;
    for (int i = 1; i <= tareas; ++i) {
        tiempoTotal[i] = tiempoTotal[i-1] + tiempos[i-1];
    }

    // Caso base 
    for (int i = 0; i <= tareas; ++i) {
        dp[i][1] = tiempoTotal[i];
    }
    
    //DP
    for (int j = 2; j <= robots; ++j) {
        for (int i = 1; i <= tareas; ++i) {
            dp[i][j] = 9999; //Para minimizar
            for (int k = 0; k < i; ++k) {
                //Calcular el max tiempo entre tareas
                int costo = max(dp[k][j - 1], tiempoTotal[i] - tiempoTotal[k]);
                dp[i][j] = min(dp[i][j], costo);
            }
        }
    }

    // Imprimir la tabla dp
    cout << "Tabla de soluciones parciales:" << endl;
    for (int i = 0; i <= tareas; ++i) {
        for (int j = 0; j <= robots; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    //Retorna el tiempo máximo que se puede realizar dicho proceso
    return dp[tareas][robots];
}

int main() {
    int tiempos[] = {15, 30, 60, 45, 10};
    int tareas = 5; 
    int robots = 2; 
    
    //Caso 1
    cout << "El tiempo máximo que utilizarían "<<robots<< " robots sería "<< minimizarTiempos(tiempos, tareas, robots) << " min." << endl<<endl;
    
    robots=3;
    //Caso 2
    cout << "El tiempo máximo que utilizarían "<<robots<< " robots sería "<< minimizarTiempos(tiempos, tareas, robots) << " min." << endl<<endl;
    return 0;
}
