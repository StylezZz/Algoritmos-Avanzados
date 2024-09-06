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
 * Created on 20 de abril de 2024, 08:11 AM
 */
#include <iostream>

using namespace std;

void imprimirArreglo(int dp[][10000], int cantBilletes, int vuelto) {
    cout << "Tabla de soluciones parciales:" << endl;
    for (int i = 0; i <= cantBilletes; i++) {
        for (int j = 0; j <= vuelto; j++) {
            if(j%10==0)cout<<endl;
            cout << dp[i][j] << " ";
        }
    }
    cout<<endl;
}

int puedeEntregarVuelto(int billetes[], int cantBilletes, int vuelto) {
    int dp[cantBilletes + 1][10000];
    dp[0][0] = 1;

    // Primera columna
    for (int i = 1; i <= cantBilletes; i++) {
        dp[i][0] = 1;
    }

    //Primera fila
    for (int j = 1; j <= vuelto; j++) {
        dp[0][j] = 0;
    }

    //DP
    for (int i = 1; i <= cantBilletes; i++) {
        for (int j = 1; j <= vuelto; j++) {
            if (billetes[i - 1] <= j) {
                //Si el billete actual es menor o igaul al vuelto requerido
                //No se usa el billete actual o Usar el billete actual
                dp[i][j] = dp[i - 1][j] || (dp[i - 1][j - billetes[i - 1]]);
            } else {
                //Si es mayor solo se puede usar el billete actual
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    imprimirArreglo(dp, cantBilletes, vuelto);

    return dp[cantBilletes][vuelto];
}

int main() {
    int billetes[] = {20, 20, 50, 50, 50, 100};
    int cantBilletes = sizeof(billetes) / sizeof(billetes[0]);
    int vuelto;

    // Caso 1: 
    vuelto = 270;
    cout << "Caso 1: Si tiene que entregar " << vuelto << " soles:" << endl;
    if (puedeEntregarVuelto(billetes, cantBilletes, vuelto)) {
        cout << "La solución será: Puede entregar el vuelto." << endl;
    } else {
        cout << "La solución será: No se puede entregar el vuelto." << endl;
    }
    
    for(int i=0;i<=70;i++)cout<<"=";
    cout<<endl;
    
    // Caso 2:
    vuelto = 230;
    cout << endl << "Caso 2: Si tiene que entregar " << vuelto << " soles:" << endl;
    if (puedeEntregarVuelto(billetes, cantBilletes, vuelto)) {
        cout << "La solución será: Puede entregar el vuelto." << endl;
    } else {
        cout << "La solución será: No se puede entregar el vuelto." << endl;
    }

    return 0;
}












