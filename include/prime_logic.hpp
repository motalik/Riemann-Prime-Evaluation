#ifndef PRIME_LOGIC_HPP
#define PRIME_LOGIC_HPP

#include <boost/multiprecision/mpfr.hpp>


typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<155>> Real;

// Real calcola_Li(Real t);
Real trova_primi(Real x, const std::vector<Real>& zeri);

#endif
