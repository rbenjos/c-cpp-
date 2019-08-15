//
// Created by roeyby on 8/14/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// TODO : derivative!!

typedef double (* RealFunction)(double);

// dummy functions ###:


double constant1(double x)
{ return 5; }

double linear1(double x)
{ return x; }

double linear2(double x)
{ return 10 * x - 5; }

double quadratic1(double x)
{ return 3 * (x * x) + (5 * x) - 2; }

double quadratic2(double x)
{ return 0.5 * (x * x) + (- 12.5 * x); }

double cubic1(double x)
{ return 2 * (x * x * x) + 3 * (x * x) + (5 * x) - 2; }

double root(double x)
{ return sqrt(x); }

double rationa1(double x)
{ return (1 / x); }

double derivative(RealFunction f, double x, double h)
{
    double positive = f(x + h);
    double negative = f(x - h);
    double derivative = (positive - negative) / (2 * h);
    return derivative;
}





// TODO : integration ###!!!:::

double integration(RealFunction f, double a, double b, unsigned int n)
{
    double delX = (b-a)/n;
    double sum = 0;

    printf("delx is: %f \n", delX);

    int i = 1;
    for (; i<=n;i++){
        double currentPoint =(2*a+delX*(2*i-1))/2 ;
        sum+= f(currentPoint)*delX;
    }

    return sum;

}

