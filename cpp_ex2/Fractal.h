//
// Created by roeyby on 9/10/19.
//

#include <cmath>
#include <vector>

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H
using namespace std;

/**
 * this class is an abstract class representing a fractal. a fractal is defined most of all by its dimension
 * by its unit size, and by a function which tells us if the "pattern" of the fractal (called baiscMember here)
 * it has a visual representation using a char called grid
 */
class Fractal
{
protected:

    // the unit _size of the fractal, sieve is 2 for example
    int _unitSize;

    // the dimension of the fractal
    int _dim;

    // the _size of one vertex of the fractal. unitSize^dim
    int _size;

    // an array of chars for the visual representation of the _grid
    vector<vector<char>> _grid;

    // so we can build the _grid only once

    /**
     * this function helps us with the belonging function. it helps us to treat whole sections
     * of the array as discrete subunits
     * @param dim the dimension of the fractal we are currently checking
     * @param x the coordinate we want to analyze
     * @return the location of our coordinate relative to the basic subunits building the function
     *
     * @example if we have a sieve fractal with dim = 3. f(3) = 0 , because the most basic division of our
     * fractals will be to divide each of its vertices by 2, batching its cells to the basic subunits
     */
    int _f(int dim, int x) const
    {
        int y = static_cast<int>(x / (pow(_unitSize, (dim - 1))));
        return y;
    }

    /**
     * this function helps us with the belonging function. it helps us to zoom in on a certain subunit
     * and to check if relative to it our coordinate is valid
     * @param dim the dimension of the fractal we are currently checking
     * @param x the coordinate we want to analyze
     * @return the location of our coordinate inside the basic subunits building the function
     *
     * @example if we have a sieve fractal with dim = 3. g(4) = 0 , because if we look only at the subunit
     * coordinate 4 is in, its the most left one, meaning if the subunit was our whole grid. coordinate 4
     * was actually 0
     */
    int _g(int dim, int x) const
    {
        int y = x % ((int) pow(_unitSize, (dim - 1)));
        return y;
    }

    // constructors
    /**
     * the most basic constructor, requires a unit size (not actually used as this is an abstract class)
     * and a dimension
     * @param dim the dimension of the fractal
     * @param unitSize the vertex size of a dim = 1 fractal
     */
    Fractal(int dim = 1, int unitSize = 1);


    //operator : no need to define any other than default






public:

    /**
     * default destructor, marked virtual because
     * its an abstract class
     */
    virtual ~Fractal();

    /**
     * this function determines if a set of coordinates is a part of the fractal or not. and this, if its should
     * be marked when printed or not
     * @param dim the dimension of the fractal we are currently analyzing
     * @param x the x coordinate
     * @param y the y coordinate
     * @return true if belongs, false otherwise
     */
    bool belongFunction(int dim, int x, int y) const;

    /**
     * this function determines if a set of coordinates is a part of a dim = 1 fractal. this relation is what
     * defines the pattern of the entire fractal
     * @param x the x coordinate
     * @param y the y coordinate
     * @return true if belongs, false otherwise
     */
    virtual bool basicMember(const int x, const int y) const = 0;

    /**
     * this function builds a grid of chars to represent our fractal using the belong function
     */
    void buildGrid();

    /**
     * this function prints the fractal if its built
     */
    void outputFractal() const;
};


//############################### subclasses ##########################


#endif //CPP_EX2_FRACTAL_H

#ifndef CPP_EX2_CARPET_H
#define CPP_EX2_CARPET_H

/**
 * this class represents a serpinski carpet. a certain fractal with unit size of 3
 */
class Carpet : public Fractal
{
private:
    const int _unitSize = 3;
public:

    /**
     * this function determines if a set of coordinates is a part of a dim = 1 carpet.
     * @param x the x coordinate
     * @param y the y coordinate
     * @return true if belongs, false otherwise
     */
    bool basicMember(const int x, const int y) const;

    /**
     * the default constructor of the carpet
     * @param dim  the dimension of the carpet
     */
    Carpet(int dim = 1);

};

#endif //CPP_EX2_CARPET_H

#ifndef CPP_EX2_SIEVE_H
#define CPP_EX2_SIEVE_H

/**
 * this class represents a serpinski sieve fractal
 */
class Sieve : public Fractal
{

private:
    const int _unitSize = 2;
public:

    /**
     * this function determines if a set of coordinates is a part of a dim = 1 sieve.
     * @param x the x coordinate
     * @param y the y coordinate
     * @return true if belongs, false otherwise
     */
    bool basicMember(const int x, const int y) const;

    /**
     * the default constructor of the sieve
     * @param dim the dimension of the sieve
     */
    Sieve(int dim = 1);

};

#endif //CPP_EX2_SIEVE_H

#ifndef CPP_EX2_DUST_H
#define CPP_EX2_DUST_H

/**
 * this class represents a cantor's dust fractal
 */
class Dust : public Fractal
{
private:
    const int _unitSize = 3;
public:

    /**
     * this function determines if a set of coordinates is a part of a dim = 1 cantor dust fractal.
     * @param x the x coordinate
     * @param y the y coordinate
     * @return true if belongs, false otherwise
     */
    bool basicMember(const int x, const int y) const;

    /**
     * the default constructor of the dust fractal
     * @param dim the dimension of the fractal
     */
    Dust(int dim = 1);

};

#endif //CPP_EX2_DUST_H

//############################### subclasses ##########################



//############################### factory ##########################

/**
 * this class represents a fractal factory. it has a single method which takes in a number
 * indicating the type of the fractal we want to create, and its dimension.
 * the method then returns a pointer to that fractal
 */
class FractalFactory
{
public:

    /**
     * this method makes a fractal object based on the index an dimension given
     * @param index the type of the fractal we want to create
     * @param dim the dimension of that fractal
     * @return a pointer to the fractal made
     *
     * @warning uses dynamic allocation, those fractals should be deleted somewhere
     */
    static Fractal *createFractal(int index, int dim);
};
//############################### factory ##########################