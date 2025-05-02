#include <iostream> 
#include <vector> 

using namespace std;

//* Ejercicio 3 -> MaxiSubconjunto //////////////////////////////////////////////////////////////////////////////////////// 

// Inputs -> //! Completar antes de ejecutar.
vector<vector<int>> matriz_entrada = {{0, 10, 10, 1}, 
                                      {10, 0, 5, 2},
                                      {10, 5, 0, 1},
                                      {1, 2, 1, 0}};

int k = 3; 

// Variables globales.
int n = matriz_entrada[0].size();
int ceros_permitidos = n - k;
vector<int> sol_parcial(n); 

int mejor_cuenta = 0;
vector<int> res;

// Declaración de funciones.
int sumatoria_enunciado(vector<vector<int>> matriz, vector<int> indices);  // Funciona bien.
void maxiSubconjunto(int posicionActual, int tamañoActual, int contador_ceros);  // Está en construcción.

// Definición de funciones.

int main() {

    maxiSubconjunto(0, 0, 0);

    cout << "Resultado: " << endl;
    for (int elemento : res) {
        cout << elemento << " ";
    }
    cout << endl;

    cout << "Resultado de la sumatoria: " << endl;
    cout << mejor_cuenta << endl;

    return 0;
}

void maxiSubconjunto(int posicionActual, int tamañoActual, int contador_ceros) {

    // Empiezo por la Poda por Optimalidad propuesta en mi ejercicio.
    vector<int> aux_poda(n);
    for (int index = 0; index < posicionActual; index ++) {
        aux_poda[index] = sol_parcial[index];
    } 
    for (int index = posicionActual; index < n; index ++) {
        aux_poda[index] = 1;
    }
    if(sumatoria_enunciado(matriz_entrada, sol_parcial) < mejor_cuenta) {
        return;
    }
    // Por cómo implementé esta poda, creo que me añade muchísima complejidad.
    // La dejo para que quede completo, pero no la dejaría jejeje.

    // Poda por Factibilidad 1 -> La Solución Parcial/Candidata se pasó de ceros.
    else if (contador_ceros > ceros_permitidos) {
        return;
    } 

    // Poda por Factibilidad 2 -> La Solución Parcial/Candidata se pasó de unos.
    else if (tamañoActual > k) {
        return;
    }

    // Caso Base -> Puse todos los unos que debía y llegué al final del array.
    else if ((tamañoActual == k) && (posicionActual == n)) {
        int cuenta = sumatoria_enunciado(matriz_entrada, sol_parcial);

        if (cuenta >= mejor_cuenta) {

            mejor_cuenta = cuenta;
            res.clear();
            
            for (int elemento : sol_parcial) {
                res.push_back(elemento);
            } 
        }

        // Esto imprime la solución parcial hasta ese entonces (lo usé antes para ir probando la función).
        /*
        cout << "Solución: " << endl;
        for (int elemento : sol_parcial) {
            cout << elemento << " ";
        }
        cout << endl;
        */

        return;
    } 

    // Paso Recursivo.
    else {
        sol_parcial[posicionActual] = 0;
        maxiSubconjunto(posicionActual + 1, tamañoActual, contador_ceros + 1);

        sol_parcial[posicionActual] = 1;
        maxiSubconjunto(posicionActual + 1, tamañoActual + 1, contador_ceros);
    }
} 

int sumatoria_enunciado(vector<vector<int>> matriz, vector<int> indices) {
    int res = 0; 

    for (int index_fila = 0; index_fila < n; index_fila ++ ) {
        if (indices[index_fila] != 0) {
            for (int index_columna = 0; index_columna < n; index_columna ++) {
                if (indices[index_columna] != 0) {
                    res += matriz[index_fila][index_columna];
                }
            }
        }
    }

    return res;

    /* OPCIÓN B -> Esta funciona con la lista de indices directos.
    for (int fila : indices) {
        for (int columna : indices) {
            res += matriz[fila - 1][columna - 1]; 
        }
    }
    */
} 

//* Fin. 