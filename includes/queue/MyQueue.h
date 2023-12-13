#ifndef MyQueue
#define MyQueue

#include "../node/node.h"


using namespace std;
template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               
        //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                         
         //default ctor
        Iterator(node<T>* p)
        {
            _ptr = p; //set equal to the value passed in (location of p)
        }                            //Point Iterator to where
        //  p is pointing to
        T operator *()
        {
            return _ptr->_item;
        }    //dereference operator
        bool is_null()
        {
            return _ptr == NULL;
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,const Iterator& right)  //true if left == right
        {
            left._ptr == right._ptr;
        }


        Iterator& operator++()
        {                         //member operator:++it
        // or ++it = new_value
            if (_ptr->_next != NULL)
            {
                _ptr = _ptr->_next;
            }
            
            return *this;                       
            
        }

        friend Iterator operator++(Iterator& it,int unused)
        {         //friend operator: it++
            assert(it._ptr != NULL);
            Iterator iter = it;

            it._ptr = it._ptr->_next;
            
            return iter;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue()
    {
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }

    Queue(const Queue<T>& copyMe)
    {
        _front =  nullptr;
        _rear =  nullptr;
        _size = 0;

        _copy_list(_front, copyMe._front);
        _size = copyMe._size;
        _rear = copyMe._rear;
    }
    ~Queue()
    {
        _clear_list(_front);
        _size = 0;
        _rear = nullptr;
        _front = nullptr;
    }
    Queue& operator=(const Queue<T>& RHS)
    {
        if (&RHS == this)
        {
            return *this;
        }
        _clear_list(_front);
        _copy_list(_front, RHS._front);
        _size = RHS._size;
        _rear = RHS._rear;
        return *this;
    }

    bool empty()
    {
        return _size == 0;
    }
    T front()
    {
        T temp = _front->_item;
        return temp;
    }
    T back()
    {
        T temp = _rear->_item;
        return temp;
    }

    void push(T item)
    {//FIFO
        _rear = _insert_after(_front, _rear, item);
        _size++;
    }
    T pop()
    {
        T temp = _front->_item;
        if (_size == 0)
        {
            return T(); //cant assign anythig to temp
        }
        _remove_head(_front);
        _size--;

        if (_size == 0)
        {
            
            _rear = nullptr;
            _front = nullptr;
            //_size = 0;
            
        }

        return temp;
    }

    Iterator begin() const
    {
        return _front;
    }                                     //Iterator to the head node
    Iterator end() const
    {
        return NULL;
    }                                       //Iterator to NULL
    void print_pointers()
    {
        _print_list(_front);
        return;
    }
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe)
    {
        //_print_list(_front);
        node<T>* ptr = printMe._front;
        while (ptr != NULL)
        {
            outs << ptr->_item;
            outs << " ";
            ptr = ptr->_next;
        }
        outs << endl;
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

#endif