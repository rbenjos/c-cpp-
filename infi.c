//
// Created by roeyby on 8/14/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


typedef double (*RealFunction)(double);

/**
 * this function evaluates the derivative of a given function in a given point and with a given
 * step size
 * @param f the function we are deriving
 * @param x the point in which we are deriving
 * @param h the step size
 * @return the value of the derivative in that point
 */
double derivative(RealFunction f, double x, double h)
{
    assert(h > 0);

    double y = f(x);
    assert(!isnan(y) && isfinite(y));

    double positive = f(x + h);
    double negative = f(x - h);
//    assert(!isnan(positive)&&!isnan(negative));
//    assert(isfinite(positive)&&isfinite(negative));
    double derivative = (positive - negative) / (2 * h);
//    assert(!isnan(derivative)&&isfinite(derivative));
    return derivative;
}

/**
 * this function implements numerical integration
 * @param f the function we integrate
 * @param a the starting point of the integration
 * @param b the endpoint of the integration
 * @param n the number of steps we are taking. the number of points we are sampling from the function
 * @return the integration value
 */
double integration(RealFunction f, double a, double b, unsigned int n)
{
    double delX = (b - a) / n;
    double sum = 0;

    assert(n > 0);
    assert (a<b);

    unsigned int i = 1;
    for ( ; i <= n; i ++ )
    {
        double currentPoint = (2 * a + delX * (2 * i - 1)) / 2;
        double val = f(currentPoint);
        sum += f(currentPoint) * delX;
    }

    return sum;

}

