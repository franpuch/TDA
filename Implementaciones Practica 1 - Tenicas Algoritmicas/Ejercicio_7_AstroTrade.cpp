#include <iostream> 
#include <vector> 
#include <algorithm>
#define inf 1e9

using namespace std; 

//* Ejercicio 7 -> AstroTrade ///////////////////////////////////////////////////////////////////////////////////////////// 

// Declaración de variables y funciones.

vector<int> p;
vector<vector<int>> dp;
int astroTrade_PD(int j, int c);

// Definición de funciones. 

int main() {

    // Inputs.
    //! No ejecutar sin completar.
    p = {2, 3, 5, 6};
    int c = 0;
    
    // Inicializo la estructura de memoización -> '-inf' es mi indicador de "no calculado".
    dp = vector<vector<int>> (p.size(), vector<int> (p.size(), inf)); 

    // Pongo en marcha la maquinaria -> empiezo desde el día 0 con 'c = 0' asteroides.
    int resultado = astroTrade_PD(0, c);

    cout << "OutPut: " << endl;
    cout << resultado << endl;

    return 0;

}

int astroTrade_PD(int j, int c) {

    // Caso Base 1 -> Llegué al final de los días.
    if (j == p.size()) {
        return 0;
    }

    else {

        if (dp[j][c] != inf) {
            return dp[j][c];
        }

        int res;

        // Caso Base 2 -> Atajar llamados recursivos que ya no tienen solución válida.
        if ((c < 0) || (c > j)) {
            res = -inf;
        }

        // Pseudo Caso Base -> Si no tengo asteroides, no puedo vender.
        else if (c == 0 ) {
            int comprar = astroTrade_PD(j + 1, c + 1) - p[j];
            int no_operar = astroTrade_PD(j + 1, c);

            res = max(comprar, no_operar);
        }

        else {
            int comprar = astroTrade_PD(j + 1, c + 1) - p[j];
            int vender = astroTrade_PD(j + 1, c - 1) + p[j]; 
            int no_operar = astroTrade_PD(j + 1, c);

            res = max({comprar, vender, no_operar});
        }

        return dp[j][c] = res;
    }
}

//* Fin. 