#include "sql.h"

Table SQL::command(string commandline)
{
    //Table t;
    char s [500];
    strcpy(s, commandline.c_str());
    Parser prsr (s);

    //prsr.get_parse_tree();
    ptree = prsr.parse_tree();
    // cout << "ptree in command :" << endl;
    // cout << ptree << endl;
    //ptree.print_lookup();
    string command = "command";
    // string table = "table_name";
    string moving;
    moving = ptree[command].at(0);
    // string mysanity = ptree[table].at(0);
    // cout << "im going to cry" << mysanity << endl;
    return run_command(moving);
    

    //return t;
}


Table SQL::run_command(string commandstr)
{
    string temp;
    string pkey;
    vector<string>tempv;
    vector<string>tempvi;
    // cout << "ptree in run command: " << endl;
    // cout << ptree << endl;
    // pkey = "table_name";
    // vector<string> tempp = ptree[pkey];
    // string tbl_name = tempp[0];

    //cout << "tbl name before anything else: " << tbl_name << endl;
    //ptree.print_lookup();
    //string test = "table_name";
    //cout << ptree[test].at(0) << endl;
    if (commandstr == "make" || commandstr == "create")
    {
        //make table
        //if its a table, we need  a name
        pkey = "table_name"; // my field table name will always have this key
        
        temp = ptree[pkey].at(0); //shoul only be one line 
        cout << "in make table: " << temp << endl;
        pkey = "col";
        tempv = ptree[pkey];
        Table maket (temp, tempv);
        return maket;
        // if (ptree.contains(pkey)) //not everyone will have more than one arg
        // {
        //     tempv = ptree[pkey];
        //     Table maket (temp, tempv);
        //     return maket;
        // }
        // else  //same thing as the one later 
        // //accounts for no conditions being passed in aka one arg
        // {
        //     Table maket (temp);
        //     recnos = maket.select_recnos();
        //     return maket;
        // }
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
        //cout << "in select: " << temp << endl;
        Table t (temp);
        


        //not all selects will have conditions
        pkey = "condition"; 
        if (!ptree.contains(pkey)) //no conditions means just return all
        {
            cout << "There is no condition." << endl;
            if (star == true)
            {
                //cout << "i need to change fields" << endl;
                _keep_track_table = t.select_all();
                _recnos = t.select_recnos();
                return _keep_track_table;
            }
            else
            {
                _keep_track_table = t.select(tempv);
                _recnos = t.select_recnos();
                return _keep_track_table;
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

        _keep_track_table = t.select(tempv, tempvi);
        _recnos = t.select_recnos();
        return _keep_track_table;
        


    }
    Table t;
    return t;
}

