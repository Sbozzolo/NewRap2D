# NewRap2D

`NewRap2D` is C implementation of a simple Newton-Raphson algorithm for
non-linear 2D systems of equations.

## How to use NewRap2D

`NewRap2D` comes in a single header file `NewRap2D.h`. The header file defines
prototypes and implementations for a series of functions. The user has to
provide the implementation for two functions `EvaluateFunctions` and
`EvaluateJacobian`.

`EvaluateFunctions(double *X, double *Y)` evaluates the functions for which the
roots have to be found in `X` and stores the output in `Y`.

`EvaluateJacobian(double *X, double (*J)[NUM_DIM])` evaluates the Jacobian of
the functions for which the roots have to be found in `X` and stores the output
in `J`.

For example, if we want to solve the system of equations
```
2x^2 + 3xy - 5 = 0,
x + 3y - 2 = 0,
```
then, (in pseudo-code)
```
x = X[0]; y = X[1];
Y[0] = 2x^2 + 3xy - 5,
Y[0] = x + 3y - 2 = 0,
```
and
```
J[0][0] = 4x + 3y;
J[0][1] = 3x;
J[1][0] = 1;
J[1][1] = 3;
```

Once the functions are defined, the solver is called as in

``` c
double X[NUM_DIM];
double X0[NUM_DIM] = {0.5, 0.2};

int err = SolveNonLinearSystem(X0, X);
```
where `X0` is the initial guess. `err` is 0 when the algorithm converges within
the desired tolerance and `-1` when the number of iteration is larger than the
maximum one (set by `TOL` and `MAX_IT` in the `NewRap2D.h`)

## Tests

`NewRap2D` uses the [greatest](https://github.com/silentbicycle/greatest)
testing framework. To run tests, just run `make test`. Tests are automatically
run at every commit.

## Note

We focus on 2D systems because we can be optimized for higher efficiency (given
that we can solve analytically 2D systems of equations in constant time).
However, the code can easily be generalized implementing Cramer's rule to solve
for the generic system of equation.
