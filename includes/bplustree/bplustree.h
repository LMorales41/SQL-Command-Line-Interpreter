#ifndef BPLUSTREE_H
#define BPLUSTREE_H


#include <iostream>
#include <string>
#include <iomanip>
#include "assert.h"
#include "btree_array_funcs.h"
#include "../stl_utils/vector_utilities.h"

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        //Iterator(){it = NULL; key_ptr = 0;}
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}

        T operator *()
        {

            return it->data[key_ptr];
        }

        const T operator *() const
        {

            return it->data[key_ptr];
        }

        Iterator operator++(int un_used) //post increment
        {   
            
            Iterator temp (it, key_ptr);
            key_ptr++;

            if (key_ptr == it->data_count)
            {
                it = it->next;
                key_ptr = 0;
            }

            return temp; //return the held one
        }
        Iterator operator++()
        {
            key_ptr++;
            if (key_ptr == it->data_count)
            {
                it = it->next;
                key_ptr = 0;
            }
            
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            if (lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr)
            {
                return true;
            }
            else
            {
                return false;
            }

            //return true;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {

            // if (lhs.it == nullptr)
            // {
            //     return false;
            // }
        
            //int check = lhs.key_ptr;
            return !(lhs == rhs);
            //return true;
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };
    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);
    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();   
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);
    void make_tree();

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object

                                                //  (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other);      //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    bool contains(const T& entry);              //true if entry can be found in the array
    bool contains (const T& entry) const;
    T& get(const T& entry);                     //return a reference to entry
//                  in the tree
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    T* find_ptr(const T& entry);                    //return a pointer to this key.
                                                //          NULL if not there.
    const T* find_ptr(const T& entry) const;
    
    Iterator find (const T& key)
    {
        if (!contains(key))
        {
            //Iterator notHere(NULL);
            return Iterator(nullptr);
        }
        else
        {
            //cout << "gets ere" << endl;

            T* temp = find_ptr(key);
            BPlusTree <T>* bagel = new BPlusTree<T>();
            bagel->insert(*temp);
            //return bagel;
            return Iterator(bagel);
            //cout << *temp << endl;
            // Iterator found(bagel);
            // return found;
        }



    }         
    //return an iterator to this key.
    //     NULL if not there.
    Iterator lower_bound(const T& key)
    {
        for (Iterator i = begin(); i != end(); i++)
        {

            if (*i >= key)
            {
                //cout << "enters equivalency op" << endl;
                return i;
            }
        }
        return Iterator (NULL);
    }  
    //return first that goes NOT BEFORE
    // key entry or next if does not
    // exist: >= entry
    Iterator upper_bound(const T& key)
    {
        for (Iterator i = begin(); i != end(); i++)
        {

            if (*i > key)
            {
                //cout << "return issue" << endl;
                return i;
            }   
        }
        return NULL;
    }  
    //return first that goes AFTER key
    Iterator begin() // works fine
    {
        return Iterator (get_smallest_node());
        //return iter;
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }
                                         //exist or not, the next entry  >entry
    int size() const;                           //count the number of elements
                                                //              in the tree
    bool empty() const;                         //true if the tree is empty

    bool is_valid();
                                                //print a readable version of
                                                //                  the tree
    void print_tree(int level = 0, ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }
    int subset_size () {return child_count;} //test function
    string pre_order();
    string post_order();
    string in_order();                          // traverse the tree in an
                                                // inorder fashion, return a 
                                                // string of all the data items
                                                // with vertical delimiters
    void loose_insert(const T& entry);


    ostream& list_keys(Iterator from = NULL, Iterator to = NULL)
    {
    if (from == NULL) from = begin();
    if (to == NULL) to = end();
    for (Iterator it = from; it != to; it++)
    cout<<*it<<" ";
    return cout;
    }
    void call_test()
    {
        
        cout << *get_smallest_node() << endl;
    }
    bool dups_ok;
