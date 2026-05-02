#ifndef ZETA_LOGIC_HPP
#define ZETA_LOGIC_HPP

#include <boost/multiprecision/mpfr.hpp>


typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<155>> Real;

Real funzione_theta(Real t, int n_stirling);
Real funzione_Z(Real t);
Real calcola_punto_gram(long long n);
Real newton(Real t0);

#endif
