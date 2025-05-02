#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

//* Resultado -> 'Limit Time on Test 5'.
/*
- Estrategia General -> Para cada celda, voy almacenando todas las temperaturas posibles para esa celda. Al final, consulto
                        si en la última celda está el cero. 
- Movimientos permitidos -> moverse para la celda de la derecha y para la celda de abajo. 
- Transiciones -> Calcular los valores de las diferentes celdas en modo BFS. 
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

        unordered_map<int, unordered_set<int>> memo_hash;
        queue<int> q;

        int max_diferencia = n + m;

        int clave_inicial = 0 * m + 0;
        memo_hash[clave_inicial].insert(matriz_entrada[0][0] + max_diferencia); 
        q.push(clave_inicial);

        while (!q.empty()) {
            int clave_celda_actual = q.front();
            q.pop();

            int r = clave_celda_actual / m;
            int c = clave_celda_actual % m;
            int pasos_restantes = (n - 1 - r) + (m - 1 - c);

            for (int temp : memo_hash[clave_celda_actual]) {

                if (abs(temp - max_diferencia) <= pasos_restantes) {

                    if (r + 1 < n) {
                        int clave_proximo_abajo = (r + 1) * m + c;
                        int nueva_temp = temp + matriz_entrada[r + 1][c];
                        if (memo_hash[clave_proximo_abajo].find(nueva_temp) == memo_hash[clave_proximo_abajo].end()) {
                            memo_hash[clave_proximo_abajo].insert(nueva_temp);
                            q.push(clave_proximo_abajo);
                        }
                    } 

                    if (c + 1 < m) {
                        int clave_proximo_derecha = r * m + (c + 1);
                        int nueva_temp = temp + matriz_entrada[r][c + 1];
                        if (memo_hash[clave_proximo_derecha].find(nueva_temp) == memo_hash[clave_proximo_derecha].end()) {
                            memo_hash[clave_proximo_derecha].insert(nueva_temp);
                            q.push(clave_proximo_derecha);
                        }
                    }
                }     
            }
        }

        int clave_ultima_aula = n * m - 1;
        if (memo_hash.count(clave_ultima_aula) && memo_hash[clave_ultima_aula].count(max_diferencia)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}