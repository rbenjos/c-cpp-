//
// Created by roeyby on 9/13/19.
//

#include <iostream>
#include <vector>

#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

using namespace std;

template<typename KeyT, typename ValueT>

class HashMap
{
    using pairKV = pair<KeyT, ValueT>;

    // constructors

public:

    // default
    HashMap() : _lowerLF(0.25), _upperLF(0.75), _sizeVar(0), _capacityVar(16)
    {
        map = vector<vector<pair<KeyT, ValueT>>>();
    }

    HashMap(int lowerLF, int upperLF) : _lowerLF(lowerLF), _upperLF(upperLF), _sizeVar(0), _capacityVar(16)
    {

    }

    HashMap(vector<ValueT> keys, vector<KeyT> values)
    {
        HashMap();
        for ( int i : indices(keys))
        {
            this->insert(keys[i], values[i]);
        }
    }

    // copy
    HashMap(HashMap& other)
    {
        _lowerLF = other._lowerLF;
        _upperLF = other._upperLF;
        _sizeVar = other._sizeVar;
        _capacityVar = other._capacityVar;

        map = other.map;
    }

    // move
    HashMap(HashMap&& other)
    {
        _lowerLF = exchange(other._lowerLF, 0);
        _upperLF = exchange(other._upperLF, 0);
        _sizeVar = exchange(other._sizeVar, 0);
        _capacityVar = exchange(other._capacityVar, 0);

        map = move(other.map);
    }


    // destructor

    ~HashMap();

    int size() const
    { return _sizeVar; }

    int capacity() const
    { return _capacityVar; }

    bool empty() const
    { return (_sizeVar == 0); }

    bool insert(KeyT key, ValueT value)
    {
        int index = hash(key);
        for ( pair<KeyT, ValueT> pair : map[index] )
        {
            if ( pair.first == key )
            { return false; }
        }
        map[index].push_back(pair < KeyT, ValueT > (key, value));
        return true;


        //TODO: more places that it can go wrong?

        // TODO: rehash if needed
    }

    bool containsKey(KeyT key)
    {
        int index = hash(key);
        if ( map[index].empty())
        { return false; }
        else
        {
            for ( pair<KeyT, ValueT> pair : map[index] )
            {
                if ( pair.first == key )
                { return true; }
            }
            return false;
        }
    }

    ValueT at(KeyT key)
    {
        int index = hash(key);
        if ( map[index].empty())
        { /* TODO: throw exception  */}
        else
        {
            for ( pair<KeyT, ValueT> pair : map[index] )
            {
                if ( pair.first == key )
                { return pair.second; }
            }
            { /* TODO: throw exception  */}
        }

    }

    bool erase(KeyT key)
    {
        int index = hash(key);
        if ( map[index].empty())
        { return false; }
        else
        {
            int i = 0;
            for ( pair<KeyT, ValueT> pair : map[index] )
            {
                if ( pair.first == key )
                {
                    map[index].erase(i);
                    return true;
                }
                i ++;
            }
            { return false; }


            // TODO: rehash if needed
        }

    }

    int bucketSize(KeyT key) const
    {
        int index = hash(key);
        return static_cast<int>(map[index].size());
    }

    void clear()
    {

    }

    iterator<KeyT, ValueT> iterator() const;

    HashMap operator=(HashMap& other);

    HashMap operator==(HashMap& other)
    {
        for ( pair<KeyT, ValueT> pair : *this )
        {
            if ( this->at(pair.first) != other[pair.first] )
            { return false; }
        }
        for ( pair <KeyT, ValueT> pair : other )
        {
            if ( other.at(pair.first) != (*this)[pair.first] )
            { return false; }
        }
        return true;
    }

    HashMap operator!=(HashMap& other)
    {
        return (! *this == other);
    }

    ValueT operator[](KeyT key);


// ########## iterator nested class ##########

    class iterator
    {
    public:
        iterator(HashMap *hashMap) : hashMap(hashMap)
        {}

        iterator& operator*()
        {
            return *(hashMap)[arrIndex][vecIndex];
        }

        iterator& operator++()
        {
            if ( hashMap->map[arrIndex].size() == (vecIndex + 1))
            {
                arrIndex ++;
                vecIndex = 0;
                while(hashMap->map[arrIndex].empty()){arrIndex++;}
            }
            else
            { vecIndex ++; }
        }

    private:

        HashMap* hashMap;
        int arrIndex, vecIndex;
    };

private:

    int hash(KeyT key)
    {
        return key & (_capacityVar - 1);
    }

    bool reHash();

    HashMap& reSize();

    // load factors
    double _lowerLF;
    double _upperLF;

    // size and capacity

    int _sizeVar;
    int _capacityVar;

    // the map itself
    vector<pair<KeyT, ValueT>> map[];
};

#endif //CPP_EX3_HASHMAP_HPP
