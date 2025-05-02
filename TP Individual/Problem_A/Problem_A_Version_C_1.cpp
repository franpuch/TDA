#include <iostream>
#include <vector>

using namespace std;

//* Resultado -> 'Limit Time on Test 6'.
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
- Estrucutra de Memoización -> Dos vectores, de tamaño 'm', de vectores de bools. Esos vectores tienen tamaño todas las tempertaturas 
                               posibles (2 * (n + m) + 1)), tienen 'True' en las temperaturas viables para esa celda y 'False' para 
                               el resto. Dos vectores porque sólo necesito mantener la información de la fila actual (la que estoy 
                               calculando) y la fila siguiente (para ir almacenando las temperaturas de las celdas que están debajo
                               de las actuales). 
- Podas Generales: propiedades del problema. 
    - Por los movimientos permitidos, los caminos siempre tiene longitud (n + m - 1). Si ese camino es impar, es imposible 
      llegar a la última celda con temperatura cero (pues siempre hay un 1 o -1 de más). 
    - Si la cantidad de 1 y/o -1 es mayor a la mitad de la longitud del camino, entonces es imposible llegar a la última
      celda con temperatura cero.
*/

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
                } else {
                    cantidad_menos_1++;
                }
            }
        }

        if ((n + m - 1) % 2 != 0) {
            cout << "NO" << endl;
            continue;
        }

        if ((cantidad_1 < ((n + m - 1) / 2)) || (cantidad_menos_1 < ((n + m - 1) / 2))) {
            cout << "NO" << endl;
            continue;
        }

        int desplazamiento = n + m;
        vector<vector<bool>> memo_fila_actual(m, vector<bool> (2 * desplazamiento + 1, false));
        vector<vector<bool>> memo_fila_siguiente(m, vector<bool> (2 * desplazamiento + 1, false));

        memo_fila_actual[0][matriz_entrada[0][0] + desplazamiento] = true;

        for (int i = 0; i < n; ++i) {
            fill(memo_fila_siguiente.begin(), memo_fila_siguiente.end(), vector<bool> (2 * desplazamiento + 1, false));
            for (int j = 0; j < m; ++j) {
                for (int s = -desplazamiento; s <= desplazamiento; s++) {
                    if (memo_fila_actual[j][s + desplazamiento]) {

                        if (i + 1 < n) {
                            int nueva_temp = s + matriz_entrada[i + 1][j];
                            if (abs(nueva_temp) <= (n - 1 - (i + 1)) + (m - 1 - j)) {
                                memo_fila_siguiente[j][nueva_temp + desplazamiento] = true;
                            }
                        }

                        if (j + 1 < m) {
                            int nueva_temp = s + matriz_entrada[i][j + 1];
                            if (abs(nueva_temp) <= (n - 1 - i) + (m - 1 - (j + 1))) {
                                memo_fila_actual[j + 1][nueva_temp + desplazamiento] = true;
                            }
                        }
                    }
                }
            }
            if (i < n - 1) {
                memo_fila_actual = memo_fila_siguiente;
            }
        }

        if (memo_fila_actual[m - 1][0 + desplazamiento]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}