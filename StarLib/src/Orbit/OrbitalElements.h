#ifndef ORBITALELEMENTS_H_
#define ORBITALELEMENTS_H_

#include <iostream>
#include <stdio.h>

namespace StarLib
{

struct OrbitalElements
{
    OrbitalElements()
    {
    }

    OrbitalElements(double q, double e, double i, double omega, double Omega,
                    double tp)
        : q(q), e(e), i(i), omega(omega), Omega(Omega), tp(tp)
    {
    }

    ~OrbitalElements()
    {
    }

    double q = 0., e = 0., i = 0., omega = 0., Omega = 0., tp = 0.;
//     double M = 0.;
// 	double a = 0;
};

} // namespace StarLib

#endif /* ORBITALELEMENTS_H_ */
