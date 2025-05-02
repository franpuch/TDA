#include <iostream> 
#include <vector>

using namespace std;  

//* Ejercicio 1 -> SumaSubconjuntosBT ///////////////////////////////////////////////////////////////////////////////////// 

// Inputs -> //!Completar antes de ejecutar.
vector<int> c = {6, 12, 6};
int k = 12;

// Variables globales.
vector<int> sol_parcial(c.size()); 

// Declaración de funciones.

void subsetSum(vector<int> c, int i, int j);

// Definición de funciones.

int main() {

    subsetSum(c, c.size() - 1, k);

    return 0;
}

void subsetSum(vector<int> c, int i, int j) {

    if (j < 0) {
        return;
    }

    else if (i < 0) {
        if (j == 0) {
            cout << "Solución: " << endl;
            for (int elemento : sol_parcial) {
                cout << elemento << " ";
            }
            cout << endl;
        }
    }

    else {
        sol_parcial[i] = 0;
        subsetSum(c, i - 1, j); 

        sol_parcial[i] = 1;
        subsetSum(c, i - 1, j - c[i]);
    }
}

//* Fin. 