/*
 * Copyright (C) 2021 Gabriele Bozzola
 *
 * GRay2 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * GRay2 is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * GRay2. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef NEWRAP2D_H_
#define NEWRAP2D_H_

#include <math.h>
#include <assert.h>
#include <stdio.h>

/* Number of dimensions of the system. This cannot be changed. */
/* One can easily generalize */
#define NUM_DIM 2

/* Tolerance for double precision (e.g., to detect if the determinant of the
 * linear system is zero) */
#define EPS 1e-12

/* Tolerance the solution */
#define TOL 1e-12

/* Maximum number of iterations */
#define MAX_IT 100

/* Prototypes */
/* The user has to implement these */

/* EvaluateFunctions takes as input a vector X and returns in Y the functions
 * evaluated at that X */

/* This defines the set of equations that we are trying to solve. Specifically,
 * we solve for Y = 0. Functions, X, Y, are all NUM_DIM-dimensional. */
void EvaluateFunctions(double *X, double *Y);

/* EvaluateJacobian takes as input a vector X and returns in J the Jacobian
 * evaluated at that J */
void EvaluateJacobian(double *X, double (*J)[NUM_DIM]);


void SolveLinearSystem(double (*A)[NUM_DIM], double *B, double *X);
double ComputeResidual(double *X);
int SolveNonLinearSystem(double *X0, double *X);


/* Implementations*/

void SolveLinearSystem(double (*A)[NUM_DIM], double *B, double *X){
    /* Solve A.X + B = 0 */

    /* Our system of equation is A.X + B = 0
     * a x + by + e = 0
     * c x + dy + f = 0
     *
     * According to Cramer's rule
     *
     * x = - (ed - bf) / (ad - bc)
     * y = - (af - ce) / (ad - bc)
     *
     *  */

    double a = A[0][0]; double b = A[0][1]; double e = B[0];
    double c = A[1][0]; double d = A[1][1]; double f = B[1];

    double det = a * d - b * c;

    /* Cannot solve with zero determinant */
    assert(fabs(det) > EPS);

    X[0] = -(e * d - b * f) / det;
    X[1] = -(a * f - c * e) / det;
}

double ComputeResidual(double *X0){
    /* Compute the residual of the equations being solved.
     * Specifically res = Sum |F(X0)| */
    double res = 0;

    double Y[NUM_DIM];
    EvaluateFunctions(X0, Y);

    for (int i=0; i<NUM_DIM; ++i) res += fabs(Y[i]);

    return res;
}

int SolveNonLinearSystem(double *X0, double *X){
    /* Solve J(X).DX + F(X) = 0 using as initial guess X0 */

    /* If the solution is obtained within the desired tolerance, the
     * return value will be 0. Otherwise, it will be -1. */

    int it_num = 0;
    double res = 0;

    double DX[NUM_DIM], JX[NUM_DIM][NUM_DIM], FX[NUM_DIM];

    for (int i=0; i<NUM_DIM; ++i) X[i] = X0[i];

    do{

        EvaluateJacobian(X, JX);
        EvaluateFunctions(X, FX);
        SolveLinearSystem(JX, FX, DX);

        /* Update solution */
        for (int i=0; i<NUM_DIM; ++i) X[i] += DX[i];

        res = ComputeResidual(X);

#if DEBUG
        printf("Iteration %d, Residual %.8e\n", it_num, res);
        printf("X0 %.16g X1 %.16g\n", X[0], X[1]);
#endif
        it_num++;
    }while(res > TOL && it_num < MAX_IT);

    if (it_num == MAX_IT)
        return -1;

    return 0;
}

#endif // NEWRAP2D_H_