private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

                                   //true if duplicate keys may be
    int data_count;                             //number of data elements
    T data[MAXIMUM + 1];                        //holds the keys
    int child_count;                            //number of children
    BPlusTree* subset[MAXIMUM + 2];                 //suBPlusTrees
    BPlusTree* next;
    bool is_leaf() const; //true if this is a leaf node

    //insert element functions
              //allows MAXIMUM+1 data
                                                //      elements in the root
    void fix_excess(int i);                     //fix excess of data elements
                                                //                  in child i

    //remove element functions:
    void loose_remove(const T& entry);          //allows MINIMUM-1 data
                                                //      elements in the root
    void fix_shortage(int i);                   //fix shortage of data elements
                                                //                  in child i

    void remove_biggest(T& entry);              //remove the biggest child of
                                                //          this tree->entry
    void rotate_left(int i);                    //transfer one element LEFT
                                                //              from child i
    void rotate_right(int i);                   //transfer one element RIGHT
                                                //              from child i
    void merge_with_next_subset(int i);         //merge subset i with subset
                                                //                      i+1
    BPlusTree<T>* get_smallest_node()
    {
        //BPlusTree<T>* temp;
        if (is_leaf())
        {
            //following return works fine:
            return this;
        }
        else
        {
            return subset[0]->get_smallest_node();
        }
    }
    void get_smallest(T& entry)
    {
        BPlusTree<T>* temp = get_smallest_node();
        entry = temp->data[0];
        return;
    }      //entry := leftmost leaf
    void get_biggest(T& entry)
    {
        return;
    }       //entry := rightmost leaf

    void transfer_left(int i)
    {

        return;
    }        //transfer one element LEFT from child i
    void transfer_right(int i)
    {
        return;
    }       //transfer one element RIGHT from child i

};

template <typename T>
bool BPlusTree<T>::is_valid()
{
    if (is_leaf())
    {
        if (data_count < MINIMUM || data_count > MAXIMUM)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else

    {
        if (child_count != data_count +1 || data_count < MINIMUM || data_count > MAXIMUM)
        {
            return false;
        }
        for (int i = 0 ; i< child_count; i++) //loop through all children
        {
            return subset[i]->is_valid();
        }
    }

}

template<typename T>
string BPlusTree<T>::pre_order()
{
    string temp = "";
    
    if (is_leaf())
    {
        for (int i = 0; i < data_count; i++)
        {
            temp += to_string(data[i]);
            temp += "|";
        }
        return temp;
    }
    for (int i = 0; i < child_count-1; i++)
    {   
        temp += to_string(data[i]);
        temp += "|";
        temp += subset[i]->pre_order();
    }
    temp += subset[child_count-1]->pre_order();

    return temp;
}

template <typename T>
string BPlusTree<T>::post_order()
{
    string temp = "";

    if (is_leaf())
    {

        for (int i = 0; i < data_count; i++)
        {
            temp+= to_string(data[i]);
            temp+= "|";
        }
        return temp;
    }
    temp+= subset[0]->post_order();
    for (int i = 1; i < child_count ; i++)
    {
        temp += subset[i]->post_order();
        if(i-1 < data_count && i >= 0)
        {
            temp+= to_string(data[i-1]);
            temp+= "|";
        }
        //cout<< i << endl;
    }
    //leftmost child is hte unwanted child in this situation
    return temp;
}

template <typename T>
T& BPlusTree<T>::get_existing(const T& entry)
{
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    if (is_leaf())
    {
        if (found)
        {
            return data[index];
        }
        else 
        {
            cout << "get_existing was called with a nonexistent entry" << endl;
            assert(found);
        }
    }
    if (found)
    {
        return subset[index+1]->get_existing(entry);
    }
    else
    {
        return subset[index]->get_existing(entry);
    }
}
template <typename T>
const T& BPlusTree<T>::get(const T& entry)const
{
    assert(!contains(entry));
    return *(find_ptr(entry));

}


template <typename T>
void BPlusTree<T>::print_tree(int level, ostream& outs) const
{
    //1. print the last child (if any)
    //2. print all the rest of the data and children
    //------------------------------------------------
    //cout << "in here" << endl;
    if (is_leaf())
    {
        for (int j = data_count-1; j >= 0; j--)
        {
            //cout << "in leaf" << endl;
            outs << setw(4 * level) <<" [" <<data[j] << "]" /*<< data_count << ":" << child_count*/ <<endl;
        }
        return;
    }
    subset[child_count-1]->print_tree(level+1, outs); //unwanted child
    for (int i = data_count-1; i >= 0; i--)
    {
        outs << setw(4 * level) <<" [" <<data[i] << "]" /*<< data_count << ":" << child_count*/ << endl; //prints out per index you are on
        subset[i]->print_tree(level+1, outs);// recurses on last line's index
    }


}

template<typename T>
BPlusTree<T>::BPlusTree(bool dups_ok)
{
    data_count = 0;
    child_count = 0;
    next = nullptr;
}

template<typename T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
{
    data_count = 0;
    child_count = 0;
    dups = false;
    next = nullptr;
    for (int i = 0; i < size; i++)
    {
        insert(a[i]);
    }
}


//big three:
template<typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{
    child_count = 0;
    data_count = 0;
    next = nullptr;
    copy_tree(other);
}


template<typename T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}   


