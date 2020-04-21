//
// Created by roeyby on 8/15/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "infi.h"

// TODO: functions!!::


double f1(double x)
{
    return (x * x) / 4;
}

double f2(double x)
{
    double numerator = - (x * x * x) + 3 * (x * x) + x - 4 * sqrt(x);
    double denominator = 2 * x * sqrt(x);
    return (numerator / denominator);
}

double f3(double x)
{
    return sin(x) * sin(x) - cos(x) * cos(x);
}

double f4(double x)
{
    double numerator = sin(x);
    double denominator = 1 + cos(2 * x);
    return (numerator / denominator);
}

double f5(double x)
{

    return pow(M_E, x);
}


double f6(double x)
{
    double numerator = sin(2 * x);
    double denominator = M_E * x * x;
    return (numerator / denominator);
}

int getFunction(unsigned int a, RealFunction fPointer)
{
    switch (a)
    {
        case 1 :
            fPointer = &f1;
            break;
        case 2 :
            fPointer = &f2;
            break;
        case 3 :
            fPointer = &f3;
            break;
        case 4 :
            fPointer = &f4;
            break;
        case 5 :
            fPointer = &f5;
            break;
        case 6 :
            fPointer = &f6;
            break;
        default:
            // TODO: handle error
            exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int checkArgsValidity(char argv[]){

    // TODO: check if:
    /* - argv[1] is unsigned int and 1<=argv[1]<=6
     * - argv[2] is valid double
     * - argv[3] is valid double
     * - argv[4] is valid unsigned int
     * - argv[5] is valid double
     * - argv[6] is valid double
     */

}
int main(int argc, char* argv[])
{
    if (argc != 6){
        // TODO: handle num of args error
    }

    // TODO : receive arguments from the user
    //          - check their validity
    checkArgsValidity(*argv);

    unsigned int functionNumber;
    double a;
    double b;
    unsigned int n;
    double x0;
    double h;

    RealFunction f;


    getFunction(functionNumber,f);
    double integral = integration(f,a,b,n);
    double derivative = derivative(f,x0,h);

    // TODO : print their outputs for every function
    printf("Integral: %.5f\n",integral);
    printf("Derivative: %.5f\n",derivative);

}

// TODO: take care of makefile
// TODO: document
// TODO: README
