#include <iostream>
#include <vector>

//* Resultado -> 'Limit Memory on Test 6'.
/*
- Estrategia General -> Para cada celda, voy almacenando todas las temperaturas posibles para esa celda. Al final, consulto
                        si en la última celda está el cero. 
- Movimientos permitidos -> moverse para la celda de la derecha y para la celda de abajo. 
- Transiciones -> voy recorriendo la matriz por filas. Dentro de cada fila, recorro las columnas de izquierda a derecha. 
- Estrategia de Memoización -> Para cada celda, almacenar todas las temperaturas posibles (para esa celda).
- Estrucutra de Memoización -> Una matriz del mismo tamaño que la matriz de entrada, donde en cada posición voy a almacenar 
                               un vector de bools. Ese vector de bools tiene tamaño todas las temperaturas posibles (2 * (n + m) + 1),
                               y tiene 'True' en todas los índices que se corresponden a una temperatura alcanzable para esa celda. 
                               En las demás posiciones, tiene 'False'.
- Podas Generales: propiedades del problema. 
    - Por los movimientos permitidos, los caminos siempre tiene longitud (n + m - 1). Si ese camino es impar, es imposible 
      llegar a la última celda con temperatura cero (pues siempre hay un 1 o -1 de más). 
*/

using namespace std;

int main() {
    int numero_test;
    cin >> numero_test;

    while (numero_test--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> matriz_entrada(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> matriz_entrada[i][j];
            }
        }

        if ((n + m - 1) % 2 != 0) {
            cout << "NO" << endl;
            continue;
        }

        int valores_temp_diferentes = 2 * (n + m) + 1; 

        vector<vector<vector<bool>>> memo(n, vector<vector<bool>>(m, vector<bool>(valores_temp_diferentes, false)));

        int max_diferencia = n + m;

        memo[0][0][matriz_entrada[0][0] + max_diferencia] = true;

        for (int i = 0 ; i < n; i++) {
            for (int j = 0 ; j < m ; j++) {
                for (int temp = 0; temp < valores_temp_diferentes; temp++) {
                    if (memo[i][j][temp]) {

                        if (i + 1 < n) {
                            int temp_desplazada = temp + matriz_entrada[i + 1][j];
                            if (temp_desplazada >= 0 && temp_desplazada < valores_temp_diferentes) {
                                memo[i + 1][j][temp_desplazada] = true;
                            }
                        } 
    
                        if (j + 1 < m) {
                            int temp_desplazada = temp + matriz_entrada[i][j + 1];
                            if (temp_desplazada >= 0 && temp_desplazada < valores_temp_diferentes) {
                                memo[i][j + 1][temp_desplazada] = true;
                            }
                        }
                    }
                }
            }
        }

        if (memo[n - 1][m - 1][max_diferencia]) {
            cout << "YES" << endl;
        } 
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}