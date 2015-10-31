/*
 * Pollard's Rho algorithms
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#ifndef POLLARD_RHO_H
#define POLLARD_RHO_H

class BigInt;

extern BigInt pollardRho(const EllipticCurve &E, const Point &P, const Point &Q);

#endif
