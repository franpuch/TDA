#include <iostream> 
#include <vector> 
#include <tuple> 
#define inf 1e9

using namespace std; 

//* Ejercicio 6 - Ítem b -> OptiPago ////////////////////////////////////////////////////////////////////////////////////// 

//* Implementación del Ítem b -> con BackTracking.

// Declaración de funciones.

tuple<int, int> min_tuplas(tuple<int, int> tupla_1, tuple<int, int> tupla_2);
tuple<int, int> optiPago_BT(vector<int> b, int i, int c);

// Definición de funciones.

int main() {

    // Definición de Inputs.
    //! No ejecutar sin completar.
    vector<int> b = {2, 3, 5, 10, 20};
    int c = 14;

    tuple<int, int> output = optiPago_BT(b, b.size() - 1, c);

    cout << "El menor exceso posible es: " << endl;
    cout << get<0>(output) << endl;

    cout << "Usando una (mínima) cantidad de billetes de: " << endl;
    cout << get<1>(output);

    /* Template para probar 'min_tuplas()':
    tuple<int, int> a = make_tuple();
    tuple<int, int> b = make_tuple();
    tuple<int, int> prueba = min_tuplas(a, b);
    cout << get<0>(prueba) << endl;
    cout << get<1>(prueba) << endl;
    */ 
    
    return 0;
}

tuple<int, int> optiPago_BT(vector<int> billetes, int i, int costo) {
    
    // Caso Base.
    if (costo <= 0) {
        tuple<int, int> res = make_tuple(abs(costo), 0);
        return res;
    }

    else if (i < 0) {
        tuple<int, int> res = make_tuple(inf, inf);
        return res;
    }

    // Paso Recursivo.
    else {
        tuple<int, int> contarBillete = make_tuple(get<0>(optiPago_BT(billetes, i - 1, costo - billetes[i])) , get<1>(optiPago_BT(billetes, i - 1, costo - billetes[i])) + 1);

        tuple<int, int> noContarBillete = make_tuple(get<0>(optiPago_BT(billetes, i - 1, costo)) , get<1>(optiPago_BT(billetes, i - 1, costo)));

        return min_tuplas(contarBillete, noContarBillete);
    }
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