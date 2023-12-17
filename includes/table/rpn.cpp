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
                //pretty vectors make my debugger go wow! what a wonderful world
                sort(l1.begin(), l1.end());
                sort(l2.begin(), l2.end());
                l3 = and_function(l1, l2);

                temp = new Solution (l3);
                solutionholder.push(temp);
            }
            else //union
            {
                //cout << "union" << endl;
                l1 = temp2->get_records();
                l2 = temp3->get_records();
                //viewbot porpoises
                sort(l1.begin(), l1.end());
                sort(l2.begin(), l2.end());
                l3 = or_function(l1, l2);

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



vector <long> RPN::or_function(vector<long> first, vector<long> second)
{
    //cout << "inside or func" << endl;
    vector<long> myunion;
    //cases first
    // cout << "first:" << endl;
    // for (int u = 0; u < first.size(); u++)
    // {
    //     cout << first[u] << " ";
    // }
    // cout << endl;
    // cout << "second:" << endl;
    // for (int u = 0; u < second.size(); u++)
    // {
    //     cout << second[u] << " ";
    // }
    if (first.size() == 0)
    {
        myunion = second;
        // return myunion;
    }
    else if (second.size() == 0)
    {
        myunion = first;
        // return myunion;
    }
    else if (first.size()==0 && second.size() == 0)
    {
        // return myunion;
    }
    else
    { 
        bool flag = false;
        for (int z = 0; z < first.size(); z++)
        {   
            myunion.push_back(first[z]);
        }
        for (int i = 0; i < second.size(); i++)
        {
            //myunion.push_back(second[i]);
            for (int j = 0; j< myunion.size(); j++)
            {
                if (second[i] == myunion[j]) //iterates through entire vector if true thenn
                {
                    flag = true;
                }
                    //only push back if not found (no matchings)

            }
            if (flag == true)
            {
                //myunion.push_back(second[i]);
                flag = false;
            }
            else
            {
                myunion.push_back(second[i]);
            }


        }


        //filter_repeats(myunion);
        // return myunion;
    }
    // cout << endl <<"myunion: " << endl;
    // for (int i =0 ;i< myunion.size();i++)
    // {
    //     cout << myunion[i] <<  " ";
    // }
    // cout << endl;
    //for easier debug
    sort(myunion.begin(), myunion.end());
    return myunion;
}

vector<long> RPN::and_function(vector<long> first, vector<long> second)
{
    //cout << "inside and func" << endl;
    vector<long> intersection;

    //cout << endl;
    //shitty code
    
    get_bigger_first(first, second);
    //cout << "first:" << endl;
    // for (int u = 0; u < first.size(); u++)
    // {
    //     cout << first[u] << " ";
    // }
    // cout << endl;
    // cout << "second:" << endl;
    // for (int u = 0; u < second.size(); u++)
    // {
    //     cout << second[u] << " ";
    // }

    for (int j = 0; j < first.size(); j++) //goes through first vector
    {
        for (int k = 0; k < second.size(); k++) //anything that matches shuold be added
        {

            if (first[j] == second[k]) 
            {
                intersection.push_back(second[k]);
            }
        }
    }
    // cout << endl << "my intersection: " << endl;
    // for (int i = 0; i < intersection.size(); i++)
    // {
    //     cout << intersection[i] << " ";
    // }
    // cout << endl;
    //viewing purples
    sort (intersection.begin(), intersection.end());
    return intersection;
}

void RPN::get_bigger_first(vector<long>& one, vector<long>& two)
{
    //make first the biggest
    vector<long> biggertemp;
    vector<long> smallertemp;
    if (one.size() > two.size())
    {
        //nothing to do! first is biggest thats all that matters for this loop
    }
    else
    {
        //hold values
        biggertemp = two;
        smallertemp = one;

        //now swap (can be done with less im just parannoid)
        one = biggertemp;
        two = smallertemp;
    }
}

void RPN::filter_repeats(vector<long>& vec)
{
    
}