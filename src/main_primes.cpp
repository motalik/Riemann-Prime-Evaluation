#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "prime_logic.hpp"

using namespace std;

int main() {
    cout << std::fixed << std::setprecision(10);

    vector<Real> lista_zeri;
    ifstream file_zeri("data/zeri.dat");
    if (!file_zeri.is_open()) {
        cerr << "Errore: Impossibile aprire il file zeri.dat" << endl;
        return 1;
    }

    string riga;
    while(file_zeri >> riga){
        if (riga.empty()) continue;
        try {
            Real valore(riga);
            if (valore != 0) {
                lista_zeri.push_back(valore);
            }
        } catch (...) { continue; }
    }
    file_zeri.close();

    cout << "Caricati " << lista_zeri.size() << " zeri non banali." << endl;

    Real n_target;
    cout << "Inserisci numero fino a cui trovare il numero di primi: ";
    cin >> n_target;

    cout << "Calcolo in corso..." << endl;
    Real res = trova_primi(n_target, lista_zeri);

    cout << "Numero stimato di primi: " << res.str(0) << endl;

    return 0;
}