template<typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS)
{
    // clear_tree();
    copy_tree(RHS);
    return *this;
}


template<typename T>
void BPlusTree<T>::insert(const T& entry)
{
    //cout << "dc: "  <<data_count << endl;
    //cout << "cc: "<<child_count <<  endl;
    
    //cout << "here?" << endl;
    loose_insert(entry);
    if (data_count > MAXIMUM) //only enters when root is in excess
    {
        //cout << "hihigh" << endl;
        BPlusTree<T>* temp  =  new BPlusTree<T>();
        copy_array(temp->data, data, temp->data_count, data_count);
        copy_array(temp->subset, subset, temp->child_count, child_count);
        //temp->next = next;
        data_count = 0;
        child_count = 1;
        //next = nullptr;
        
        subset[0] = temp;
        //cout << "butterfly" << endl;
        fix_excess(0);
        //cout << "poo shampoo" << endl;

    }
    
    //cout << data_count << endl;

    return;
}                
//insert entry into the tree


template<typename T>
void BPlusTree<T>::remove(const T& entry)
{
    if (contains(entry) == false)
    {
        cout << "doesnt contain!" << endl;
        
        return;
    }

    loose_remove(entry);
    if (data_count < MINIMUM && child_count > 0) //shrink
    {
        BPlusTree<T>* temp = subset[0];
        //copies into temp


        //copies into parent
        copy_array(data, temp->data, data_count, temp->data_count);
        copy_array(subset, temp->subset, child_count, temp->child_count);
        temp->child_count = 0;
        temp->data_count = 0;
        //cout << "dc in main remove: " << data_count << endl;
        delete temp;

    }

    //cout << "dc in main remove: " << data_count << endl;
    //cout << "cc in main remove: " << child_count << endl;
    return;
}                
//remove entry from the tree



template<typename T>
void BPlusTree<T>::clear_tree()
{
    data_count = 0;
    for (int i =0;i < child_count; i++)
    {
        subset[i]->clear_tree();
        delete subset[i];
        subset[i] = nullptr;
    }
    child_count = 0;
}                          
//clear this object
//  (delete all nodes etc.)



template<typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    //cout << "orig data[0]: " << other.data[0] << endl;
    //move into other copy
    clear_tree(); //student keeps on showing up just clear on every copy
    BPlusTree<T> *temp = nullptr;
    copy_tree (other, temp);


}      
//copy other into this object

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
{
    clear_tree();
    copy_array(data, other.data, data_count, other.data_count); //goes uppy here
    
    if (is_leaf()) //next only exists at leaves
    {
        if (last_node != nullptr) 
        { //only if there are pointers to copy :D
            last_node->next = this;
            last_node = this;
        }
        ///DONT RETURN FROM HERe - > needs to copy leaves too
        else
        {
            last_node = this; //this was causing seg faults
        }
    }
    // else 
    // { bad placement
    //     last_node = this;
    // }
    
    dups_ok = other.dups_ok; //ehh
    for (int i = 0; i < other.child_count; i++)
    {
        subset[i] = new BPlusTree <T>();
        subset[i]->copy_tree(*(other.subset[i]), last_node); //called it wrong last time
    }
    child_count = other.child_count; //this at end or else breaky breaky
}

