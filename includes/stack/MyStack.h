#ifndef MyStack
#define MyStack
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}            //default ctor
        Iterator(node<ITEM_TYPE>* p){_ptr = p;}      //Point Iterator to where
                                            //  p is pointing to
        ITEM_TYPE operator *(){//return *_ptr; //doesnt work?
                                return _ptr->_item;}    //dereference operator
        bool is_null(){return _ptr == NULL;}            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){                        //member operator:++it
        //increment, return the one incremented

            if (_ptr != NULL)
            {
                _ptr = _ptr->_next;
            }
            return *this;                                               // or ++it = new_value
        }

        friend Iterator operator++(Iterator& it, 
                                   int unused){        //friend operator: it++
                                   //increment then return the one before
            assert(it._ptr!=NULL);
            Iterator iter = it;
            it._ptr = it._ptr->_next;
            return iter;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };
    Stack(node<ITEM_TYPE>* top = nullptr, int size = 0 ):_top(top), _size(size) {}
    Stack(const Stack<ITEM_TYPE>& copyMe)
    {
        _top = nullptr;
        _size = 0;
        //cout << "here" << endl;
        /*if (this == copyMe) //if equivalent do not copy
        {
            
        }
        else
        {*/
        _copy_list(_top, copyMe._top);
        _size = copyMe._size;
        //cout << "here" << endl;
        //}
    }
    ~Stack()
    {
        _clear_list(_top); //list gone
        _size = 0;   
    }
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS)
    {
        _copy_list(_top, RHS._top);
        _size = RHS._size;
        return *this;
    }
    ITEM_TYPE top()
    {
        return _top->_item;
    }
    bool empty()
    {
        if (_size == 0)
        {
            return true;
        }
        else 
        {
            return false;
        }
        
    }
    void push(ITEM_TYPE item)
    {
        //item passed in
        _insert_head(_top, item); //inserts at head for stack
        _size++;
    }
    ITEM_TYPE pop() //Item type ~ ~ is like <T>
    {
        //remove after (can be top/tail depending on Last in first out/first in first out)
        if (_size == 0) //empty
        {
            return ITEM_TYPE(); //return nothing?
            //issue if called here
        }

        ITEM_TYPE temp = _top->_item; //store the popped item
        _top = _remove_head(_top); //pop the stack
        _size--;
        //return _remove_head(_top); //returns the remove function
        return  temp;
    }
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe)
    {
        node<T>* temp = printMe._top; //change value to itereate through entire stack
        while (temp != nullptr)
        {
            outs << "[";
            outs << temp->_item;
            outs << "]";
            temp = temp->_next;
        }
        //outs<<"["<<printMe<<"]->";
        return outs;
    }
    Iterator begin() const{return _top;}                  //Iterator to the head node
    Iterator end() const
    {return nullptr;}                    //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

#endif