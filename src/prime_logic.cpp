#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <omp.h>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/math/constants/constants.hpp>
#include "../include/prime_logic.hpp"

using namespace boost::multiprecision;

typedef number<mpfr_float_backend<155>> Real;

const Real EUL_MASC = Real("0.57721566490153286060651209008240243104215933593992");

Real espansione_asintotica(Real M, Real phi) {
    Real somma = 1.0;
    Real termine = 1.0;
    for(int k = 1; k <= 50; ++k) {
        Real r_k = Real(k) / M;
        termine *= r_k;
        somma += termine * cos(Real(k) * -phi);
        if (abs(termine) < Real("1e-120")) break;
    }
    Real exp_x = exp(M * cos(phi));
    Real arg = M * sin(phi) - phi;
    return (exp_x / M) * cos(arg) * somma;
}

Real calcola_Li(Real u) {
    if (u > 100.0) {
        Real somma = 1.0;
        Real fattoriale = 1.0;
        for(int k = 1; k <= 50; ++k) {
            fattoriale *= k;
            Real t = fattoriale / pow(u, k);
            somma += t;
            if (t < Real("1e-110")) break;
        }
        return (exp(u) / u) * somma;
    }
    Real risultato = 0.0;
    Real numeratore_u = u;
    Real fattoriale = 1.0;
    for(int k = 1; k <= 500; ++k) {
        Real termine = numeratore_u / (Real(k) * fattoriale);
        risultato += termine;
        if (abs(termine) < Real("1e-110")) break;
        numeratore_u *= u;
        fattoriale *= (k + 1);
    }
    return EUL_MASC + log(abs(u)) + risultato;
}

Real serie_Soldner(Real M, Real phi) {
    Real somma = 0.0;
    Real fattoriale = 1.0;
    Real potenza_M = M;
    for(int i = 1; i <= 500; ++i) {
        Real termine = (potenza_M / (Real(i) * fattoriale)) * cos(Real(i) * phi);
        somma += termine;
        if(abs(termine) < Real("1e-110")) break;
        potenza_M *= M;
        fattoriale *= (i + 1);
    }
    return somma;
}

Real contributo(Real t, const std::vector<Real>& zeri) {
    Real L = log(t);
    Real A = L * 0.5;
    Real somma_totale = 0.0;
    int n_zeri = static_cast<int>(zeri.size());

    #pragma omp parallel for reduction(+:somma_totale)
    for (int i = 0; i < n_zeri; ++i) {
        Real gamma = zeri[i];
        Real B = gamma * L;
        Real M = sqrt(A * A + B * B);
        Real phi = atan2(B, A);

        Real Li_rho;
        if (M < 80.0) {
            Li_rho = EUL_MASC + log(M) + serie_Soldner(M, phi);
        } else {
            Li_rho = espansione_asintotica(M, phi);
        }
        somma_totale += 2.0 * Li_rho;
    }
    return somma_totale;
}

Real calcola_Jx(Real x, const std::vector<Real>& zeri){
    if (x < 2.0) return 0.0;
    Real li_x = calcola_Li(log(x));
    Real somma_zeri = contributo(x, zeri);
    Real pezzo = log(Real(2.0));
    return li_x - somma_zeri - pezzo;
}

int mu(int n){
    if (n == 1) return 1;
    int count = 0;
    int temp_n = n;
    for(int i = 2; i * i <= temp_n; i++){
        if (temp_n % i == 0){
            count++;
            temp_n /= i;
            if (temp_n % i == 0) return 0;
        }
    }
    if (temp_n > 1) count++;
    return (count % 2 == 0) ? 1 : -1;
}

Real trova_primi(Real x, const std::vector<Real>& zeri){
    if (x < 2) return 0;
    Real res = 0;
    int n_max = floor(log2(static_cast<double>(x.convert_to<double>())));
    for (int n = 1; n <= n_max; ++n){
        int m = mu(n);
        if (m == 0) continue;
        Real rad_n = pow(x, 1.0 / n);
        Real j = calcola_Jx(rad_n, zeri);
        res += (Real(m) / Real(n)) * j;
    }
    return round(res);
}
