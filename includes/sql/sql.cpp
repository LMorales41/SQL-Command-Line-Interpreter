#include "sql.h"

Table SQL::command(string commandline)
{
    //Table t;
    char s [500];
    strcpy(s, commandline.c_str());
    Parser prsr (s);
    //cout << "issue with table?" << endl;
    //prsr.get_parse_tree();
    // ptree.clear();
    ptree = prsr.parse_tree();
    //cout << "issue here?" << endl;
    // cout << "ptree in command :" << endl;
    // cout << ptree << endl;
    //ptree.print_lookup();
    string command = "command";
    // string table = "table_name";
    string moving;
    moving = ptree[command].at(0);
    //cout << "after [] .at" << endl;
    // cout << "N STUFF " << moving << endl;
    // string mysanity = ptree[table].at(0);
    // cout << "im going to cry" << mysanity << endl;
    _keep_track_table = run_command(moving);
    //cout << "after run command" << endl;
   // ptree.clear();
    return _keep_track_table;

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
    // cout << "using lookup:" << endl;
    // ptree.print_lookup();
    string tbl = "table_name";
    string tbl_name = ptree[tbl][0];
    //cout << "tbl name before anything else: " << tbl_name << endl;



    if (commandstr == "make" || commandstr == "create")
    {
        //make table
        //if its a table, we need  a name
        pkey = "table_name"; // my field table name will always have this key
        
        temp = ptree[pkey].at(0); //shoul only be one line 
        //cout << "in make table: " << temp << endl;
        pkey = "col";
        tempv = ptree[pkey];
        Table maket (temp, tempv);
        return maket;


    }
    else if (commandstr == "insert")
    {
        pkey = "table_name"; // my field table name will always have this key
        //cout << "insert at is not constructed properly" << endl;
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
        

        return t;
    }
    else if (commandstr == "select")
    {
        //select 
        pkey = "table_name"; // my field table name will always have this key
        // cout << "ptree in command call: " << endl;
        // cout << ptree << endl;
        temp = (ptree[pkey]).at(0); //shoul only be one line 
        // cout << "aaa: " <<temp << endl;
        pkey = "fields";
        tempv = ptree[pkey]; //i have vector of fields
        // cout << "wtf: " << endl;
        // cout << tempv.at(0) << endl;
        bool star = false;
        if (tempv[0] == "*")
        {
            star = true;
        }
        //cout << "in select: " << temp << endl;
        Table t (temp);
        
        // get into select
        // Table (temp);
        // call a select depending on no conditons/conditions
        // t.select(pass something in)
        // my priv table = t.select(pass something in)

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
    return _keep_track_table;
}

