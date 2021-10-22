#include "Integrator.h"

namespace StarLib
{


static double FALSE = 0;
static double TRUE = 1;
static double ONE = 1.0;
static double ZERO = 0.0;
static double HALF = 0.5;
static double SR = 1.4;


void Integrator::set_state(const std::vector<Vec3> &pos,
						   const std::vector<Vec3> &vel,
						   const std::vector<double> &m)
{
	positions = pos;
	velocities = vel;
	masses = m;
}



double Integrator::integrate(double time_delta, double sequence_size, int precision)
{
    ASSERT(positions.size() == velocities.size(),
           "Initial vectors are of different size");
    ASSERT(positions.size() == num_bodies,
           "number of bodies does not match the size of positions");

    int nf; /* number of force calls  (out)       */

    int num_equations = num_bodies * 3;

    double c[21], d[21], r[21], b[7][num_equations], g[7][num_equations],
        e[7][num_equations], bd[7][num_equations], w[7], u[7], pw, dir, w1, ss,
        tp, s, t, t2, tval, q, q2, q3, q4, temp, gk, hv = 0.0;

    std::vector<Vec3> f1(num_bodies), fj(num_bodies), y(num_bodies), z(num_bodies),
        x, v;
    x = positions;
    v = velocities;


    int nw[] = {0, 0, 1, 3, 6, 10, 15, 21};
    int npq, nsf, nper, ncl, nes, n, k, l, la, lb, lc, ld, le, ncount, ns, m,
        ni, j, jd;

    /* These h values are the Gauss - Radau spacings, scaled to the range 0 to
       1, for integrating to order 15.   h[1] is always 0.0 . */

    double h[] = {0.0,
                  0.05626256053692215,
                  0.18024069173689236,
                  0.35262471711316964,
                  0.54715362633055538,
                  0.73421017721541053,
                  0.88532094683909577,
                  0.97752061356128750};


    /* The sum of these h-values should be 3.733333333333333333333 */

    nper = FALSE;
    nsf = FALSE;
    ncl = (nclass == 1);
    npq = (nclass < 2);

    /*    y'=f(y,t)...................ncl = TRUE,  nclass =  1, npq = TRUE
          y"=f(y,t)...................ncl = FALSE, nclass = -2, npq = TRUE
          y"=f(y',y,t)................ncl = FALSE, nclass =  2, npq = FALSE
          nsf is FALSE on starting sequence, otherwise TRUE,
          nper is TRUE only on the last sequence of the integration,
          nes is TRUE only if ll is negative. Then the sequence size is xl. */

    dir = (time_delta < ZERO) ? -ONE : ONE;
    nes = (precision < 0);
    sequence_size = fabs(sequence_size) * dir;
    pw = 1. / 9.;

    /* Evaluate the constants in vectors : w[],u[],c[],d[],r[] */

    int nn;
    for (n = 1; n < 8; ++n)
    {
        nn = n + 1;
        w[n - 1] = ONE / (ncl ? nn : nn + nn * nn);
        u[n - 1] = ONE / nn;
    }
    for (k = 0; k < num_equations; ++k)
    {
        int idx = (int)(k / 3.0);
        int idy = k % 3;
        if (ncl)
            v[idx][idy] = ZERO;
        for (l = 0; l < 7; ++l)
        {
            bd[l][k] = ZERO;
            b[l][k] = ZERO;
        }
    }
    w1 = (ncl) ? ONE : HALF;
    c[0] = -h[1];
    d[0] = h[1];
    r[0] = ONE / (h[2] - h[1]);

    la = 1;
    lc = 1;

    for (k = 3; k <= 7; ++k)
    {
        lb = la;
        la = lc + 1;
        lc = nw[k + 1 - 1];
        c[la - 1] = -h[k - 1] * c[lb - 1];
        c[lc - 1] = c[la - 1 - 1] - h[k - 1];
        d[la - 1] = h[2 - 1] * d[lb - 1];
        d[lc - 1] = -c[lc - 1];
        r[la - 1] = ONE / (h[k + 1 - 1] - h[2 - 1]);
        r[lc - 1] = ONE / (h[k + 1 - 1] - h[k - 1]);
        if (k > 3)
            for (l = 4; l <= k; ++l)
            {
                ld = la + l - 3;
                le = lb + l - 4;
                c[ld - 1] = c[le - 1] - h[k - 1] * c[le + 1 - 1];
                d[ld - 1] = d[le - 1] + h[l - 1 - 1] * d[le + 1 - 1];
                r[ld - 1] = ONE / (h[k + 1 - 1] - h[l - 1 - 1]);
            }
    }


    ss = pow(10.0, -1.0 * precision);


    /* The statements above are used only once in an integration to set up the
       constants. They use less than a second of execution time. Next set is a
       reasonable estimate to tp based on experience. Same sign as dir.
       An initial first sequence size can be set with xl even whith ll > zero.
     */

    tp = 0.1 * dir;
    if (sequence_size != ZERO)
        tp = sequence_size;
    if (nes)
        tp = sequence_size;
    if (tp / time_delta > HALF)
        tp = HALF * time_delta;
    ncount = 0;

    do
    { /* This is the starting point of every sequence */
        iteration++;
        if (!nsf)
        {           /* For starting sequence only ! */
            ns = 0; /* number of sequences. */
            nf = 0; /* number of force calls */
            ni = 6; /* number of iterations */
            tm = ZERO;

//             force(x, v, ZERO, f1);
			force_strategy->execute(x, v, ZERO, f1);

            ++nf;
        }
        /* First find new g-values from the predicted b-values,following eqs.
         * (7)   */

        for (k = 0; k < num_equations; ++k)
        {
            g[0][k] = b[0][k] + d[0] * b[1][k] + d[1] * b[2][k] +
                      d[3] * b[3][k] + d[6] * b[4][k] + d[10] * b[5][k] +
                      d[15] * b[6][k];
            g[1][k] = b[1][k] + d[2] * b[2][k] + d[4] * b[3][k] +
                      d[7] * b[4][k] + d[11] * b[5][k] + d[16] * b[6][k];
            g[2][k] = b[2][k] + d[5] * b[3][k] + d[8] * b[4][k] +
                      d[12] * b[5][k] + d[17] * b[6][k];
            g[3][k] =
                b[3][k] + d[9] * b[4][k] + d[13] * b[5][k] + d[18] * b[6][k];
            g[4][k] = b[4][k] + d[14] * b[5][k] + d[19] * b[6][k];
            g[5][k] = b[5][k] + d[20] * b[6][k];
            g[6][k] = b[6][k];
        }
        t = tp;
        t2 = (ncl) ? t : t * t;
        tval = fabs(t);

        /* You can output nf,ns,x[1],x[2],t,tm,tf to monitor the progress here
         */

        /***************************************************************************/

        // tu wstawiam np. kod wykrywający zbliżenie ...
		if (stop_strategy->should_stop(x, v, tm))
			break;

        /***************************************************************************/
        for (m = 0; m < ni;
             ++m) /* 6 iterations for first sequence and 2 thereafter */
            for (j = 1; j < 8;
                 ++j) /* loop for each substep within a sequence */
            {
                jd = j - 1;
                s = h[j];
                q = (ncl) ? ONE : s;

                /* Here y is used for the value of y at substep n.  We use
                 * eq.(9).          */

                for (k = 0; k < num_equations; ++k)
                {
                    int idx = (int)(k / 3.0);
                    int idy = k % 3;
                    y[idx][idy] =
                        x[idx][idy] +
                        q * (t * v[idx][idy] +
                             t2 * s *
                                 (f1[idx][idy] * w1 +
                                  s * (w[0] * b[0][k] +
                                       s * (w[1] * b[1][k] +
                                            s * (w[2] * b[2][k] +
                                                 s * (w[3] * b[3][k] +
                                                      s * (w[4] * b[4][k] +
                                                           s * (w[5] * b[5][k] +
                                                                s * w[6] *
                                                                    b[6]
                                                                     [k]))))))));

                    /* Next are calculated the velocity predictors if needed for
                       general class II. Here z is used as the value of y' at
                       substep n.(Eq.10).        */

                    if (npq)
                        continue;
                    z[idx][idy] =
                        v[idx][idy] +
                        s * t *
                            (f1[idx][idy] +
                             s * (u[0] * b[0][k] +
                                  s * (u[1] * b[1][k] +
                                       s * (u[2] * b[2][k] +
                                            s * (u[3] * b[3][k] +
                                                 s * (u[4] * b[4][k] +
                                                      s * (u[5] * b[5][k] +
                                                           s * u[6] *
                                                               b[6][k])))))));
                }

//                 force(y, z, tm + s * t, fj);
				force_strategy->execute(y, z, tm + s * t, fj);


                ++nf; /* find forces at each substep */

                /* Find g-value for the force fj found at the current substep.
                 * Eq. (4)     */

                for (k = 0; k < num_equations; ++k)
                {
                    int idx = (int)(k / 3.0);
                    int idy = k % 3;

                    temp = g[jd][k];
                    gk = (fj[idx][idy] - f1[idx][idy]) / s;
                    switch (j)
                    {
                    case 1:
                        g[0][k] = gk;
                        break;
                    case 2:
                        g[1][k] = (gk - g[0][k]) * r[0];
                        break;
                    case 3:
                        g[2][k] = ((gk - g[0][k]) * r[1] - g[1][k]) * r[2];
                        break;
                    case 4:
                        g[3][k] = (((gk - g[0][k]) * r[3] - g[1][k]) * r[4] -
                                   g[2][k]) *
                                  r[5];
                        break;
                    case 5:
                        g[4][k] = ((((gk - g[0][k]) * r[6] - g[1][k]) * r[7] -
                                    g[2][k]) *
                                       r[8] -
                                   g[3][k]) *
                                  r[9];
                        break;
                    case 6:
                        g[5][k] =
                            (((((gk - g[0][k]) * r[10] - g[1][k]) * r[11] -
                               g[2][k]) *
                                  r[12] -
                              g[3][k]) *
                                 r[13] -
                             g[4][k]) *
                            r[14];
                        break;
                    case 7:
                        g[6][k] =
                            ((((((gk - g[0][k]) * r[15] - g[1][k]) * r[16] -
                                g[2][k]) *
                                   r[17] -
                               g[3][k]) *
                                  r[18] -
                              g[4][k]) *
                                 r[19] -
                             g[5][k]) *
                            r[20];
                        break;
                    }

                    /* Upgrade all b-values */

                    temp = g[jd][k] - temp;
                    b[jd][k] += temp;

                    /* Temp is now the improvement on g[jd][k] over its former
                       value. Now we upgrade the b-value using this difference
                       in the one term. Eq.(5).       */

                    switch (j)
                    {
                    case 1:
                        break;
                    case 2:
                        b[0][k] += c[0] * temp;
                        break;
                    case 3:
                        b[0][k] += c[1] * temp;
                        b[1][k] += c[2] * temp;
                        break;
                    case 4:
                        b[0][k] += c[3] * temp;
                        b[1][k] += c[4] * temp;
                        b[2][k] += c[5] * temp;
                        break;
                    case 5:
                        b[0][k] += c[6] * temp;
                        b[1][k] += c[7] * temp;
                        b[2][k] += c[8] * temp;
                        b[3][k] += c[9] * temp;
                        break;
                    case 6:
                        b[0][k] += c[10] * temp;
                        b[1][k] += c[11] * temp;
                        b[2][k] += c[12] * temp;
                        b[3][k] += c[13] * temp;
                        b[4][k] += c[14] * temp;
                        break;
                    case 7:
                        b[0][k] += c[15] * temp;
                        b[1][k] += c[16] * temp;
                        b[2][k] += c[17] * temp;
                        b[3][k] += c[18] * temp;
                        b[4][k] += c[19] * temp;
                        b[5][k] += c[20] * temp;
                        break;
                    }
                }
            }
        /* Integration of sequence is over. Next is sequence size control. */

        if (!nes)
        {
            hv = ZERO;
            for (k = 0; k < num_equations; ++k)
            {
                double aux;
                if ((aux = fabs(b[6][k])) > hv)
                    hv = aux;
            }
            hv = hv * w[6] / pow(tval, 7.0);
        }
        if (!nsf)
        {
            if (!nes)
            {
                tp = pow(ss / hv, pw) * dir;
                if (tp / t <= ONE)
                {
                    tp *= 0.8;
                    ++ncount;
                    if (ncount > 10)
                    {
                        //                         return (tm);
                        break;
                    }
                    continue;
                    /* Restart with 0.8*t if new tp is smaller than original t
                     * on 1-st sequence */
                }
            }
            else
                tp = sequence_size;
            nsf = TRUE;
        }

        /* This loop finds new x and v values at the end of the sequence.
         * Eqs.11,12 */

        for (k = 0; k < num_equations; ++k)
        {
            int idx = (int)(k / 3.0);
            int idy = k % 3;
            x[idx][idy] = x[idx][idy] + v[idx][idy] * t +
                          t2 * (f1[idx][idy] * w1 +
                                (b[0][k] * w[0] +
                                 (b[1][k] * w[1] +
                                  (b[2][k] * w[2] +
                                   (b[3][k] * w[3] +
                                    (b[4][k] * w[4] +
                                     (b[5][k] * w[5] + (b[6][k] * w[6]))))))));
            if (!ncl)
                v[idx][idy] =
                    v[idx][idy] +
                    t * (f1[idx][idy] +
                         (b[0][k] * u[0] +
                          (b[1][k] * u[1] +
                           (b[2][k] * u[2] +
                            (b[3][k] * u[3] +
                             (b[4][k] * u[4] +
                              (b[5][k] * u[5] + (b[6][k] * u[6]))))))));
        }
        tm += t;
        ++ns;
        if (nper)
        {
            break;
            //             return (tm); /*  return if done    */
        }

        /* Control on size of the next sequence and adjust last sequence to
           exactly cover the integration span.  Nper = TRUE for the last
           sequence.          */

//         force(x, v, tm, f1);
		force_strategy->execute(x, v, tm, f1);


        ++nf;
        if (!nes)
        {
            tp = dir * pow(ss / hv, pw);
            if (tp / t > SR)
                tp = t * SR;
        }
        else
            tp = sequence_size;
        if (dir * (tm + tp) >= (dir * time_delta - 1.0e-14))
        {
            tp = time_delta - tm;
            nper = TRUE;
        }

        /* Now predict b-values for next step using eqs.(13).  Values from the
           preceding sequence were saved in the e[][]-matrix. The corection bd
           is applied in next loop as described in sec. 2.5. */

        q = tp / t;
        q2 = q * q;
        q3 = q2 * q;
        q4 = q2 * q2;
        for (k = 0; k < num_equations; ++k)
        {
            if (ns != 1)
                for (j = 0; j < 7; ++j)
                    bd[j][k] = b[j][k] - e[j][k];

            e[0][k] =
                q * (b[0][k] + 2.0 * b[1][k] + 3.0 * b[2][k] + 4.0 * b[3][k] +
                     5.0 * b[4][k] + 6.0 * b[5][k] + 7.0 * b[6][k]);
            e[1][k] = q2 * (b[1][k] + 3.0 * b[2][k] + 6.0 * b[3][k] +
                            10.0 * b[4][k] + 15.0 * b[5][k] + 21.0 * b[6][k]);
            e[2][k] = q3 * (b[2][k] + 4.0 * b[3][k] + 10.0 * b[4][k] +
                            20.0 * b[5][k] + 35.0 * b[6][k]);
            e[3][k] = q4 * (b[3][k] + 5.0 * b[4][k] + 15.0 * b[5][k] +
                            35.0 * b[6][k]);
            e[4][k] = q2 * q3 * (b[4][k] + 6.0 * b[5][k] + 21.0 * b[6][k]);
            e[5][k] = q3 * q3 * (b[5][k] + 7.0 * b[6][k]);
            e[6][k] = q4 * q3 * b[6][k];

            for (l = 0; l < 7; ++l)
                b[l][k] = e[l][k] + bd[l][k];
        }
        ni = 2; /* Two iterations for every sequence(use 3 for 23rd or 27th
                   order)*/
    } while (1);


    return tm;
}


}
