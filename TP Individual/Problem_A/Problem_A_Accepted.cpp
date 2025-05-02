#include <iostream>
#include <vector>
#include <tuple> 

//* Resultado -> 'Accepted'.
/*
- Estrategia General -> Para cada celda, me quedo con la mínima y la máxima temperatura posible (para esa celda).
                        Resulta que si el cero está en el intervalo [temp mínima , temp máxima], es posible llegar a esa
                        celda con temperatura cero (por algún camino que siga los movimientos permitidos).
- Movimientos permitidos -> moverse para la celda de la derecha y para la celda de abajo. 
- Transiciones -> voy recorriendo la matriz por filas. Dentro de cada fila, recorro las columnas de izquierda a derecha. 
- Estrategia de Memoización -> Para cada celda, almacenar sólo la temperatura mínima y máxima (de todas las posibles para 
                               esa celda). Para cada celda: una tupla (temp mínima , temp máxima).
- Estrucutra de Memoización -> Dos vectores, de tamaño 'm', de tuplas. En uno llevo las tuplas de temperatura de la fila 
                               que estoy calculando; en la otra, las tempeperaturas de la fila anterior. 
                               Para calcular las temperaturas de cada celda sólo necesito las temperaturas de la celda 
                               anterior y la de la celda de arriba. Sólo quiero el resultado de la última celda, así que 
                               no hace falta que almacene la info de todas las celdas.
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

        vector<tuple<int, int>> memo_fila_anterior(m, make_tuple(0, 0));
        vector<tuple<int, int>> memo_fila_actual(m, make_tuple(0, 0));

        memo_fila_actual[0] = make_tuple(matriz_entrada[0][0], matriz_entrada[0][0]);

        for (int i = 0; i < n; ++i) {
            fill(memo_fila_actual.begin(), memo_fila_actual.end(), make_tuple(0, 0));
            for (int j = 0; j < m; ++j) {

                int valor_matriz_entrada = matriz_entrada[i][j];

                if ((i == 0) && (j != 0)) {
                    memo_fila_actual[j] = make_tuple(get<0>(memo_fila_actual[j - 1]) + valor_matriz_entrada, get<1>(memo_fila_actual[j - 1]) + valor_matriz_entrada);
                }

                else if (j == 0) {
                    memo_fila_actual[j] = make_tuple(get<0>(memo_fila_anterior[j]) + valor_matriz_entrada, get<1>(memo_fila_anterior[j]) + valor_matriz_entrada);
                }

                else {
                    int min_1 = get<0>(memo_fila_anterior[j]) + valor_matriz_entrada;
                    int min_2 = get<0>(memo_fila_actual[j - 1]) + valor_matriz_entrada;

                    int max_1 = get<1>(memo_fila_anterior[j]) + valor_matriz_entrada;
                    int max_2 = get<1>(memo_fila_actual[j - 1]) + valor_matriz_entrada;

                    memo_fila_actual[j] = make_tuple((min(min_1, min_2)), (max(max_1, max_2)));
                }
            }
            if (i < n - 1) {
                memo_fila_anterior = memo_fila_actual;
            }
        }

        if ((get<0>(memo_fila_actual[m - 1]) <= 0) && (get<1>(memo_fila_actual[m - 1]) >= 0)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
} 
