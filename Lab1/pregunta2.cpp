/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 * PREGUNTA 2
 * Nombre: Christian Carrillo Aburto
 * Codigo: 20202692
 * Fecha: 6/04/24
 */
#include <iostream>
#include <string>

using namespace std;
void generarGrupos(int equipos[], int tamano, char* grupo, int index, int tamanoGrupo) {
    if (index == tamano) {
        cout << grupo << endl;
        return;
    }

    grupo[tamanoGrupo] = equipos[index] + '0';
    grupo[tamanoGrupo + 1] = ' ';

    generarGrupos(equipos, tamano, grupo, index + 1, tamanoGrupo + 2);

    grupo[tamanoGrupo] = '\0';

    generarGrupos(equipos, tamano, grupo, index + 1, tamanoGrupo);
}

int main() {
    int equipos[4] = {4, 5, 9, 2};
    int tamano = 4;

    char grupo[20]{};

    cout << "Las diferentes formas de agrupar a los equipos tácticos son:" << endl;
    generarGrupos(equipos, tamano, grupo, 0, 0);

    return 0;
}