template<typename T>
bool BPlusTree<T>::contains(const T& entry) const
{

    int index = first_ge(data, data_count, entry);

    if (is_leaf())
    {
        if (data[index] == entry)
        {
            return true;
        }
        else {
            return false;
        }
        
        //if anything breaks it was here
        // if (data[index] == entry)
        // {
        //     return true;
        // }
        // else
        // {
        //     return false;
        // }
    }
    else if (data[index] == entry)
    {
        return true;
    }
    else
    {
        return subset[index]->contains(entry);
    }
    return false;
}


template<typename T>
bool BPlusTree<T>::contains(const T& entry) 
{
    
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);
    if (found)
    {
        return true;
    }
    else if (!is_leaf() && index <= data_count)
    {
        return subset[index]->contains(entry);
    }
    return false;
}              
//true if entry can be found in
//                  the array


template<typename T>
T& BPlusTree<T>::get(const T& entry)
{
    //cout << "goes here instead" << endl;
    if (contains(entry))
    {
        return get_existing(entry);
    }
    else 
    {
        //cout << "checks in here" << entry << endl;
        insert(entry);
        return get_existing(entry);
    }
    
}                     
//return a reference to entry
//                  in the tree


template<typename T>                                           
T* BPlusTree<T>::find_ptr(const T& entry)
{
    int here = first_ge(data, data_count, entry);
    bool found = here < data_count && data[here] == entry;
    if (is_leaf() && here < data_count)
    {
        if (data[here] == entry)
        {
            return &data[here];
        }
    }
    else if (here <= data_count && is_leaf() == false)
    {
        return subset[here+found]->find_ptr(entry);
    }

    return nullptr;

}                    
//return a pointer to this key.
// NULL if not there.

template <typename T>
const T* BPlusTree<T>::find_ptr(const T& entry) const
{
    int here = first_ge(data, data_count, entry); //index to check
    if (is_leaf())
    {
        if (here < data_count && data[here] == entry)
        {
            //cout << "wat b here: " << *(&data[here]) << endl;
            return &data[here];
        }
    }
    else if (here <= data_count && data[here] != entry)
    {
        return subset[here]->find_ptr(entry);
    }


    return nullptr; // if nothing else
}


template<typename T>
int BPlusTree<T>::size() const
{
    int ct = 0;
    Iterator it = begin();
    for (; it != end(); it++)
    {
        ct++;
    }
    return ct;
}                           
//count the number of elements
//              in the tree



template<typename T>                                            
bool BPlusTree<T>::empty() const
{
    return data_count == 0 && child_count == 0;
}                         
//true if the tree is empty







template<typename T>
string BPlusTree<T>::in_order()
{
    string tree = "";
    if (is_leaf())
    {

        for (int i = 0; i< data_count; i++)
        {
            tree+=to_string(data[i]);
            tree+="|";
        }
        return tree;

    }

    for (int i = 0; i < child_count-1; i++)
    {
        
        tree+= subset[i]->in_order();

        tree+= to_string(data[i]);
        tree+= "|";
    }
    tree+=subset[child_count-1]->in_order();
    

    

    return tree;
}                          
// traverse the tree in an
// inorder fashion, return a 
// string of all the data items
// with vertical delimiters





//insert element functions


template<typename T>
void BPlusTree<T>::loose_insert(const T& entry)
{
    
    //cout << "hi" << endl;
    int index =  first_ge(data, data_count, entry);
    bool found = index < data_count && data[index] == entry;
    // if (index > data_count)
    // {
    //     return;
    // }

    if (is_leaf())
    {

        //cout << "entry: " << entry << endl;
        if (found == true)
        //if found, simply override <- dont do 
        {
            data[index] = data[index] + entry;
            return;
        }
        else
        {
            ordered_insert(data, data_count, entry);
        }
        //actual value, insert here
        //cout << "here" << endl;
        //cout << "dc: " <<data_count << endl;

        return;
    }
    subset[index+found]->loose_insert(entry);
    if (subset[index+found]->data_count > MAXIMUM)
    {
        fix_excess(index+found);
    }

    return;
}          
//allows MAXIMUM+1 data
//elements in the root



