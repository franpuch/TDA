# include <iostream> 
# include <string>
# include <iomanip>
using namespace std;

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

double hiloComunicados(int posicion_real, string mensaje, int index, int posicion_actual) {

    if (index == mensaje.length()) {
        if (posicion_actual == posicion_real) {
            return 1;
        } else {
            return 0;
        }
    }

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

int main() {
    
    string s1, s2;
    cin >> s1;
    cin >> s2;

    int posicion_verdadera = calcular_posicion_real(s1);
    double res = hiloComunicados(posicion_verdadera, s2, 0, 0);

    cout << fixed << setprecision(10) << res << endl;

    return 0;
} 