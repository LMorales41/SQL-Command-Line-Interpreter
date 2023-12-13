#include "sql.h"

Table SQL::command(string commandline)
{
    //Table t;
    char s [300];
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
    if (ptree.contains(command))
    {
        moving = ptree[command].at(0);
    }
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
    Table t;
    if (commandstr == "make")
    {
        //make table
        //if its a table, we need  a name
        pkey = "table_name"; // my field table name will always have this key
        temp = ptree[pkey].at(0); //shoul only be one line 
        pkey = "col";
        if (ptree.contains(pkey)) //not everyone will have more than one arg
        {
            tempv = ptree[pkey];
        }
        else  //same thing as the one later 
        //accounts for no conditions being passed in aka one arg
        {
            Table maket (temp);
            recnos = maket.select_recnos();
            return maket;
        }
        //now I have all things necessary for make command
        //  - the command, the table name, and the vector of fields
        // now i build it
        Table maket(temp, tempv);
        recnos = maket.select_recnos();
        return maket;

    }
    else if (commandstr == "insert")
    {
        //insert into
        pkey = "table_name"; //grabs name next
        temp = ptree[pkey].at(0); //should only be one item 
        pkey = "values"; //grabs conditions next
        tempv = ptree[pkey]; //vector of conditions


        //now call insert_into
        Table inser_tt(temp); //should already exist so only 1 arg
        inser_tt.insert_into(tempv);
        recnos = inser_tt.select_recnos();
        return inser_tt;

    }
    else if (commandstr == "select")
    {
        //select 
        pkey = "fields";
        tempv = ptree[pkey]; //i have vector of fields

        pkey = "table_name";
        temp = ptree[pkey].at(0); //should be simple name
        Table selct(temp); //1 arg bc it should already exist



        //not all selects will have conditions
        pkey = "condition"; 
        if (!ptree.contains(pkey)) //no conditions means just return all
        {
            return selct.select_all();
        }

        tempvi = ptree[pkey]; //should have conditions here
        //now we call selects based off what we have

        return selct.select(tempv, tempvi);
        


    }
    return t;
}

