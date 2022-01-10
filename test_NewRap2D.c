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


#include <stdio.h>

/* Main code */
#include "NewRap2D.h"

/* Testing framework */
#include "greatest.h"

/* Declare a local suite. */
SUITE(suite);

/* Simple non linear F. This defines the set of equations that we are trying to
 * solve. */
void EvaluateFunctions(double *X, double *Y){
    /* F(X) = {2x^2 + 3xy - 5, x + 3y - 2 = 0 } */
    double x = X[0]; double y = X[1];

    Y[0] = 2 * x * x + 3 * x * y - 5;
    Y[1] = x + 3 * y - 2;
}

void EvaluateJacobian(double *X, double (*J)[NUM_DIM]){
    /* F(X) = {2x^2 + 3xy - 5, x + 3y - 2 = 0 } */
    /* J = {{4x + 3y, 3x}, {1, 3}} */
    double x = X[0]; double y = X[1];

    J[0][0] = 4 * x + 3 * y;
    J[0][1] = 3 * x;

    J[1][0] = 1;
    J[1][1] = 3;
}

TEST test_NUM_DIM(void) {
    ASSERT_EQ(NUM_DIM, 2);
    PASS();
}

TEST test_SolveLinearSystem(void) {
    double A[NUM_DIM][NUM_DIM] = { {2, 3}, {7, 1} };
    double X[NUM_DIM];
    double B[NUM_DIM] = {5, 3};

    /* X = {-4/19, -29/19} */

    SolveLinearSystem(A, B, X);

    ASSERT_IN_RANGE( -4./19., X[0], EPS);
    ASSERT_IN_RANGE( -29./19., X[1], EPS);
    PASS();
}

TEST test_ComputeResidual(void) {
    double X[NUM_DIM] = {3, 2};
    /* Y = {31, 7} -> res = 38 */

    ASSERT_IN_RANGE(38., ComputeResidual(X), EPS);
    PASS();
}

TEST test_SolveNonLinearSystem(void) {
    double X[NUM_DIM];
    double X0[NUM_DIM] = {0.5, 0.2};

    int err = SolveNonLinearSystem(X0, X);

    /* From WolframAlpha */

    ASSERT_IN_RANGE( sqrt(6) - 1, X[0], EPS);
    ASSERT_IN_RANGE( 1 - sqrt(6)/3, X[1], EPS);
    ASSERT_EQ(err, 0);
    PASS();
}

/* Primary test suite. */
SUITE(suite) {
    RUN_TEST(test_NUM_DIM);
    RUN_TEST(test_SolveLinearSystem);
    RUN_TEST(test_ComputeResidual);
    RUN_TEST(test_SolveNonLinearSystem);
}

/* Add all the definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */

    RUN_SUITE(suite);

    GREATEST_MAIN_END();        /* display results */
}
