/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 17 de mayo de 2024, 08:08 AM
 */

/*
 * Nombre: Christian Carrillo Aburto
 * Codigo: 20202692
 * Pregunta 2 (Baerin)
 * Casi terminada
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_N = 100; 
const int MAX_TARGET = 100; 

int contarDinares(int denominaciones[], int size, int monto) {
    //Matriz para almacenar sol parciales
    int dp[MAX_N + 1][MAX_TARGET + 1] = {0};

    // Iniciar primera columna de valores
    for (int i = 0; i <= size; ++i) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= monto; ++j) {
            if (denominaciones[i - 1] <= j) {
                /* 
                 Si la denominación actual es menor o igual al dato actual, se puede usar
                 Entonces, el número de formas de alcanzar el objetivo es la suma del número de formas sin usar esta denominación
                 y el número de formas usando esta denominación
                 */
                dp[i][j] = dp[i - 1][j] + dp[i][j - denominaciones[i - 1]];
            } else {
                /*
                 Si la denominación actual es mayor que el objetivo actual, no se puede usar
                 Entonces, el número de formas es igual al número de formas sin usar esta denominación
                 */
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Imprimir la matriz de sol parciales
    cout << "Matriz de soluciones parciales:" << endl;
    for (int i = 0; i <= size; ++i) {
        for (int j = 0; j <= monto; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[size][monto];
}

int main() {
    cout<<"Caso 1: "<<endl<<"======================================="<<endl;
    int denominaciones1[] = {2, 5, 10, 20};
    int monto1 = 13;
    int size1 = sizeof(denominaciones1) / sizeof(denominaciones1[0]);
    cout << "Respuesta: " << contarDinares(denominaciones1, size1, monto1) <<" forma "<< endl<<endl;
        
    cout<<"Caso 2: "<<endl<<"======================================="<<endl;
    int denominaciones2[] = {2, 5, 10, 20};
    int monto2 = 3;
    int size2 = sizeof(denominaciones2) / sizeof(denominaciones2[0]);
    cout << "Respuesta: " << contarDinares(denominaciones2, size2, monto2) <<" formas " <<endl<<endl;
            
    
    cout<<"Caso 3: "<<endl<<"======================================="<<endl;
    int denominaciones3[] = {1, 2, 10, 20};
    int monto3 = 7;
    int size3 = sizeof(denominaciones3) / sizeof(denominaciones3[0]);
    cout << "Respuesta: " << contarDinares(denominaciones3, size3, monto3) <<" formas ";

    return 0;
}