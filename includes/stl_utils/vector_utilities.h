#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        outs << list[i];
        outs << " ";
    }
    return outs;
} //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme)
{
    list.push_back(addme);
    return list;
} //list.push_back addme






#endif