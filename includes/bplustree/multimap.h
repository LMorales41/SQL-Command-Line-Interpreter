#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <iostream>
#include <vector>
#include <cstring>
#include "../stl_utils/vector_utilities.h"
#include "btree_array_funcs.h"
#include "bplustree.h"

using namespace std;



template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K())
    {
        key = k;
    }
    MPair(const K& k, const V& v)
    { 
        key = k;
        //insert value into list
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist)
    {
        key = k;
        for (int i = 0; i < vlist.size(); i++) //insert vector into vector
        {
            value_list.push_back(vlist[i]); 
        }
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << print_me.key << ": ";
        for (int i = 0; i < print_me.value_list.size();i++)
        {
            outs << print_me.value_list[i];
            outs << " ";
        }
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        //cout << " operator > here" << endl;
        return lhs.key > rhs.key;
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        MPair <K, V> hold(lhs.key, lhs.value_list); //this holds lhs values
        for (int i = 0; i < rhs.value_list.size(); i++)
        {
            hold.value_list.push_back(rhs.value_list[i]);
        }
        //hold.value_list.insert(rhs.value_list);
        //hold.value_list.insert(rhs.value_list.begin(), lhs.value_list.end());
        //this does not change lef hand side and you can return hold result
        return hold;
    }

};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator (){}
        Iterator(typename map_base::Iterator it)
        {
            _it = it;
        }
        Iterator operator ++(int unused)
        {
            //cout << "operator++ in mmap" << endl;
            
            //need to do something else? 
            //post++ operator
            return _it++;
        }
        Iterator operator ++()
        { 
            //pre++ operator
            
            return ++_it;
        }
        MPair<K, V> operator *()
        {
            //MPair<K, V> temp;

            //return temp.key;
            //cout << "dereference" << endl;
            return *(_it);
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

    MMap()
    {
    }   

//  Iterators
    Iterator begin()
    {
        
        return mmap.begin();
    }
    Iterator end()
    {
        return mmap.end();
    }

//  Capacity
    int size() const
    {
        return mmap.size();
    }
    bool empty() const
    {
        return mmap.empty();
    }

//  Element Access
    const vector<V>& operator[](const K& key) const
    {
        MPair<K, V> temp (key);
        return mmap.get(temp).value_list;
    }

    vector<V>& operator[](const K& key) 
    {
        MPair <K, V> temp (key);
        return mmap.get(temp).value_list;
    }

//  Modifiers
    void insert(const K& k, const V& v)
    {
        MPair<K, V> inserting_this(k, v); //fills in the mpair to insert
        //cout <<  "here?" << endl;
        //cout << "mmap insert func" << endl;
        mmap.insert(inserting_this);
        return;
    }
    void erase(const K& key)
    {
        V temp;
        MPair <K, V> removing_this (key, temp);
        mmap.remove(removing_this);
        return;
    }
    void clear()
    {
        mmap.clear_tree();
        return;
    }

//  Operations:
    bool contains(const K& key) const
    {
        //V temp;
        //MPair <K, V> temp (key);
        return mmap.contains(MPair<K, V>(key));
    }
    vector<V> &get(const K& key)
    {
        V temp;
        MPair<K, V> get_this (key, temp);
        return mmap.get(get_this);

        //return nullptr;
    }

    Iterator find(const K& key)
    {
         Iterator it(mmap.find(key));
        return it;
    }
    int count(const K& key)
    {
        return 0;
    }
    vector<V> at (const K& key) //very very likely wrong lmao
    {   
        MPair <K, V> temp (key);
        
        return mmap.get(temp).value_list;

    }
    vector<V> at (const K& key) const //const ver
    {   
        MPair <K, V> temp (key);
        
        return mmap.get(temp).value_list;

    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:
    Iterator lower_bound(K& key)
    {
        MPair<K, V> temp (key);
        return Iterator(mmap.lower_bound(temp));
    }
    Iterator upper_bound (K& key)
    {
        MPair <K, V> temp (key);
        //cout << "UB in mmap: " << temp << endl;
        return Iterator(mmap.upper_bound(temp));
    }
    Iterator equal_range(int key)
    {
        Iterator it;
        return it;
    }


    bool is_valid()
    {
        return mmap.is_valid();
        //return true;
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup()
    {
        string col = "col";
        string command = "command";
        string condition = "condition";
        string fields = "fields";
        string table_name = "table_name";
        string values = "values";
        string where = "where";
        if (mmap.contains(col))
        {
            cout << *mmap.find(col) << endl;
        }
        if (mmap.contains(command))
        {
            cout << *mmap.find(command) << endl;
        }
        if (mmap.contains(condition))
        {
            cout << *mmap.find(condition) << endl;
        }
        if (mmap.contains(fields))
        {
            cout << *mmap.find(fields) << endl;
        }
        if (mmap.contains(table_name))
        {
            cout << *mmap.find(table_name) << endl;
        }
        if (mmap.contains(values))
        {
            cout << *mmap.find(values) << endl;
        }
        if (mmap.contains(where))
        {
            cout << *mmap.find(where) << endl;
        }
        
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};





#endif