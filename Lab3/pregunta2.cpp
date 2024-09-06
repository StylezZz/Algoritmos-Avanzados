#include <iostream>
#include <algorithm>
#include <vector>

//Christian Carrillo Aburto
//20202692

using namespace std;


struct Paquete {
    int numero;
    int ganancia;
    int peso;
};

bool compararPorRelacion(const Paquete &a, const Paquete &b) {
    return (double)a.ganancia / a.peso > (double)b.ganancia / b.peso;
}

void llenarContenedor(vector<Paquete> &paquetes, int n, int capacidadContenedor) {
    sort(paquetes.begin(), paquetes.end(), compararPorRelacion);

    int pesoTotal = 0;
    int gananciaTotal = 0;

    for (int i = 0; i < n; i++) {
        if (pesoTotal + paquetes[i].peso <= capacidadContenedor) {
            pesoTotal += paquetes[i].peso;
            gananciaTotal += paquetes[i].ganancia;
        }
    }

    cout << "Peso sobrante en el contenedor: " << capacidadContenedor - pesoTotal << " Tn\n";
    cout << "Ganancia de la exportación: " << gananciaTotal << " en miles de dólares\n";
}

int main() {
    //Primer caso
    vector<Paquete> paquetes = {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,24,12},
        {5,8,2}
    };
   
    //Capacidad Primer Caso
    int capCaso1 = 16; 

    cout << "Caso 1: " << endl;
    llenarContenedor(paquetes, paquetes.size(), capCaso1);
    
    cout<<"----------------------------------------------------------------------"<<endl;
    
    //Caso 2
    vector<Paquete> paquetes2 = {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,14,12},
        {5,8,2},
        {6,5,5}
    };
    
    //Capacidad Segundo Caso
    int capCaso2= 20;
    cout << "Caso 2: " << endl;
    llenarContenedor(paquetes2,paquetes2.size(),capCaso2);
    
    return 0;
}
