#include <iostream> 
#include <vector> 
#include <tuple> 
#define inf 1e9 

using namespace std; 

//* Ejercicio 6 - Ítem e -> OptiPago //////////////////////////////////////////////////////////////////////////////////////

// Declaración de funciones y variables globales.

vector<vector<tuple<int, int>>> dp;
tuple<int, int> optiPago_PD(vector<int> billetes, int i, int j);
tuple<int, int> min_tuplas(tuple<int, int> tupla_1, tuple<int, int> tupla_2);

// Definición de funciones.

int main() { 

    // Definición de Inputs.
    //! No ejecutar sin completar.
    vector<int> b = {2, 3, 5, 10, 20};
    int c = 14;

    // Inicialización de la estructura de memoización.
    int n = b.size();
    int m = c + 1;
    dp = vector<vector<tuple<int, int>>> (n, vector<tuple<int, int>> (m, make_tuple(inf, inf)));

    // Arranco la máquina.
    tuple<int, int> res = optiPago_PD(b, b.size() - 1, c);

    // Imprimo los resultados.
    cout << "El menor exceso que se puede obtener es: " << endl;
    cout << get<0>(res) << endl;
    cout << "Usando una cantidad minima de billetes: " << endl;
    cout << get<1>(res) << endl; 

    return 0;
}

tuple<int, int> optiPago_PD(vector<int> billetes, int i, int j) {

    // Casos Base.
    if (j <= 0) {
        return make_tuple(abs(j), 0);
    }

    if (i < 0) {
        return make_tuple(inf, inf);
    }

    // Transiciones. 
    if (get<0>(dp[i][j]) != inf) {
        return dp[i][j]; 
    }

    tuple<int, int> ponerBillete = make_tuple(get<0>(optiPago_PD(billetes, i - 1, j - billetes[i])) , 
                                              1 + (get<1>(optiPago_PD(billetes, i - 1, j - billetes[i]))));

    tuple<int, int> noPonerBillete = optiPago_PD(billetes, i - 1, j);

    return dp[i][j] = min_tuplas(ponerBillete, noPonerBillete);
}

tuple<int, int> min_tuplas(tuple<int, int> tupla_1, tuple<int, int> tupla_2) {

    // Comparar las primeras componentes.
    if (get<0>(tupla_1) > get<0>(tupla_2)) {
        return tupla_2;
    }
    else if (get<0>(tupla_1) < get<0>(tupla_2)) {
        return tupla_1;
    }

    // Si las primeras componentes son iguales, comparar las segundas componentes.
    if (get<1>(tupla_1) >= get<1>(tupla_2)) {
        return tupla_2;
    }
    else {
        return tupla_1;
    }
}

//* Fin. 