template<typename T>
void BPlusTree<T>::fix_excess(int i)
{ 
    int midpoint_index = subset[i]->data_count/2;

    //cout << midpoint_index << endl;
    BPlusTree<T>* temp = new BPlusTree<T>();

    // THIS GOES INTO PARENT (midpoint of the child)
    //int middle_index = first_ge(data, data_count, subset[i]->data[midpoint_index]);

    T item = subset[i]->data[midpoint_index];
    //cout << "cc: " << child_count << endl;

    //insert new BPlusTree into location i+1
    insert_item(subset, i+1, child_count, temp);
    //next = subset[i+1];

    //ordered_insert(subset, child_count, temp, i+1); 
    //cout << "test for 60: " << subset[2]->data[0];
    

    //split data
    split_array(subset[i]->data, temp->data,subset[i]->data_count,temp->data_count );
    
    //split subset
    split_array(subset[i]->subset, temp->subset,subset[i]->child_count, temp->child_count);

    //detach 
    //detach_item(subset[i]->data, subset[i]->data_count, subset[i]->data[data_count-1]);

    // [2]
    //[1][2] [3]
    //
    //dont forget to detach the moved up midpoint
    T deleted;
    detach_item(subset[i]->data, subset[i]->data_count, deleted );
    //delete_item(subset[i]->data, midpoint_index ,subset[i]->data_count, deleted);
    //cout << "deleted: " << deleted<< endl;

    if (subset[i]->is_leaf())
    {
        insert_item(subset[i+1]->data, 0 ,subset[i+1]->data_count, deleted);
        subset[i+1]->next = subset[i]->next;
        subset[i]->next = subset[i+1];
        //cout << "checking what its in my data: " << data[0] << endl;
        //cout << "assigning next in excess: " <<next->data[0] << endl;
    }
    ordered_insert(data, data_count, deleted);
    //cout << "assigning next in excess: " <<next->data[0] << endl;

    return;
}                     
//fix excess of data elements
//in child i
//remove element functions:


template<typename T>
void BPlusTree<T>::loose_remove(const T& entry)//entry will always be valid
{
    int here = first_ge(data, data_count, entry); //found (or not)
    T temp;

    // cout << "Here: " << here << endl;
    if (is_leaf() && here < data_count) //delete in index does not call remove max
    {
        // cout << "Bruh moment\n";
        delete_item(data, here, data_count, temp);
        return;
    }

    else if (!is_leaf() && data[here] == entry && here < data_count) //here calls remove_max to deal with it being inner_node or root
    {

        subset[here]->remove_biggest(temp); 
        data[here] = temp; //necessary? works?

    }

    else//recurse 
    {
        //cout << "Recursion moment\n";
        subset[here]->loose_remove(entry);

    }


    
    return;
}          
//allows MINIMUM-1 data
//elements  in the root


template<typename T>                                            
void BPlusTree<T>::fix_shortage(int i)
{

    if (subset[i]->data_count >= MINIMUM)
    {
        // cout << "subset" << i << "has sufficient data members and has returned" << endl;
        return;
    }
    //4 cases

    //1. borrow from left
    if (i > 0 && subset[i-1]->data_count > MINIMUM)
    {
        //cout << "Rotate right\n:";
        rotate_right(i);
    }


    //2.borrow from right
    else if (i < child_count-1 && subset[i+1]->data_count > MINIMUM)
    {
        rotate_left(i);
    }


    //3. merge with left
    else if (i > 0)
    {
        //cout << "merge with left" << endl;
        merge_with_next_subset(i-1);
        //merge(subset[i-1]->data, subset[i-1]->data_count, subset[i]->data,subset[i]->data_count);
    }


    //4. merge with right
    else
    {
        //cout << "merge wit right " << endl;
        merge_with_next_subset(i);
    }

    return;
}                   
//fix shortage of data elements
//                  in child i


template<typename T>
void BPlusTree<T>::remove_biggest(T& entry)
{
    
    if (is_leaf())
    {
        //cout << "in remove biggest leaf " << data_count << endl;
        delete_item(data, data_count-1, data_count, entry);
        // cout << "dc:" << data_count << endl;
        return;
    }
    int here = child_count-1;
    subset[here]->remove_biggest(entry);
    // cout << "subset I am going into to fix shortage: " << here << endl;
    // cout << "inside subset: " << subset[here]->data[0];

    fix_shortage(here);
    return;
}              
//remove the biggest child of
//          this tree->entry


