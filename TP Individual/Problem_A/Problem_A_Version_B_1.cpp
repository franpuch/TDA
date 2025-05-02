#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

//* Resultado -> 'Limit Memory on Test 6'.
/*
- Estrategia General -> Para cada celda, voy almacenando todas las temperaturas posibles para esa celda. Al final, consulto
                        si en la última celda está el cero. 
- Movimientos permitidos -> moverse para la celda de la derecha y para la celda de abajo. 
- Transiciones -> voy recorriendo la matriz por filas. Dentro de cada fila, recorro las columnas de izquierda a derecha. 
- Estrategia de Memoización -> Para cada celda, almacenar sólo las temperaturas viables: aquellas generadas con las 
                               temperaturas de la celda anterior y la de arriba, y que tienen posibilidad de llegar a 
                               cero en la última celda. 
                               Esto lo hago viendo si el valor absoluto, de cada temperatura nueva, no supera la longitud 
                               del camino restante hasta la última celda. De esa forma, para cada celda, no almaceno temperaturas 
                               que no tienen posibilidad de llevarme al resultado.
- Estrucutra de Memoización -> Una Tabla de Hash, donde las claves son los index de la posición de la celda (en realidad, con 
                               esos valores estoy haciendo una cuentita) y los valores son conjuntos de ints. En estos conjuntos
                               almaceno las temperaturas viables de cada celda.
- Podas Generales: propiedades del problema. 
    - Por los movimientos permitidos, los caminos siempre tiene longitud (n + m - 1). Si ese camino es impar, es imposible 
      llegar a la última celda con temperatura cero (pues siempre hay un 1 o -1 de más). 
    - Si la cantidad de 1 y/o -1 es mayor a la mitad de la longitud del camino, entonces es imposible llegar a la última
      celda con temperatura cero.
*/

using namespace std;

int main() {
    int numero_test;
    cin >> numero_test;

    while (numero_test--) {
        int n, m;
        cin >> n >> m; 

        int cantidad_1 = 0;
        int cantidad_menos_1 = 0;

        vector<vector<int>> matriz_entrada(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> matriz_entrada[i][j];
                if (matriz_entrada[i][j] == 1) {
                    cantidad_1++;
                }
                else {
                    cantidad_menos_1++;
                }
            }
        }

        if ((n + m - 1) % 2 != 0) {
            cout << "NO" << endl;
            continue;
        }

        if ((cantidad_1 < ((n + m - 1)/2)) || (cantidad_menos_1 < ((n + m - 1)/2))) {
            cout << "NO" << endl;
            continue;
        }

        unordered_map<int, unordered_set<int>> memo_hash;

        int clave_inicial = 0 * m + 0;
        memo_hash[clave_inicial].insert(matriz_entrada[0][0]); 

        for (int i = 0 ; i < n; i++) {
            for (int j = 0 ; j < m ; j++) {
                int clave_celda_actual = i * m + j;

                for (int temp : memo_hash[clave_celda_actual]) {

                    if (i + 1 < n) {
                        int clave_proximo_abajo = (i + 1) * m + j;
                        int nueva_temp = temp + matriz_entrada[i + 1][j];
                        if (abs(nueva_temp) <= (n - 1 - (i + 1)) + (m - 1 - j)) {
                            memo_hash[clave_proximo_abajo].insert(nueva_temp);
                        }
                    } 

                    if (j + 1 < m) {
                        int clave_proximo_derecha = i * m + (j + 1);
                        int nueva_temp = temp + matriz_entrada[i][j + 1];
                        if (abs(nueva_temp) <= (n - 1 - i) + (m - 1 - (j + 1))) {
                            memo_hash[clave_proximo_derecha].insert(nueva_temp);
                        }
                    }       
                }
            }
        }

        int clave_ultima_aula = (n - 1) * m + (m - 1);
        if (memo_hash[clave_ultima_aula].count(0)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }

    }

    return 0;
} 