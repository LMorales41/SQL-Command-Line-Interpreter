#ifndef linkedlistfunctionsTemplated_h
#define linkedlistfunctionsTemplated_h
#include "../node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);


//DEFINITIONS


//Linked List General Functions:
template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this)
{
    // this is previous code
    //give head a value at beginning to do linkedlist differently
    //cout << "amogus head" << endl;
    node<T>* nNode = new node<T>;
    nNode->_item = insert_this;
    nNode->_next= head;

    if (head == nullptr) //if head is only declared, no linked list yet built
    {
        head = nNode;
    }
    else { //else if list is pointing to existing node
        // nNode->_next= head;
        head->_prev = nNode; // previous node gets current node address
        head = nNode;
    } 
    return head;
    //end of previous code
}
//6224159
template <typename T>
void _print_list(node<T>* head)
{
    node<T>* ptr = head;
    while (ptr!= NULL)
    {
        //cout << ptr->_item << " "; //prints list flat out
        cout << *ptr << " "; //prints list with pointer thingies
        ptr = ptr->_next;
    }
    cout << endl;
}
//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    //function can be simplified if the key will always be in list
    //otherwise must include not found test case
    node<T>* ptr = head;
    bool found = false; // needed in case value is not found
    while (ptr!= NULL)
    {
        if (ptr->_item == key) // if pointed at object has the key in item
        {
            found = true; //set boolean flag
            break;
        }
        ptr = ptr->_next;
    }
    if (ptr == NULL && found == false)
    {
        return NULL; //only happens if value is not found
    }
    return ptr; // if found this will output instead
}




//insert after ptr: insert head if marker null
template <typename T> 
node<T>* _insert_after(node<T>*& head,node<T>* after_this, T insert_this)
{
    
    if (head == nullptr)
    {
        //cout <<  "choerry soda" << endl;
        head = _insert_head(head, insert_this);
        return head;
    }
    else 
    {
        node<T>* nNode = new node<T>;
        //cout << "pink lemonade" << endl;
        nNode->_item = insert_this; //copies value into item
        nNode->_next = after_this->_next; //sets nNodes next to be selected node's old next
        after_this->_next = nNode;// sets nNode as selected node's new next
        nNode->_prev = after_this; //sets nNode's prev as selected node
        return nNode;//returns inserted
    }
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,node<T>* before_this,T insert_this)
{
    
    if (head == nullptr)
    {
        _insert_head (head, insert_this);
        return head;
    }
    node<T>* nNode = new node<T>;
    nNode->_item = insert_this;

    if (!before_this->_prev) //if this is at front
    {
        before_this->_prev = nNode;
        head = nNode;
        nNode->_next = before_this;
    }


    else
    {
        nNode->_prev = before_this->_prev;
        before_this->_prev->_next = nNode;
        before_this->_prev = nNode;
        nNode->_next = before_this;

    }

    return nNode;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this)
{
    T temp = delete_this->_item; //copy item before deleting node
    node<T>* ptr = head;
    //node<T>* temp;
    while(ptr != NULL)
    {
        if (ptr->_item == delete_this->_item)
        {
            ptr->_prev->_next = ptr->_next;
            delete ptr;
            return temp;
        }
        ptr = ptr->_next;
    }
    return temp;
}
// write in _remove_head
//unsure how test is supposed to look
template <typename T>
node<T>* _remove_head(node<T>*& head){
    // if empty
    node<T>* temp;
    if (head == nullptr)
    {
        return nullptr;
    }


    if (head->_next == nullptr) //if only one element is in head
    {
        delete head;
        head = nullptr;
    }
    else
    {
        temp = head;
        head =head->_next;
        head->_prev = nullptr; //changing the prev of the new head node
        delete temp;
        temp = nullptr;
    }
    return head;
}



//duplicate the list...
template <typename T> //focus
node<T>* _copy_list(node<T>* head)
{//return last node of destination
    node<T>* temp = head;

    if (head == nullptr)
    {
        return nullptr;
    }
    node<T>* copy_into = new node <T>; //create new list here?
    copy_into->_item = temp->_item;
    node<T>* temp2; //to iterate through second list
    temp2 = copy_into;


    while (temp != nullptr)
    {
        temp2 = _insert_after(copy_into, temp2, temp->_item);
        //iterate through list 

        //will automatically insert into after list, no iteration needed for copy_into
        //temp2 =temp2->_next;
        temp = temp->_next;
    }
    return _remove_head(temp2); //remove first item inserted as it should be double
    //return nullptr;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    node<T>* ptr = src;
    node <T>* inserted;
    if (src == nullptr) //empty? list should be copied as empty?

    {
        _clear_list(dest);

        dest = nullptr;
        return dest; 

    }

    while (ptr != nullptr)
    {
        // inserted is returned into so that after_this
        // can be updated
        inserted = _insert_after(dest, inserted, ptr->_item); 
        ptr = ptr->_next;
    }
    return inserted;


    // THIS WORKS
    //cout << *ptr << endl;
    //cout << "amogus" << endl;
    /*node<int>* nNode;
    nNode = new node<int>;
    nNode->_item = ptr->_item;
    nNode->_next = nullptr;
    dest = nNode;
    ptr = ptr->_next;
    node<int>* walker = nNode;
    while (ptr != NULL)
    {
        nNode = new node<int>;
        nNode->_item = ptr->_item;
        nNode->_next = nullptr;
        walker->_next = nNode; //old nNode->_next = nNode;
        
        walker = walker->_next;
        ptr = ptr->_next;
    }
    return walker;*/
}



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    node<T>* ptr = head;
    //node<T>* temp;
    /*cout << "baby shark" << endl;
    cout << *ptr << endl;
    cout << "mommy shark" << endl;*/
    //ptr = ptr->_next;
    while (ptr!= NULL)
    {
        delete ptr; //delete each node as we traverse the list
        ptr = ptr->_next;
    }
    //cout << *ptr << endl;
    //cout << "enderman" << endl;
    
    head = nullptr; // make sure to set head to nullptr in case we want to initialize another list
    // also avoids memory errors from deleting
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    node<T>* ptr = head;
    for (int i = 1; i < pos; i++)
    {
        ptr = ptr->_next;
    }
    return ptr->_item;
}

#endif