template<typename T>
void BPlusTree<T>::rotate_left(int i)
{
    //cout << "rotate left" << endl;
    //want to grab leftmost item (0)from i+1 subset data
    // turn this into parent data [i]
    //grab parent data [i] and insert into subset[i] data

    T temp, parentTemp;
    BPlusTree<T>* subsetTemp;
    int grab_index = 0; //leftmost node of right tree index will always be 0
    bool move_ss = false; // only true if it isnt a leaf
    int insert_here = 0;
    if (subset[i]->data_count != 0) { insert_here = subset[i]->data_count-1;}
    if (!subset[i+1]->is_leaf())
    {
        move_ss = true;
    }
    delete_item(subset[i+1]->data, grab_index, subset[i+1]->data_count, temp); //
    delete_item(data, i, data_count, parentTemp);
    insert_item(data, i, data_count, temp); //insering into parent
    insert_item(subset[i]->data, insert_here, subset[i]->data_count, parentTemp);

    if (move_ss == true)
    {
        delete_item(subset[i+1]->subset, grab_index ,subset[i+1]->child_count, subsetTemp); //grab removed value's unwanted child
        insert_item(subset[i]->subset, subset[i]->child_count-1, subset[i]->child_count, subsetTemp);// plugs into < min subset
    }


    return;
}                    
//transfer one element LEFT
//              from child i


template<typename T>
void BPlusTree<T>::rotate_right(int i)
{
    //cout << "rotate right" << endl;
    //want to grab rightmost item (data_count-1) from i-1 subset
    //turn this into parent node i-1, copy parent node i-1 into temp
    //grab temp
    T temp, parentTemp;
    BPlusTree<T>* unwantedChildTemp; 
    int grab_index = subset[i-1]->data_count-1; //rightmost node of left tree index
    //cout << "rotate right" << endl;
    bool move_ss = false; //flag in case the leaf subset cannot be grabbed
    if (!subset[i-1]->is_leaf())
    {
        move_ss = true;
    }
    detach_item(subset[i-1]->data, subset[i-1]->data_count, temp); //this should store value?
    delete_item(data, i-1, data_count, parentTemp); //stores parent value 
    insert_item(data, i-1, data_count, temp); // plugs in the removed left tree rightmost value into parent
    insert_item(subset[i]->data, 0, subset[i]->data_count, parentTemp); //plugs into < min data
    
    if (move_ss == true)
    {
        detach_item(subset[i-1]->subset, subset[i-1]->child_count, unwantedChildTemp); //grab removed value's unwanted child
        insert_item(subset[i]->subset, 0, subset[i]->child_count, unwantedChildTemp);// plugs into < min subset
    }

    //deal with pointer here -- monkey brain way
    /*unwantedChildTemp = subset[i-1]->subset[child_count-1];
    subset[i-1]->child_count--;
    shift(subset[i]->subset, subset[i]->child_count,0);
    subset[i]->subset[0] = unwantedChildTemp;*/ 


    return;
}                   
//transfer one element RIGHT
//              from child i


template<typename T>
void BPlusTree<T>::merge_with_next_subset(int i)
{

    T temp;
    BPlusTree <T>* childTemp;
    //detach_item(data, data_count, temp);
    delete_item(data, i, data_count, temp); //delete parent @i 
    //cout << "dc after delete item: " << data_count << endl;
    //cout <<"cout temp in merge_with_next call: " <<temp << endl;
    attach_item(subset[i]->data, subset[i]->data_count, temp);
    //cout << "dc after insert item: " << subset[i]->data_count << endl;

    merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);
    //cout << "dc after merge: " << subset[i]->data_count << endl;
    merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
    // subset[i+1]->child_count = 0;
    delete_item(subset, i+1, child_count, childTemp);
    delete childTemp;
    //cout << "dc after delete item: " << subset[i]->data_count << endl;

    return;
}         
//merge subset i with subset
//                      i+1


template <typename T>
bool BPlusTree<T>::is_leaf() const
{
    if (child_count == 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}






#endif