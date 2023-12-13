#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <iostream>

using namespace std;

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   
//return the first element in data that is
//not less than entry

template <class T>
int index_of_maximal(T data[ ], int n); 

template <class T>
void swap(T& a, T& b);


template<class T>
void ordered_insert(T data[ ], int& n, T entry);       //insert entry into the sorted array
// data = array, n = size, entry = item to insert, @index 

template <class T>
void shift(T data [ ], int &shift_amount, int leave_hole_here); // be careful not to go over size


template<class T>
void insert_item(T data[ ], int i, int& n, T entry);
//data = array, i = index to insert in, n = size, entry = item to insert

template <class T>
void detach_item(T data[ ], int& n, T& entry);

template <class T>
void split_array(T data_src [ ] , T data_dest [ ] ,int& size_src, int& size_dest);
template <class T>
void copy_array(T dest[], const T src[],int& dest_size, int src_size);

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void shift_left(T data [ ], int &shift_amount, int hole_here);

template <class T>
void attach_item(T data[ ], int& n, const T& entry);

template <class T>
void print_array(T data[ ], int& n, const T& entry)
{

}

///////////////////////////////////////////////////////
template <class T>
void attach_item(T data[ ], int& n, const T& entry)
{
    data[n] = entry;
    n++;
}

template <class T>
void shift_left(T data [ ], int &shift_amount, int hole_here)
{
    int j = shift_amount - 1;
    for (int i = hole_here; i < j; i++)
    {
        data[i] = data[i+1];
    }
    shift_amount--;
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2) //data1 gets big, data2 gets small
{
    int newSize = n1 + n2;
    /*cout << "test for merge(before): ";
    for (int i = 0; i < n1;i++)
    {
        cout << data1[i] << "|";
    }*/
    for (int i = 0; i < n2; i++)
    {
        data1[i + n1] = data2[i];
    }
    n2 = 0;
    n1 = newSize;

    /*cout << endl;
    n1 += count;
    n2 -= count;
    cout << "test for merge(after): ";
    for (int i = 0; i < n1;i++)
    {
        cout << data1[i] << "|";
    }
    cout << endl;*/
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)
{
    entry = data[i];
    for (int j = i; j < n;j++)
    {
        data[j] = data[j+1];
    }
    n--;

}

template <class T>
void copy_array(T dest[], const T src[],int& dest_size, int src_size)
{
    
    for (int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
        
    }
    dest_size = src_size;

}

template <class T>
void split_array(T data_src [ ] , T data_dest [ ], int& size_src, int& size_dest) // size is of source array
{
    //int size = size - start_splitting_here;
    //T copy_array [size];

    
    int midpoint = size_src/2;
    if (size_src % 2 == 0)
    {
        midpoint--;
    }
    int iter_for_copy_array = 0;
    int count = 0;
    //cout << "size_dest: " << size_dest << endl;
    //cout << "size: " << size << endl;


    //going to make it start at midpoint instead of midpoint+1 <- new for b+tree

    for (int i = midpoint+1; i < size_src; i++)
    {
        //insert_item(data_dest, iter_for_copy_array, size_dest, data_src[i] );
        data_dest[iter_for_copy_array] = data_src[i];
        
        iter_for_copy_array++;
        count++;
    }
    size_dest += count;
    size_src -= count;
    //cout << "size_dest: " << size_dest << endl;
    //cout << "size: " << size <<endl;
    /*for (int i = size; i > start_splitting_here; i--)
    {
        detach_item(data_src, size, data_src[i]);
    }*/
}
//breaks off starting at midpoint+1
//inserts into new array
//removes copied pieces from old array
//returns new array (with elements from midpoint+1)

template <class T>
void detach_item(T data[ ], int& n, T& entry)
{
    //data[n-1] = entry //was like thisbefore
    entry = data[n-1];
    n--;
}


template <class T>
int index_of_maximal(T data[ ], int n)
{
    return data[n-1];
}



template<class T>
void insert_item(T data[ ], int i, int& n, T entry)
{
    shift(data, n, i);
    data[i] = entry;
    //n++;
}

template <class T>
void shift(T data [], int& shift_amount, int leave_hole_here)
{
    //cout << "index: " << leave_hole_here << "amt: " << shift_amount <<endl;
    for (int i = shift_amount; i > leave_hole_here; i--) 
    {
        //cout << i << endl;
        data[i] = data[i-1];
    }
    shift_amount++;
}


template <class T>
void ordered_insert(T data[ ], int& n, T entry)
{
    // cout << "size: " << n << endl;

    int index = first_ge(data, n, entry);
    shift (data, n,index); //increases
    // cout << "index: " << index <<endl;
    // cout << "entry: " << entry << endl;
    data[index] = entry;
    //insert_item(data, index, n, entry); //increases again
    //n--;
}


template <class T>
void swap(T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}


template <class T>
int first_ge(const T data[ ], int n, const T& entry)
{
    //check entry
    for (int i = 0; i < n; i++)
    {
        if (data[i] >= entry)
        {
            
            return i;
        }
        else 
        {

        }
    }
    return n;
}   
//return the first element in data that is
//not less than entry






#endif