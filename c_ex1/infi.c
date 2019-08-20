//
// Created by roeyby on 8/14/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// TODO : derivative!!

typedef double (* RealFunction)(double);

// dummy functions ###:


// todo: check what input is correct for x,h
double derivative(RealFunction f, double x, double h)
{
    assert(h!=0);
    double positive = f(x + h);
    double negative = f(x - h);
    assert(!isnan(positive)&&!isnan(negative));
    assert(isfinite(positive)&&isfinite(negative));
    double derivative = (positive - negative) / (2 * h);
    assert(!isnan(derivative)&&isfinite(derivative));
    return derivative;
}


// TODO: check what input is correct for a,b,n

double integration(RealFunction f, double a, double b, unsigned int n)
{
    double delX = (b-a)/n;
    double sum = 0;

    assert(n>0);

    unsigned int i = 1;
    for (; i<=n;i++){
        double currentPoint =(2*a+delX*(2*i-1))/2 ;
        sum+= f(currentPoint)*delX;
    }

    return sum;

}

