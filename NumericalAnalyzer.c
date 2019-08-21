//
// Created by roeyby on 8/15/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "infi.h"


#define MAX_CHARS_PER_DOUBLE 1024
// TODO: functions!!::

void invalidInput(void)
{
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
}

int validateDouble(const char *strNumber)
{

    int counter = 0;
    int delCounter = 0;
    int sign = 1;
    if ( strNumber[counter] == '-' )
    {
        sign = - 1;
        counter++;
    }
    while ( strNumber[counter] != '\0' )
    {
        char currentChar = strNumber[counter];
        int digit = currentChar - '0';
        if ( 0 <= digit && digit <= MAX_CHARS_PER_DOUBLE )
        {
            counter ++;
        }
        else
        {
            if ( currentChar == '.' )
            {
                delCounter ++;
                counter ++;
            }
            else
            {
                invalidInput();
            }
        }
    }
    if ( delCounter <= 1 && counter <= MAX_CHARS_PER_DOUBLE )
    {
        return 0;
    }
    else
    {
      invalidInput();
    }
}

int validateInt(const char *strNumber)
{
    int counter = 0;
    int delCounter = 0;
    int sign = 1;
        if ( strNumber[counter] == '-' )
        {
            sign = - 1;
            counter++;
    }
    while ( strNumber[counter] != '\n' && strNumber[counter] != '\0' )
    {
        char currentChar = strNumber[counter];
        int digit = currentChar - '0';
        if ( 0 <= digit && digit <= 9 )
        {
            counter ++;
        }
        else
        {
           invalidInput();
        }
    }
    return 0;
}


double f1(double x)
{
    return (x * x) / 4;
}

double f2(double x)
{
    double numerator = - (x * x * x) + 3 * (x * x) + x - 4 * sqrt(x);
    double denominator = 2 * x * sqrt(x);

    if ( denominator == 0 || x < 0 )
    {
        invalidInput();
    }

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
    if ( denominator == 0 )
    {
        invalidInput();
    }


    return (numerator / denominator);
}

double f5(double x)
{

    return pow(M_E, x);
}


double f6(double x)
{
    double numerator = sinh(2 * x);
    double denominator = M_E * x * x;

    if ( denominator == 0 )
    {
        invalidInput();
    }
    return (numerator / denominator);
}

int getFunction(unsigned int a, RealFunction *fPointer)
{
    switch (a)
    {
        case 1 :
            *fPointer = &f1;
            break;
        case 2 :
            *fPointer = &f2;
            break;
        case 3 :
            *fPointer = &f3;
            break;
        case 4 :
            *fPointer = &f4;
            break;
        case 5 :
            *fPointer = &f5;
            break;
        case 6 :
            *fPointer = &f6;
            break;
        default:
            invalidInput();
    }
    return EXIT_SUCCESS;
}

void checkArgsValidity(char *argv[])
{

    // TODO: check if:
    /* - argv[1] is unsigned int and 1<=argv[1]<=6
     * - argv[2] is valid double
     * - argv[3] is valid double
     * - argv[4] is valid unsigned int
     * - argv[5] is valid double
     * - argv[6] is valid double
     */

    validateInt(argv[1]);
    validateDouble(argv[2]);
    validateDouble(argv[3]);
    validateInt(argv[4]);
    validateDouble(argv[5]);
    validateDouble(argv[6]);


}

int main(int argc, char *argv[])
{
    if ( argc != 7 )
    {
        fprintf(stderr, "Usage:  NumericalAnalyzer <function number> <a> <b> <N> <x0> <h>\n");
        exit(EXIT_FAILURE);
    }

    // TODO : receive arguments from the user
    //          - check their validity
    checkArgsValidity(argv);

    // if they are valid we will assign them

    int functionNumber = atoi(argv[1]);
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    int n = atoi(argv[4]);
    double x0 = atof(argv[5]);
    double h = atof(argv[6]);


    // and check if they are in the right range:

    if ( functionNumber < 1 || functionNumber > 6 )
    { invalidInput(); }
    if ( n <= 0 )
    { invalidInput(); }
//    if ( h <= 0.0 )
//    { invalidInput(); }
    if (b<=a){invalidInput();}
    // we also cant integrate through an asymptote or

    RealFunction *f;
    getFunction(functionNumber, f);
    double integralVal = integration(*f, a, b, n);
    double derivativeVal = derivative(*f, x0, h);

    // TODO : print their outputs for every function
    printf("Integral: %.5f\n", integralVal);
    printf("Derivative: %.5f\n", derivativeVal);

    return 0;

}

// TODO: take care of makefile
// TODO: document
// TODO: README
