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
                l1 = temp2->get_records();
                l2 = temp3->get_records();

                
                for (int j = 0; j < l2.size(); j++) //goes through first vector
                {

                    for (int k = 0; k < l1.size(); k++) //anything that matches shuold be added
                    {

                        if (l1[k] == l2[j]) 
                        {
                            l3.push_back(l2[j]); //l3 =  intersection
                        }
                    }
                }
                temp = new Solution (l3);
                solutionholder.push(temp);

                // cout << "field1: " <<temp2->get_string() << endl;
                // cout << "field2: " << temp3->get_string() << endl;
                // cout << "l3:" << endl;
                // for (int p = 0; p < l3.size(); p++)
                // {
                //     cout << l3[p] << " ";
                // }
                // cout << endl;


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

                sort(l3.begin(), l3.end());
                auto last = std::unique(l3.begin(), l3.end()); //last will be itr where the dups are pushed to
                l3.erase(last, l3.end()); //erases starting at last to end of vector

                temp = new Solution (l3);
                solutionholder.push(temp);

            }
        }
        else 
        {
            solutionholder.push(temp);
        }
        
    }
    temp = solutionholder.pop();

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
    vector <long> field_recnos;
    if (oper == "=") 
    {
        field_recnos = indices[index][otherField]; //returns value lists where key = otherField
    }
    else if (oper == ">")
    {
        itr = indices[index].upper_bound(otherField); 
        
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
        itr =  indices[index].upper_bound(otherField); 
        for (; itbegin!= itr; itbegin++) //starts at beginning, goes up TO the spot where its greater than
        {
            MPair <string, long> temp = *(itbegin);
            for (int i = 0; i < temp.value_list.size(); i++) //goes through all vectors of mpairs
            {
                field_recnos.push_back(temp.value_list[i]); //pushes back values one by one
            }
        }

    }
    else if (oper == ">=")
    {// lower bound is >=
        itr = indices[index].lower_bound(otherField); 
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
    return sltn.get_records();
}