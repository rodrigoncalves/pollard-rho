/*
 * Pollard's rho algorithms
 *
 * Author: Rodrigo
 * Date: 31/10/2015
 * License: LGPL. No copyright.
 */
#ifndef POLLARD_RHO_H
#define POLLARD_RHO_H

namespace PollardRho {
	BigInt original(EllipticCurve &E, const Point &P, const Point &Q);
	BigInt serial(EllipticCurve &E, const Point &P, const Point &Q);
	BigInt parallelized(EllipticCurve &E, const Point &P, const Point &Q);
}

#endif
