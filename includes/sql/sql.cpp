#include "sql.h"

Table SQL::command(string commandline)
{
    //Table t;
    char s [500];
    strcpy(s, commandline.c_str());
    Parser prsr (s);
    ptree = prsr.parse_tree();
    //ptree.print_lookup();
    get_keys();
    // for (int i = 0 ; i < keys.size(); i++)
    // {
    //     cout << keys[i] << " ";
    // }
    string command = "command";
    string moving;
    moving = ptree[command].at(0);
    return run_command(moving);
    

    //return t;
}

void SQL::get_keys()
{
    string check; 
    //can just be a const this is bad

    vector<string> temp = {"col", "command", "condition", "fields", "table_name", "values", "where"};
    for (int i = 0; i < temp.size(); i++)
    {
        check = temp[i];
        if (ptree.contains(check))
        {
            keys.push_back(check);
        }
    }
}

Table SQL::run_command(string commandstr)
{
    string temp, tempop, tempoth;
    string pkey;
    vector<string>tempv;
    vector<string>tempvi;
    if (commandstr == "make" || commandstr == "create")
    {
        //make table
        //if its a table, we need  a name
        pkey = "table_name"; // my field table name will always have this key
        temp = ptree[pkey].at(0); //shoul only be one line 
        pkey = "col";
        if (ptree.contains(pkey)) //not everyone will have more than one arg
        {
            tempv = ptree[pkey];
            Table maket (temp, tempv);
            return maket;
        }
        else  //same thing as the one later 
        //accounts for no conditions being passed in aka one arg
        {
            Table maket (temp);
            recnos = maket.select_recnos();
            return maket;
        }
        // cout << "checking col : " << tempv.size() <<endl;
        // for (int i = 0; i < tempv.size(); i++)
        // {
        //     cout << tempv[i] << ",";
        // }
        // cout << endl;
        //now I have all things necessary for make command
        //  - the command, the table name, and the vector of fields
        // now i build it


    }
    else if (commandstr == "insert")
    {
        //Table t;
        pkey = "table_name"; // my field table name will always have this key
        temp = ptree[pkey].at(0); //shoul only be one line 
        Table t(temp);
        //insert into 
        pkey = "values"; //grabs conditions next $lname, $fname, etc
        tempv = ptree[pkey]; //vector of conditions

        // cout << "checking values: " << endl;
        // for (int i = 0; i < tempv.size(); i++)
        // {
        //     cout << tempv[i] << " ";
        // }
        // cout << endl;


        //now call insert_into
        t.insert_into(tempv);
    }
    else if (commandstr == "select")
    {
        //select 
        pkey = "table_name"; // my field table name will always have this key
        temp = ptree[pkey].at(0); //shoul only be one line 
        
        pkey = "fields";
        tempv = ptree[pkey]; //i have vector of fields
        bool star = false;
        if (tempv[0] == "*")
        {
            star = true;
        }

        Table t (temp);
        


        //not all selects will have conditions
        pkey = "condition"; 
        if (!ptree.contains(pkey)) //no conditions means just return all
        {
            cout << "There is no condition." << endl;
            if (star == true)
            {
                cout << "i need to change fields" << endl;
                return t.select_all();
            }
            else
            {
                return t.select(tempv);
            }
            
        }

        // cout << "checking fields: " << endl;
        // for (int i = 0; i < tempv.size(); i++)
        // {
        //     cout << tempv[i] << " ";
        // }

        tempvi = ptree[pkey]; //should have conditions here
        // cout << "checking conditions:" << endl;
        // for (int i = 0; i < tempvi.size(); i++)
        // {
        //     cout << tempvi[i] << " ";
        // }
        // cout << endl;
        
        //now we call selects based off what we have
        if (star == true)
        {
            tempv = t.get_fields();
        }
        
        return t.select(tempv, tempvi);
        


    }
    Table t;
    return t;
}

