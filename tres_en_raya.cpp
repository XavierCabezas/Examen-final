#include <iostream>
#include <cstdlib>
using namespace std;

void actualizarPuntaje(int* ptrPuntaje){
    (*ptrPuntaje)++;
}

class TresEnRaya{
private:
    char tablero[9];
    string jugador1, jugador2;
    char sim;
public:
    TresEnRaya(string p1, string p2){
        jugador1 = p1;
        jugador2 = p2;
        reiniciar();
    }

    void reiniciar() {
        for (int i = 0; i < 9; i++){
            tablero[i] = '1' + i;
        }
        sim ='X';
    }
    void mostrarTablero(){
        cout << "\n";
        cout << tablero[0] << " | " << tablero[1] << " | " << tablero[2] << endl;
        cout << "--|---|--" << endl;
        cout << tablero[3] << " | " << tablero[4] << " | " << tablero[5] << endl;
        cout << "--|---|--" << endl;
        cout << tablero[6] << " | " << tablero[7] << " | " << tablero[8] << endl;
        cout << "\n";
    }
    bool colocarFicha(int posicion){
        if (posicion < 1 || posicion > 9){
            cout << "Error: posicion fuera de rango.\n";
            return false;
        }

        int indice = posicion - 1;

        if (tablero[indice] == 'X' || tablero[indice] == 'O'){
            cout << "Error: posicion ocupada. Intenta de nuevo.\n";
            return false;
        }

        tablero[indice] = sim;
        return true;
    }
    char verificarGanador(){
        int combinaciones[8][3]={
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; i++){
            int a = combinaciones[i][0];
            int b = combinaciones[i][1];
            int c = combinaciones[i][2];

            if (tablero[a] == tablero[b] && tablero[b] == tablero[c]){
                return tablero[a];
            }
        }

        return ' ';
    }
    bool tableroLleno(){
        for (int i = 0; i < 9; i++){
            if (tablero[i] != 'X' && tablero[i] != 'O'){
                return false;
            }
        }
        return true;
    }

    void cambiarTurno(){
        if (sim == 'X')
            sim = 'O';
        else
            sim = 'X';
    }
    char getsim(){
        return sim;
    }
    string getNombreJugadorActual(){
        if (sim == 'X')
            return jugador1;
        else
            return jugador2;
    }
};
int main(){
    srand(1);
    int opcion;
    int puntaje1 = 0, puntaje2 = 0;
    string jugador1, jugador2;

    do {
        cout << "\n=== TRES EN RAYA ===\n";
        cout << "1. Jugar\n";
        cout << "2. Ver puntajes\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        if (opcion == 1){
            cout << "Jugador 1: ";
            cin >> jugador1;
            cout << "Jugador 2: ";
            cin >> jugador2;
            TresEnRaya juego(jugador1, jugador2);

            int turnoAleatorio = rand() % 2;
            if (turnoAleatorio == 1) {
                cout << "\nComienza: " << jugador2 << " (aleatorio)\n";
                juego.cambiarTurno();
            } else {
                cout << "\nComienza: " << jugador1 << " (aleatorio)\n";
            }

            char ganador = ' ';
            int posicion;

            while (ganador == ' ' && !juego.tableroLleno()){
                juego.mostrarTablero();

        cout << juego.getNombreJugadorActual()
                     << " (" << juego.getsim()
                     << ") elige posicion (1-9): ";
               cin >> posicion;
                if (juego.colocarFicha(posicion)){
                    ganador = juego.verificarGanador();

            if (ganador == ' '){
                        juego.cambiarTurno();
                    }
                }
            }

            juego.mostrarTablero();
            if (ganador == 'X'){
                cout << jugador1 << " gana!\n";
                actualizarPuntaje(&puntaje1);
            } else if (ganador == 'O') {
                cout << jugador2 << " gana!\n";
                actualizarPuntaje(&puntaje2);
            } else{
                cout << "Empate!\n";
            }
            cout << "Puntajes: " << jugador1 << ": " << puntaje1
                 << " | " << jugador2 << ": " << puntaje2 << endl;
        }
        else if (opcion == 2){
            cout << "\nPuntaje jugador 1: " << puntaje1 << endl;
            cout << "Puntaje jugador 2: " << puntaje2 << endl;
        }
        else if (opcion == 3){
            cout << "Hasta luego!\n";
        }
        else {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);

    return 0;
}