#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstring>
#include <vector>
#include "../stl_utils/vector_utilities.h"
#include "bplustree.h"


using namespace std;


template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V())
    {
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << print_me.key;
        outs << ":";
        outs << print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = nullptr)
        {
            _it = it;
        }
        Iterator operator ++(int unused)
        {
            Iterator temp = _it;
            _it++;

            //needs more? 
            //post ++ operator?
            return temp;
        }
        Iterator operator ++()
        {
            _it++;
            return *this;
        }

        Pair<K, V> operator *()
        {
            Pair<K, V> temp = *(_it);
            //return *(_it);
            //return Pair <K, V>();
            return temp;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }
    private:
        typename map_base::Iterator _it;

    };

    Map()
    {
        key_count = 0;
    }
//  Iterators
    Iterator begin()
    {
        return map.begin();
    }
    typename Map<K,V>::Iterator end()
    {
        return map.end();
    }

//  Capacity
    int size() const
    {
        return map.size();
    }
    bool empty() const
    {
        return map.size() == 0;
    }

//  Element Access
    V& operator[](const K& key)
    {
        //cout << "Here" << endl;
        Pair <K, V> temp (key, V());

        return (map.get(temp).value);
    }
    V& at(const K& key)
    {
        Pair <K, V> temp (key);
        return map.get(temp).value;
    }
    const V& at(const K& key) const
    {
        Pair <K, V> temp (key);
        return map.get(temp).value;
       //return map[key];
    }


//  Modifiers
    void insert(const K& k, const V& v)
    {
        //cout << "map insert" << endl;
        map.insert(Pair<K, V> (k, v));
        return;
    }
    void erase(const K& key)
    {
        map.remove(Pair<K, V>(key));
        return;
    }
    void clear()
    {
        map.clear_tree();
        return;
    }
    V get(const K& key)
    {
        Pair <K, V> temps(key);
        return map.get(temps).value;
    }

//  Operations:
    typename Map<K,V>::Iterator find(const K& key)
    {
        Pair <K, V> temp(key);
        //cout << "in maps find" << endl;
        return Map<K, V>::Iterator (map.find(temp));
        //return found;
    }
    bool contains(const Pair<K, V>& target) const
    {
        return map.contains(target.key);
    }

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:
    int count (const K& key)
    {
        return 0;
    }

    //NOT on foremans thing if it doesnt work idfk good luck in esports
    /*Iterator equal_range(int key)
    {
        Iterator it;
        return it;
    }*/

    Iterator upper_bound(K& key)
    {
        Pair<K, V> temp(key);
        return map.upper_bound(key);
    }
    Iterator lower_bound(K& key)
    {
        Pair <K, V> temp(key);
        // Pair<K, V> check;
        // cout << "in lower bound " << endl;
        // cout << *(begin()) << endl;
        // for (Iterator i = begin(); i != end(); i++)
        // {
        //     check = *i;
        //     cout << "enters this loop" << endl;
        //     cout << check << endl;
        //     if (check >= temp)
        //     {
        //         cout << "return issue" << endl;
        //         return i;
        //     }
        // }
        // cout << "here?" << endl;
        // Iterator itr = end();
        // return itr;
        return map.lower_bound(temp);
    }
    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};



#endif