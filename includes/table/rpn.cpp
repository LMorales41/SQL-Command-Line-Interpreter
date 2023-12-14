#include "rpn.h"
// testing purposes
// void RPN::check_maps()
// {
//     cout << "fieldmap: " << endl;
//     cout << fieldMap << endl;

//     cout << "indices (all 3 mmaps)" << endl;
//     for (int i = 0; i < indices.size(); i++)
//     {
//         cout << indices[i] << endl;
//     }
//     MMap<string, long>::Iterator itbegin =  indices[0].begin();
//     cout << "begin: " << endl;
//     cout << *itbegin << endl;
//     cout << " ++ : " << endl;
//     itbegin++;
//     cout << "after ++ : " << endl;
// }


//MUST pass by reference my b+ tre copy doesnt work
//ONLY call in table_select functions or it breaks cause of this
//lazy workaround for it to work outside of table functions is to create a table with the other tables bin file then delete?
    //too much work just clal only in selects
void RPN::do_rpn_thing(Map <string, long>& fieldMap, vector<MMap<string, long>>& indices)
{
    Token* temp;
    Token* temp2;
    Token* temp3;
    string fldname, unique, oper;
    Solution hold;
    // cout << "before loop in rpn thing: " << endl;
    // cout << "pfix size: " << postfix.size() << endl;
    int size = postfix.size();
    //cout << "size: " << postfix.size() <<endl;
    for (int i = 0 ; i < size; i++)
    {
        //cout << "pop" << endl;
        temp = (postfix.pop());
        //cout << "handling: " << temp->get_string() <<endl;
        if (temp->get_type() == TokenType::RELATIONAL)
        {
            //if this is a < or > etc
            //pop twice once I get this
            temp2 = solutionholder.pop();
            temp3 = solutionholder.pop();

            unique = temp2->get_string();
            fldname = temp3->get_string();
            oper = temp->get_string();
            // cout << "check strings im handing it: " << endl;
            // cout << "fldname : " << fldname << endl;
            // cout << "unique : " << unique << endl;
            // cout << "oper : " << oper << endl;
            //temp = new Solution (check_recnos(fieldMap, indices, fldname, oper, unique));
            temp =  new Solution;
            temp->set_records(check_recnos(fieldMap, indices, fldname, oper, unique));
            //hold.set_records(check_recnos(fieldMap, indices, fldname, oper, unique));
            solutionholder.push(temp); //solution is now inside the stack
        }
        else if (temp->get_type() == TokenType::LOGICAL)
        {
            vector<long> l1,l2, l3;
            temp2 = solutionholder.pop();
            temp3 = solutionholder.pop();
            //cout << "temp: " << temp->get_string() << endl;
            if (temp->get_string() == "and") //intersection
            {
                //cout << "intersection" << endl;
                l1 = temp2->get_records();
                l2 = temp3->get_records();
                // cout << "l1: " << l1.size() << endl;
                // cout << "l2: " << l2.size() << endl;
                // cout << "elements inside l1 : " << endl;
                // for (int z = 0; z < l1.size(); z++)
                // {
                //     cout << l1[z] << " ";
                // }
                // cout << endl;
                // cout << "elements inside l2 : " << endl;
                // for (int z = 0; z < l2.size(); z++)
                // {
                //     cout << l2[z] << " ";
                // }
                // cout << endl;
                
                for (int j = 0; j < l2.size(); j++) //goes through first vector
                {

                    //cout << "iterating thru l2: " << l2[j] << endl;
                    for (int k = 0; k < l1.size(); k++) //anything that matches shuold be added
                    {
                        //cout << "iterating thru l1" << l1[k] << endl;
                        if (l1[k] == l2[j]) 
                        {
                            l3.push_back(l2[j]); //l3 =  intersection
                        }
                    }
                }
                // cout << "l3 size : " << endl;
                // cout << l3.size() << endl;
                // for (int z = 0; z < l3.size(); z++)
                // {
                //     cout << l3[z] << " ";
                // }
                // cout << endl;
                //this puts intersection into the stack
                temp = new Solution (l3);
                solutionholder.push(temp);

                //this is for testing
                //sltn.set_records(l3);
            }
            else //union
            {
                //cout << "union" << endl;
                l1 = temp2->get_records();
                l2 = temp3->get_records();
                l3 = l1;
                for (int z = 0; z < l2.size(); z++)
                {
                    l3.push_back(l2[z]);
                }

                //using alogirthm library for these
                //cout << "l3 before sorting: " << l3.size() <<endl;
                sort(l3.begin(), l3.end());
                auto last = std::unique(l3.begin(), l3.end()); //last will be itr where the dups are pushed to
                l3.erase(last, l3.end()); //erases starting at last to end of vector
                // cout << "l3: " << endl;
                // for (int p=0; p < l3.size(); p++)
                // {
                //     cout << l3[p] << " ";
                // }
                // cout << endl;
                //this will only leave uniques
                //cout << "l3 after sorting: " << l3.size() << endl;
                //this puts intersection into the stack
                temp = new Solution (l3);
                solutionholder.push(temp);

                //this is for testing
                //sltn.set_records(l3);
            }
        }
        else 
        {
            solutionholder.push(temp);
        }
        
    }
    temp = solutionholder.pop();

    //cout << "i did something? " << endl;
    // vector<long> fortesting = temp->get_records();
    // cout << "fortesting size: " << endl;
    // cout << "items inisde the vector: " << endl; 
    // for (int i = 0; i < fortesting.size(); i++)
    // {
    //     cout <<  fortesting[i] << " ";
    // }
    // cout << endl;
    sltn.set_records(temp->get_records());
}


