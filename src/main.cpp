#include <iostream>
#include <iomanip>
#include <fstream>
#include "zeta_logic.hpp"

using namespace std;
int main() {

    cout << std::fixed << std::setprecision(512);
    ofstream outdata;
    int zeri_da_trovare;
    cout << "Inserisci zeri da trovare: " << endl;
    cin >> zeri_da_trovare;
    int trovati = 0;
    long long n_gram = -1;
    std::ofstream fileZeri("data/zeri.dat");
    fileZeri << std::fixed << std::setprecision(512);
    if (!outdata){
	    cerr << "Errore apertura file" << endl;
	    exit(1);
    }

    while(calcola_punto_gram(++n_gram) < 13);
    fileZeri << 14.134725141734693790457251983562470270784257115699243175685567460149 << endl;
    while (trovati < zeri_da_trovare){
	    Real g0 = calcola_punto_gram(n_gram);
	    Real g1 = calcola_punto_gram(n_gram + 1);
	    
	    Real z0 = funzione_Z(g0);
	    Real z1 = funzione_Z(g1);
	    
	    if ((z0 > 0 && z1 < 0) || (z0 < 0 && z1 > 0)){
		    Real stima = (g0 + g1) / 2.0;
		    Real zero = newton(stima);

		    trovati++;
		    fileZeri << zero << endl;
		    cout << "Zero: " << trovati << ": " << zero << endl;
	    }
	    n_gram++;
    }
    outdata.close();
    
    return 0;
}
