#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/bernoulli.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include "../include/zeta_logic.hpp"

using namespace boost::multiprecision;
typedef number<mpfr_float_backend<155>> Real;

const Real PI = boost::math::constants::pi<Real>();
const Real DUE_PI = 2.0 * PI;
const int N_TERM_SIEGEL = 10;

Real funzione_theta(Real t, int n_stirling) {
    Real t2 = t / 2.0;
    Real res = t2 * log(t2 / PI) - t2 - (PI / 8.0);

    for (int k = 1; k <= n_stirling; ++k){
        int due_k = 2 * k;
        Real B2k = boost::math::bernoulli_b2n<Real>(k);

        Real coeff_frazione = (Real(1) - pow(Real(2), 1 - due_k)) * B2k;
        Real denominatore = Real(due_k) * (due_k - 1) * pow(t2, due_k - 1);

        if (k % 2 != 0) res += coeff_frazione / denominatore;
        else res -= coeff_frazione / denominatore;
    }
    return res;
}

Real calcola_sommatoria(Real t, Real theta, int N) {
    Real s = 0.0;
    for(int n = 1; n <= N; n++){
        s += cos(theta - t * log(Real(n))) / sqrt(Real(n));
    }

    return 2.0 * s;
}

Real C0(Real p) {
    return cos(DUE_PI * (p * p - p - Real(1)/16.0)) / cos(DUE_PI * p);
}

Real C1(Real p){
    Real u = 2 * p - 1;
    Real u2 = u * u;
    return (Real(1)/96) * (7 - 32*u2);
}

Real calcola_resto(Real t, int N, Real p) {

    Real segno = ((N - 1) % 2 == 0) ? Real(1) : Real(-1);
    Real x = t / DUE_PI;

    Real x1 = pow(x, Real(-0.25));
    Real x2 = pow(x, Real(-0.5));

    return segno * x1 * C0(p);
}



Real funzione_Z(Real t) {
    Real limite = sqrt(t / DUE_PI);
    int N = floor(limite.convert_to<double>());
    Real p = limite - N;

    Real theta = funzione_theta(t, N_TERM_SIEGEL);
    Real somma = calcola_sommatoria(t, theta, N);
    Real resto = calcola_resto(t, N, p);
    return somma + resto;
}

Real derivata(Real t){
    const Real h = Real("1e-120");
    return (funzione_Z(t+h) - funzione_Z(t-h)) / (2 * h);
}

Real newton(Real t0){
    const Real TOL = Real("1e-140");
    const int MAX_ITERAZIONI = 50;
    Real t = t0;
    for (int i = 0; i < MAX_ITERAZIONI; i++){
        Real f = funzione_Z(t);
        Real fd = derivata(t);
        if (abs(fd) < Real("1e-150")) break;
        Real tn1 = t - f / fd;
        if(abs(tn1 - t) < TOL) return tn1;
        t = tn1;
    }
    return t;
}

Real calcola_punto_gram(long long n){
    Real t = DUE_PI * (Real(n) + 1) / log(Real(n) + 2);
    if (t < 7) t = 7;

    for(int i=0; i<10; i++){
        Real th = funzione_theta(t, 5);
        Real d_th = 0.5 * log(t / DUE_PI);
        Real diff = th - (Real(n) * PI);
        t = t - diff / d_th;
    }
    return t;
}