//MUST pass as reference, b+tree copy doesnt copy over iterators currently
        //if I can implement with copied linked list then reference not needed
vector<long> RPN::check_recnos (Map <string, long>& fieldMap, vector<MMap<string, long>>& indices, string field, string oper, string otherField)
{
    int index = fieldMap.get(field);
   // cout << "it will check this position in the mmap vector for the recnos : " << index << endl;
    
    MMap<string, long>::Iterator itr; //this will help for >, < to serve as our sig value
    MMap<string, long>::Iterator itbegin =  indices[index].begin(); //start of the itr
    //cout << "the field at this position is: " <<  *(itbegin) << endl;
    //these functions will populate field_recnos with recnos
    //these recnos are locations in our bin file where we find the records
    vector <long> field_recnos;
    if (oper == "=") 
    {
        //cout << otherField << endl;
        //cout << "my ex wife also hates the = operator" << endl;
        field_recnos = indices[index].at(otherField); //returns value lists where key = otherField
    }
    else if (oper == ">")
    {
        //ex. I want all indices where ages > otherField (im in this mmap already cause of int index)
        // for loop..?

        // gives an iterator to first spot where the key is > otherField
        //cout << "in greater than " << endl;
        //cout << otherField << endl;
        //cout << "mmap in indices[index] : " << indices[index] << endl;
        itr = indices[index].upper_bound(otherField); 
        //cout << "dereferenced itr ";
        //cout << *(itr) <<endl;
        
        for (; itr != indices[index].end(); itr++) //goes through all iterators greater than
        {
            MPair <string, long> temp = *(itr);
            for (int i = 0; i < temp.value_list.size(); i++) //goes through all vectors of mpairs
            {
                field_recnos.push_back(temp.value_list[i]); //pushes back values one by one
            }

        }
        //sort vector afterwards?
        
    }
    else if (oper == "<")
    {
        //ex. i want all indices where lname < otherField
        //i hate the french 
        itr = indices[index].upper_bound(otherField); 
        for (; itbegin != itr ; itbegin++) //starts at beginning, goes up TO the spot where its greater than
        {
            
            MPair <string, long> temp = *(itbegin);
            if (temp.key == otherField) //used to stop upper bound shenanigans
            {
                break;
            }
            for (int i = 0; i < temp.value_list.size(); i++) //goes through all vectors of mpairs
            {
                field_recnos.push_back(temp.value_list[i]); //pushes back values one by one
            }
        }
    }
    else if (oper == "<=" )
    {
        //first assign the equals to - then fill with less than 
        //field_recnos = indices[index].at(otherField);
        // ^this doesnt work it goes out 
            //of order for this
                //specific operator


        
        itr = indices[index].upper_bound(otherField); 
        for (; itbegin != itr ; itbegin++) //starts at beginning, goes up TO the spot where its greater than
        {
            MPair <string, long> temp = *(itbegin);
            if (temp.key == otherField) //used to stop with upper bound shenanigans
            {
                break;
            }
            for (int i = 0; i < temp.value_list.size(); i++) //goes through all vectors of mpairs
            {
                field_recnos.push_back(temp.value_list[i]); //pushes back values one by one
            }
        }
        //pushes back this vector at the end, same as assigning it but should do this in the correct order now
        vector<long> tempv = indices[index].at(otherField);
        for (int i = 0; i < tempv.size(); i++)
        {
            field_recnos.push_back(tempv[i]);
        }


        
        //then I want to push back the ones that are less than then I want to sort the vector

    }
    else if (oper == ">=")
    {
        //first take equals to - then insert the greater thans
        field_recnos = indices[index].at(otherField);
        itr = indices[index].upper_bound(otherField); 
        for (; itr != indices[index].end(); itr++) //goes through all iterators greater than
        {
            MPair <string, long> temp = *(itr);
            for (int i = 0; i < temp.value_list.size(); i++) //goes through all vectors of mpairs
            {
                field_recnos.push_back(temp.value_list[i]); //pushes back values one by one
            }
        }
        //then I want to push back the ones that are greater than and then i want to sort the vector

    }

    return field_recnos;
}


//maybe just set it to a private variable Solution's vector<long> ?
//this still technically works

//change this when actually doing the thing but for now its testing
vector<long> RPN::get_solution() //pops last value in solutionholder and returns that Solution's vectorlong
{
    // Solution sln;
    // sln.set_records(solutionholder.pop()->get_records());
    
    // return sln.get_records();

    return sltn.get_records();
    // vector <long> templ;

    // return templ;
    
}