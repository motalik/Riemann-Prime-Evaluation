#include <iostream>
#include <iomanip>
#include <fstream>
#include "zeta_logic.hpp"
using namespace std;
int main() {
    cout << std::fixed << std::setprecision(150);
    std::ofstream fileZeri("data/zeri.dat");
    fileZeri << std::fixed << std::setprecision(150);

    int zeri_da_trovare;
    cout << "Quanti zeri vuoi trovare? ";
    cin >> zeri_da_trovare;

    int trovati = 0;
    Real t = 13.0;
    Real passo = 0.1;

    Real z_precedente = funzione_Z(t);

    cout << "Inizio ricerca..." << endl;

    while (trovati < zeri_da_trovare) {
        t += passo;
        Real z_attuale = funzione_Z(t);

        if ((z_precedente < 0 && z_attuale > 0) || (z_precedente > 0 && z_attuale < 0)) {

            Real zero = newton(t - passo / 2.0);

            trovati++;
            fileZeri << zero << endl;
            cout << "Trovato zero n. " << trovati << " a t = " << zero << endl;

            z_attuale = funzione_Z(t + 0.001);
            t += 0.001;
        }

        z_precedente = z_attuale;

    }

    fileZeri.close();
    cout << "Ricerca completata." << endl;
    return 0;
}
