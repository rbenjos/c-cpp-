//
// Created by roeyby on 9/13/19.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

using namespace std;

template<typename KeyT, typename ValueT>

/**
 * this class represents a hashmap. as any map, it associates keys with values using a hash function
 * @tparam KeyT the type of the keys
 * @tparam ValueT the type of the values
 */
class HashMap
{
    using pairKV = pair<KeyT, ValueT>;

    // constructors

public:

    // default
    /**
     * the default constructor. initializes the lower and upper load factors to 0.25 and 0.75 respectively
     */
    HashMap() : _lowerLF(0.25), _upperLF(0.75), _sizeVar(0), _capacityVar(16)
    {
        map = new vector<pairKV>[_capacityVar];
    }


    /**
     * this constructor takes in lower and upper load factors
     * @param lowerLF the lower load factor
     * @param upperLF the upper load factor
     */
    HashMap(int lowerLF, int upperLF) : _lowerLF(lowerLF), _upperLF(upperLF), _sizeVar(0), _capacityVar(16)
    {

    }

    /**
     * this constructor takes in a vector of keys and a vector of values and builds and inserts them
     * as pairs to the newly constructed hashmap
     * @param keys the vector of keys
     * @param values the vector of values
     */
    HashMap(vector<ValueT> keys, vector<KeyT> values) : HashMap(0.25,0.75)
    {
        for ( int i : indices(keys))
        {
            this->insert(keys[i], values[i]);
        }
    }

    // copy

    /**
     * the copy constructor
     * @param other a referene to a different hashmap
     */
    HashMap(const HashMap &other)
    {
        _lowerLF = other._lowerLF;
        _upperLF = other._upperLF;
        _sizeVar = other._sizeVar;
        _capacityVar = other._capacityVar;


        delete[] map;
        map = new vector<pairKV>[_capacityVar];
        for ( int i = 0; i < _capacityVar; i ++ )
        {
            map = other.map[i];
        }
    }

    // move
    /**
     * the move constructor
     * @param a reference to another hashmap
     */
    HashMap(HashMap &&other) noexcept
    {
        _lowerLF = exchange(other._lowerLF, 0);
        _upperLF = exchange(other._upperLF, 0);
        _sizeVar = exchange(other._sizeVar, 0);
        _capacityVar = exchange(other._capacityVar, 0);

        map = move(other.map);
    }


    // destructor

    /**
     * the destructor. has to delete the dynamically allocated array of vectors
     */
    ~HashMap()
    {
        delete[] map;
    }

    /**
     * @return the number of pairs in the hashmap
     */
    int size() const
    { return _sizeVar; }

    /**
     * @return the current capacity of the hashmap, meaning the size of the array of vectors
     */
    int capacity() const
    { return _capacityVar; }

    /**
     * @return true if the map is empty. false if not
     */
    bool empty() const
    { return (_sizeVar == 0); }

