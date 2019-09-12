//
// Created by roeyby on 9/10/19.
//

#include "Fractal.h"
#include <iostream>

/**
 * this function determines if a set of coordinates is a part of the fractal or not. and this, if its should
 * be marked when printed or not
 * @param dim the dimension of the fractal we are currently analyzing
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true if belongs, false otherwise
 */
bool Fractal::belongFunction(int dim, int x, int y) const
{
//    cout << "checking if" << x << y << "belong\n";
    if ( dim == 1 )
    { return basicMember(x, y); }
    else
    {
        if ( basicMember(_f(dim, x), _f(dim, y)))
        {
            int x1 = _g(dim, x);
            int y1 = _g(dim, y);
            return belongFunction(dim - 1, x1, y1);
        }
        else
        { return false; }
    }
}

/**
 * this function builds a grid of chars to represent our fractal using the belong function
 */
void Fractal::buildGrid()
{
//    cout << "building _grid \n";

//    cout << "dim now " << _dim << "\n";
//    cout << "unit_size is " << _unitSize << "\n";

    int size = static_cast<int>(pow(_unitSize, _dim));
//    cout << "_size is " << _size << "\n";
    for ( int y = 0; y < size; y ++ )
    {
        for ( int x = 0; x < size; x ++ )
        {
            if ( belongFunction(_dim, x, y))
            { _grid[y][x] = '#'; }
            else
            {
                _grid[y][x] = ' ';
            }
        }
    }
}

/**
 * the most basic constructor, requires a unit size (not actually used as this is an abstract class)
 * and a dimension
 * @param dim the dimension of the fractal
 * @param unitSize the vertex size of a dim = 1 fractal
 */
Fractal::Fractal(int dim, int unitSize) : _unitSize(unitSize), _dim(dim)
{
    _size = static_cast<int>(pow(_unitSize, dim));
    _grid = vector<vector<char>>();
    _grid.resize(static_cast<unsigned long>(_size), vector<char>(static_cast<unsigned long>(_size)));

}

/**
 * this function prints the fractal if its built
 */
void Fractal::outputFractal() const
{
    for ( int y = 0; y < _size; y ++ )
    {
        for ( int x = 0; x < _size; x ++ )
        {
            std::cout << _grid[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Fractal::~Fractal() = default;

/**
 * this function determines if a set of coordinates is a part of a dim = 1 carpet.
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true if belongs, false otherwise
 */
bool Carpet::basicMember(const int x, const int y) const
{
    return ! (x == 1 && y == 1);
}

/**
 * the default constructor of the carpet
 * @param dim  the dimension of the carpet
 */
Carpet::Carpet(int dim) : Fractal(dim, 3)
{

}

/**
 * this function determines if a set of coordinates is a part of a dim = 1 sieve.
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true if belongs, false otherwise
 */
bool Sieve::basicMember(const int x, const int y) const
{
    return ! (x == 1 && y == 1);
}

/**
 * the default constructor of the sieve
 * @param dim the dimension of the sieve
 */
Sieve::Sieve(int dim) : Fractal(dim, 2)
{
//    cout << "dim received was " << _dim << "\n";
//    cout << "unit_size is " << _unitSize << "\n";
}

/**
 * this function determines if a set of coordinates is a part of a dim = 1 cantor dust fractal.
 * @param x the x coordinate
 * @param y the y coordinate
 * @return true if belongs, false otherwise
 */
bool Dust::basicMember(const int x, const int y) const
{
    return ((x == 0 && y == 0) || (x == 2 && y == 2) || (x == 0 && y == 2) || (x == 2 && y == 0));
}

/**
 * the default constructor of the dust fractal
 * @param dim the dimension of the fractal
 */
Dust::Dust(int dim) : Fractal(dim, 3)
{

}

//############################### factory ##########################
Fractal *FractalFactory::createFractal(int index, int dim)
{
    Fractal *fractal;
    switch (index)
    {
        case 1:
            fractal = new Carpet(dim);
            break;
        case 2:
            fractal = new Sieve(dim);
            break;

        default:
            fractal = new Dust(dim);
            break;
    }
    return fractal;
}
//############################### factory ##########################