/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 6 de abril de 2024, 08:09 AM
 */

//PREGUNTA 1
//Nombre: Christian Carrillo Aburto 
//Codigo: 20202692
//Fecha: 6/04/2024
#include <iostream>
#include <vector>
using namespace std;

void ordenar(vector<int>& cortes) {
    int n = cortes.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (cortes[j] > cortes[j + 1]) {
                int temp = cortes[j];
                cortes[j] = cortes[j + 1];
                cortes[j + 1] = temp;
            }
        }
    }
}

void encontrarCombinaciones(const vector<int>& cortes, int pesoMaximo, int diferenciaMaxima, vector<int>& seleccionados, int index, int pesoActual, int& numPedidos) {
    if (pesoActual == pesoMaximo) {
        numPedidos++;
        cout << "Pedido " << numPedidos << ": ";
        for (int corte : seleccionados) {
            cout << corte << " ";
        }
        cout << endl;
        return;
    }

    for (int i = index; i < cortes.size(); i++) {
        if (i > index && cortes[i] == cortes[i - 1]) {
            continue;
        }

        if (pesoActual + cortes[i] <= pesoMaximo && (
            seleccionados.empty() || 
            (seleccionados.back() != cortes[i]) || 
            (abs(cortes[i] - seleccionados.back()) <= diferenciaMaxima))
        ) {
            seleccionados.push_back(cortes[i]);
            encontrarCombinaciones(cortes, pesoMaximo, diferenciaMaxima, seleccionados, i + 1, pesoActual + cortes[i], numPedidos);
            seleccionados.pop_back();
        }
    }
}

int main() {
    int P = 15;
    vector<int> t = {2, 8, 9, 6, 7, 6};
    int k = 4;

    ordenar(t);

    int numPedidos = 0;
    vector<int> seleccionados;
    encontrarCombinaciones(t, P, k, seleccionados, 0, 0, numPedidos);

    cout << "Número de pedidos que se puede atender de " << P << " kg: " << numPedidos << endl;

    return 0;
}




