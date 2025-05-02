#include <iostream> 
#include <vector> 

using namespace std;

//* Ejercicio 4 -> RutaMinima ///////////////////////////////////////////////////////////////////////////////////////////// 

// Inputs -> //! Completar antes de ejecutar.
vector<vector<int>> matriz_entrada = {{0, 1, 10, 10}, 
                                      {10, 0, 3, 15},
                                      {21, 17, 0, 2},
                                      {3, 22, 30, 0}};

// Variables globales.
int n = matriz_entrada[0].size();
vector<int> sol_parcial(n); 

vector<int> elementos_usados(n);

int mejor_resultado = 9999;
vector<int> res;

// Declaración de funciones.
int cuenta_enunciado(vector<vector<int>> matriz, vector<int> indices);
void ruta_minima(int index); 

// Definición de funciones. 

int main() { 

    ruta_minima(0);

    cout << "Resultado: " << endl;
    for (int elemento : res) {
        cout << elemento << " ";
    }
    cout << endl;

    cout << "Resultado de la sumatoria: " << endl;
    cout << mejor_resultado << endl;

    return 0;
}

void ruta_minima(int index) {

    // Caso Base.
    if (index == n) {
        int cuenta_actual = cuenta_enunciado(matriz_entrada, sol_parcial);

        if (cuenta_actual < mejor_resultado) {
            mejor_resultado = cuenta_actual;
            res.assign(sol_parcial.begin(), sol_parcial.end());

            /* Otra forma mas 'manual' de copiar. 
            res.clear();
            
            for (int elemento : sol_parcial) {
                res.push_back(elemento);
            }
            */
        } 
    }

    // Paso Recursivo.
    else {
        for (int i = 1; i <= n; i ++) {
            if (!elementos_usados[i - 1]) {   // Me fijo si aún no está usado.
                elementos_usados[i - 1] = 1;  // Le taggeo como usado.
                sol_parcial[index] = i;       // Lo uso.
                ruta_minima(index + 1);       // LLamo recursivamente.

                elementos_usados[i - 1] = 0;  // Lo desuso.
            }
        }
    }
}

int cuenta_enunciado(vector<vector<int>> matriz, vector<int> indices) {
    int res = matriz[indices[n - 1] - 1][indices[0] - 1]; 

    int sumatoria = 0;
    for (int indice = 0; indice < indices.size() - 1; indice ++) {
        sumatoria += matriz[indices[indice] - 1][indices[indice + 1] - 1];
    }

    return res + sumatoria;
}

//* Fin. 