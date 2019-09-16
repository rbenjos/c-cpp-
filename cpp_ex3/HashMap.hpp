//
// Created by roeyby on 9/13/19.
//

#include <iostream>
#include <vector>
#include <algorithm>

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
        map = new vector<pairKV>[_capacityVar];
    }

    HashMap(int lowerLF, int upperLF) : _lowerLF(lowerLF), _upperLF(upperLF), _sizeVar(0), _capacityVar(16)
    {

    }

    HashMap(vector<ValueT> keys, vector<KeyT> values) : _lowerLF(0.25), _upperLF(0.75), _sizeVar(0), _capacityVar(16)
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
    HashMap(HashMap&& other) noexcept
    {
        _lowerLF = exchange(other._lowerLF, 0);
        _upperLF = exchange(other._upperLF, 0);
        _sizeVar = exchange(other._sizeVar, 0);
        _capacityVar = exchange(other._capacityVar, 0);

        map = move(other.map);
    }


    // destructor

    ~HashMap()
    {
        delete[] map;
    }

    int size() const
    { return _sizeVar; }

    int capacity() const
    { return _capacityVar; }

    bool empty() const
    { return (_sizeVar == 0); }

    bool insert(KeyT key, ValueT value)
    {

        // check containment
        if ( ! containsKey(key))
        {
            _sizeVar ++;
//            if ( loadfactor() <= _lowerLF )
//            {
//                reHash(0);
//            }
            if ( _upperLF <= loadfactor())
            {
                reHash(1);
            }

            int index = hash(key);
            map[index].push_back(pair<KeyT, ValueT>(key, value));
            return true;
        }
        else
        { return false; }


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
        // check containment
        if ( containsKey(key))
        {
            _sizeVar --;

            int index = hash(key);
            vector<pairKV> vec = map[index];

            for ( int i = 0; i < vec.size(); i ++ )
            {
                if ( vec[i].first == key )
                {
                    map[index].erase(vec.begin() + i);
                    if ( loadfactor() <= _lowerLF )
                    {
                        reHash(0);
                    }
                    return true;
                }
            }
        }
        else
        { return false; }

    }

    int bucketSize(KeyT key) const
    {
        int index = hash(key);
        return static_cast<int>(map[index].size());
    }

    void clear()
    {

    }

    double loadfactor()
    {
        double size1 = size();
        double capacity1 = capacity();
        return (size1 / capacity1);
    }

//    iterator<KeyT, ValueT> iterator() const
//    {
//
//    }

    void printMap()
    {
        for ( int i = 0; i < capacity(); i ++ )
        {
            vector<pairKV> vec = map[i];
            cout << "vec num " << i << " of size : " << vec.size() << ": ";
            for ( pairKV pair : vec )
            {
                cout << "** key: " << pair.first << " value: " << pair.second << "**, ";
            }
            cout << "\n";
        }
    }

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
        iterator(HashMap *hashMap = nullptr) : hashMap(hashMap), arrIndex(0)
        {
            currVector = hashMap->map[0];
            iter = currVector.begin();
        }

        iterator& operator*()
        {
            return *iter;
        }

        iterator *operator->()
        {
            return iter;
        }

        iterator& operator++()
        {
            while ( *iter == currVector.end())
            {
                arrIndex ++;
                currVector = hashMap->map[arrIndex];
                iter = currVector.begin();
            }

            iter ++;

        }

    private:

        HashMap *hashMap;
        vector<pairKV> currVector;
        typename vector<pairKV>::iterator *iter;
        int arrIndex;


    };

private:

    int hash(KeyT key)
    {
        return key & (_capacityVar - 1);
    }

    bool reHash(int factor)
    {

        // resizing the capacity
        int oldCap = _capacityVar;
        switch (factor)
        {
            case 0:
                _capacityVar /= 2;
                break;
            case 1:
                _capacityVar *= 2;
                break;
            default:
                break;
        }

        vector<pairKV> *newMap = new vector<pairKV>[_capacityVar];
        for ( int i = 0; i < oldCap; i ++ )
        {
            vector<pairKV> vec = map[i];
            for ( pairKV pair : vec )
            {
                int hashCode = hash(pair.first);
                newMap[hashCode].push_back(pair);
            }
        }
        delete[] map;
        map = newMap;

    }

    // load factors
    double _lowerLF;
    double _upperLF;

    // size and capacity

    int _sizeVar;
    int _capacityVar;

    // the map itself
    vector<pair<KeyT, ValueT>> *map;
};

#endif //CPP_EX3_HASHMAP_HPP
