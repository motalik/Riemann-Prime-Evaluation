#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <fstream>
#include <string>
#include "prime_logic.hpp"

using namespace std;
int main() {
    cout << std::fixed << std::setprecision(512);
    vector<Real> lista_zeri;
    int n_primi;
    ifstream file_zeri("data/zeri.dat");
    if (!file_zeri.is_open()) {
        cerr << "Errore: Impossibile aprire il file zeri.dat!" << endl;
        return 1;
    }

    string riga;
    while(file_zeri >> riga){
        if (riga.empty()) continue;
        Real valore(riga);
        if (valore != 0){
          lista_zeri.push_back(valore);
        }

    }
    file_zeri.close();

    cout << "Caricati " << lista_zeri.size() << " zeri non banali" << endl;
    cout << "Inserisci numero fino a cui trovare il numero di primi: " << endl;
    cin >> n_primi;
    Real res = trova_primi(n_primi, lista_zeri);
    long long res1 = res.convert_to<long long>();
    cout << "numero di primi: " << res1 << endl;

    return 0;
}
