# include <iostream> 
# include <string>
# include <iomanip>
using namespace std;

//* Funciones que resuelven el problema.

// Trabaja con: s1.
int calcular_posicion_real(string s) {
    int res = 0;

    for (char movimiento : s) {
        if (movimiento == '+') {
            res += 1;
        }
        else {
            res += (-1);
        }
    }

    return res;
}

// Trabaja con: la posición real calculada a partir de s1, y s2.
double hiloComunicados(int posicion_real, string mensaje, int index, int posicion_actual) {

    // Caso Base -> Llegué al final de la cadena.
    if (index == mensaje.length()) {
        if (posicion_actual == posicion_real) {
            return 1;
        } else {
            return 0;
        }
    }

    // Paso Recursivo.
    else {
        char instruccion = mensaje[index];

        if (instruccion == '+') {
            return hiloComunicados(posicion_real, mensaje, index + 1, posicion_actual + 1);
        }
        else if (instruccion == '-') {
            return hiloComunicados(posicion_real, mensaje, index + 1, posicion_actual - 1);
        }
        else {
            return (0.5) * hiloComunicados(posicion_real, mensaje, index + 1, posicion_actual + 1) + (0.5) * hiloComunicados(posicion_real, mensaje, index + 1, posicion_actual - 1); 
        }
    }

} 

//* Función 'Main' -> lee los inputs, ejecuta e imprime el resultado.
int main() {

    string s1, s2;

    // Leer la primera línea: la secuencia de instrucciones dictada (s1)
    cin >> s1;

    // Leer la segunda línea: la secuencia de instrucciones recibida (s2)
    cin >> s2;

    // Llamado de funciones e impresión del resultado.
    int posicion_verdadera = calcular_posicion_real(s1);
    float res = hiloComunicados(posicion_verdadera, s2, 0, 0);

    cout << fixed << setprecision(10) << res << endl;

    return 0;
}