    /**
     * this method takes in a key and a value. if possible, it inserts them as a pair to the hashmap. if not, if
     * returns false
     * @param key the key
     * @param value the value
     * @return true if successful, false if not
     */
    bool insert(const KeyT key, const ValueT value)
    {
        // check containment
        if ( ! containsKey(key))
        {
            _sizeVar ++;
//            if ( loadfactor() <= _lowerLF )
//            {
//                reHash(0);
//            }
            if ( _upperLF <= getLoadFactor())
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

    /**
     * @param key
     * @return true if our map contains the key, false if not
     */
    bool containsKey(const KeyT key) const
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

    /**
     * this method returns the value associated with a given key. it raises an exception if
     * the map doesnt contain the key
     * @param key
     * @return an lvalue of the ValueT type
     */
    ValueT &at(const KeyT key)
    {
        int index = hash(key);
        if ( map[index].empty())
        { throw std::exception();/* TODO: throw exception  */}
        else
        {
            for ( int i = 0; i < map[index].size(); i ++ )
            {
                if ( map[index][i].first == key )
                { return map[index][i].second; }
            }
            { throw std::exception();/* TODO: throw exception  */}
        }

    }

    /**
     * this method returns the value associated with a given key. it raises an exception if
     * the map doesnt contain the key
     * @param key
     * @return an rvalue of the ValueT type
     */
    const ValueT &at(const KeyT key) const
    {

        int index = hash(key);
        if ( map[index].empty())
        { throw std::exception();/* TODO: throw exception  */}
        else
        {
            for ( int i = 0; i < map[index].size(); i ++ )
            {
                if ( map[index][i].first == key )
                { return map[index][i].second; }
            }
            { throw std::exception();/* TODO: throw exception  */}
        }
    }

    /**
     * this method erase the pair associated with the key given if it exists.
     * @param key the key of the pair we want to erase
     * @return true if successful, false if not
     */
    bool erase(const KeyT key)
    {

        // check containment
        if ( containsKey(key))
        {
            _sizeVar --;

            int index = hash(key);

            for ( int i = 0; i < map[index].size(); i ++ )

                if ( map[index][i].first == key )
                {
                    map[index].erase(map[index].begin() + i);
                    if ( getLoadFactor() <= _lowerLF )
                    {
                        reHash(0);
                    }
                    return true;
                }
        }

        else
        { return false; }

    }

    /**
     * this method returns the size of the vector which contains the given key
     * @param key
     * @return the size of the vector that contains that key. if the key doesnt exist, it will return
     * the size of the bucket that will contain it (the cell given by the hash function)
     */
    int bucketSize(const KeyT key) const
    {
        int index = hash(key);
        return static_cast<int>(map[index].size());
    }

    /**
     * this method clears the hashmap of all of its pairs
     */
    void clear()
    {
        for ( int i = 0; i < capacity(); i ++ )
        {
            map[i].clear();
        }
    }

    /**
     * @return the load factor of the map, meaning the size/capacity ratio
     */
    double getLoadFactor() const
    {
        double size1 = size();
        double capacity1 = capacity();
        return (size1 / capacity1);
    }

//    iterator<KeyT, ValueT> iterator() const
//    {
//
//    }

    /**
     * a helper function to print the map
     */
    void printMap() const
    {
        // general info about map:
        cout << "############## start of hashmap ###########" << "\n";
        cout << "capacity is: " << capacity() << "\n";
        cout << "size is: " << size() << "\n";
        cout << "load factor is: " << getLoadFactor() << "\n";
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
        cout << "############## end of hashmap ###########" << "\n";
    }





    // operators

    // copy =
    /**
     * the copy assignment operator
     * @param other a const reference to another hashmap
     * @return a reference to this hashmap
     */
    HashMap &operator=(const HashMap &other)
    {
        if ( this != &other )
        {
            _lowerLF = other._lowerLF;
            _upperLF = other._upperLF;
            _sizeVar = other._sizeVar;
            _capacityVar = other._capacityVar;
            delete[] map;
            map = new vector<pairKV>[_capacityVar];
            for ( int i = 0; i < _capacityVar; i ++ )
            {
                map = other.map[i];
            }
        }
        return *this;
    }

    // move =

    /**
     * the move assignment operator
     * @param other an rvalue to a hashmap object
     * @return a reference to this hashmap
     */
    HashMap &operator=(HashMap &&other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    /**
     * the lvalue subscript operator, takes in a key and return an lvalue of the value associated with it
     * if the key doesnt exist, it creates a new one
     * @param key
     * @return a reference to the value associated with the key
     */
    ValueT &operator[](const KeyT key)
    {
        if ( ! containsKey(key))
        {
            insert(key, ValueT());
        }
        return at(key);
    }

    /**
     * the rvalue subscript operator, takes in a key and return an lvalue of the value associated with it
     * if the key doesnt exist, it creates a new one
     * @param key
     * @return a reference to the value associated with the key
     */
    const ValueT &operator[](const KeyT key) const
    {
        if ( ! containsKey(key))
        {
            insert(key, ValueT());
        }
        return at(key);
    }

    /**
     * the == operator, compares between 2 hashmaps. because they are basically setes, 2 hashmaps are equal
     * if and only if each member of every map is contained in the other map
     * @param other a reference to another hashmap
     * @return true if equal, false if not
     */
    HashMap operator==(const HashMap &other) const
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

    /**
     * the != operator, returns exactly the opposite of the == operator
     * @param other a reference to another hashmap
     * @return false if the hashmaps are equal, true if they are not
     */
    HashMap operator!=(HashMap &other) const
    {
        return ! (*this == other);
    }


// ########## iterator nested class ##########

    /**
     * this nested class represents an iterator that iterates over the pairs in the hashmaps
     */
    class iterator
    {
    public:
        /**
         * the default constructor, initializes the iterator based on the pointer to the hashmap it
         * gets
         * @param map a pointer to a hashmap object, a nullptr by default
         * @param idx the index in which we are suupposed to start, 0 by default
         */
        iterator(HashMap *map = nullptr, int idx = 0) : hashMap(map), arrIndex(idx)
        {
            if ( map != nullptr )
            {
                currVector = hashMap->map[idx];
                iter = currVector.begin();
                while ( iter == currVector.end() && arrIndex < hashMap->capacity())
                {
                    ++ (*this);
                }
            }
        }


        /**
         * a copy constructor, copies another iterator
         * @param other a reference to another iterator of the same type
         */
        iterator(const iterator &other) : \
        hashMap(other.hashMap), arrIndex(other.arrIndex),
        currVector(hashMap->map[arrIndex]), iter(currVector.begin())
        {}

        /**
         * the dereferencing operator. gives the current pair the iterator is on
         * @return a reference to the current pair of the iterator
         */
        const pairKV &operator*() const
        {
            return *iter;
        }

        /**
         * the -> operator
         * @return the current address of the pair the iterator is currently refering to
         */
        iterator *operator->()
        {
            return iter;
        }

        /**
         * the ++ operator, hops on to the next pair in the hashmap
         * @return a reference to this iterator
         */
        iterator &operator++()
        {
            iter ++;
            while ( iter == currVector.end() && arrIndex < hashMap->capacity())
            {
                arrIndex ++;
                currVector = hashMap->map[arrIndex];
                iter = currVector.begin();
            }

            if ( arrIndex < hashMap->capacity())
            {
                return *this;
            }
            hashMap = nullptr;
            return *this;
        }

        /**
         * the comparison operator
         * @param other a reference to another iterator of the same type
         * @return true if the iterators are in the same position, false if not
         */
        bool operator==(const iterator &other) const
        {
            if ( hashMap == nullptr && other->hashMap == nullptr )
            { return true; }
            else if ( hashMap == nullptr || other->hashMap == nullptr )
            { return false; }
            else
            {
                return (other.iter == this->iter);
            }

        }

        /**
         * the != operator
         * @param other a reference to another iterator of the same type
         * @return false if the iterators are in the same position, true if not
         */
        bool operator!=(const iterator &other) const
        {
            return ! (other.iter == this->iter);
        }

        iterator &operator=(const iterator &other)
        {
            if (this != &other)
            {
                hashMap=other.hashMap;
                arrIndex=other.arrIndex;
                currVector=hashMap->map[arrIndex];
                iter=currVector.begin();
            }
            return *this;
        }

    private:

        HashMap *hashMap;
        int arrIndex;
        vector<pairKV> currVector;
        typename vector<pairKV>::iterator iter;


    };

    // iterator related methods;

    /**
     * @return a reference to an iterator starting from the first pair of the hashmap
     */
    iterator begin()
    {
        iterator iter(this);
        return iter;
    }

    /**
     * @return an iterator with a nullptr as its hashmap pointer
     */
    iterator end()
    {
        iterator iter(nullptr);
        return iter;
    }

private:

    /**
     *
     * @param key
     * @return
     */
    int hash(const KeyT key) const
    {
        std::hash<KeyT> hasher;
        return hasher(key) & (_capacityVar - 1);
    }

    /**
     *
     * @param factor
     * @return
     */
    bool reHash(const int factor)
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

        auto *newMap = new vector<pairKV>[_capacityVar];
        for ( int i = 0; i < oldCap; i ++ )
        {
            for ( pairKV pair : map[i] )
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
