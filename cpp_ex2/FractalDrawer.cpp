#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include "Fractal.h"
#include <filesystem>
#include <fstream>
#include <assert.h>
#include <stack>

using namespace std;

/**
 * this function handles a misuse of the program by the user.
 */
void badUsage()
{
    cerr << "Usage:  FractalDrawer <file path>\n";
}

/**
 * this function handles an invalid input in the file given
 */
void invalidInput()
{
    cerr << "Invalid input\n";
}

void disposeStack(stack<Fractal *> *fractals)
{
    while ( ! fractals->empty())
    {
        Fractal *currentFractal = fractals->top();
        delete currentFractal;
        fractals->pop();
    }
}

/**
 * this is the main function, it assures the validity of the file given and its content. if it is
 * indeed valid, it builds a stack of pointers to fractals, and then prints those fractals
 * @param fileName
 * @return
 */
int drawFractals(const string& fileName)
{
    fstream file;
    file.open(fileName, ios::in);

    // assert exists
    if ( file.fail())
    {
        invalidInput();
    }

    // assert not empty
    if ( file.peek() == fstream::traits_type::eof())
    {
        invalidInput();
    }


    /* our job is to treat every line by itself. if its valid we should create a fractal based on it
     * with the fractal factory we will make and append it to a Fractal data structure
     * (probably a vector or a stack. maybe a stack because we need to print it from the last one to the first).
     * otherwhise we should exit */

    // so lets create that data structure
    stack<Fractal *> fractals;
    Fractal *currentFractal;

    // now lets parse the lines
    char line[100];
    while ( file.getline(line, 100, '\n'))
    {
        int type = line[0] - '0';
        char comma = line[1];
        int dim = line[2] - '0';
        char end = line[3];


        // now the validity of the content:

        // the type should be between 1 and 3 (inclusive)
        if ( type < 1 || 3 < type )
        {
            disposeStack(&fractals);
            file.close();
            invalidInput();
            return 1;

        }

            // the dimension should be between 1 and 6 (inclusive)
        else if ( dim < 1 || 6 < dim )
        {
            disposeStack(&fractals);
            file.close();
            invalidInput();
            return 1;

        }

            // there should be a comma between them
        else if ( comma != ',' )
        {
            disposeStack(&fractals);
            file.close();
            invalidInput();
            return 1;

        }

            // and there should be no additional characters after the second number
        else if ( end != '\0' )
        {
            disposeStack(&fractals);
            file.close();
            invalidInput();
            return 1;

        }

            // if the line is valid, we will build a fractal using the factory and append to the stack
        else
        {
            currentFractal = FractalFactory::createFractal(type, dim);
            fractals.push(currentFractal);
        }
    }

    // after we are done building the stack we will print in reverse order anything in it, and dispose of it
    while ( ! fractals.empty())
    {
        currentFractal = fractals.top();
        currentFractal->buildGrid();
        currentFractal->outputFractal();
        delete currentFractal;
        fractals.pop();
    }
    file.close();
    return 0;

}

/**
 * the main function of the program.
 * @param argc the number of arguments received
 * @param argv an array of strings representing the arguments
 * @return 0 if successfully ended.
 */
int main(int argc, char **argv)
{
    if ( argc != 2 )
    { badUsage(); }
    if ( drawFractals(argv[1]) == 1 )
    {
        return 1;
    }
    return 0;
}
