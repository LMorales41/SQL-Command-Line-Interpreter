#include "sql.h"

Table SQL::command(string commandline)
{
    //Table t;
    char s [300];
    strcpy(s, commandline.c_str());
    Parser prsr (s);
    ptree = prsr.get_parse_tree();
    string command = ptree["command"][0];
    cout << "ptree: "<< endl <<ptree << endl;
    // cout << "name w get: " << ptree.get("table_name") << endl;
    // cout << "name: " <<ptree["table_name"] << endl;
    if (command == "make" || command == "create")
    {
        string name_m =  ptree["table_name"][0];
        vector<string> col = ptree["col"]; //returns a vetor by default
        //make the tabel

        Table t (name_m, col);
        ptree.clear();
        _keep_track_table = t;
        return _keep_track_table;
    }
    else if (command == "insert")
    {
        string name_i = ptree["table_name"][0];
        vector<string>values = ptree["values"]; //returns vectori
        //now create a table insert into then assign it to my priv table
        ptree.clear();
        Table t (name_i);
        t.insert_into(values);
        _keep_track_table = t;
        return _keep_track_table;
    }
    else if (command == "select")
    {
        //cout << ptree << endl;
        //string name_s = ptree["table_name"][0];
        string name_s = ptree.get("table_name").at(0);
        Table t (name_s);
        vector<string> fields = ptree["fields"]; //check for star
        bool starflag = false;
        if (fields[0] == "*")
        {
            starflag = true;
        }

        //condition check
        if (!ptree.contains("condition"))
        {
            ptree.clear();
            cout << "There is no condition" << endl;
            if (starflag == true)
            {
                _keep_track_table = t.select_all();
                _recnos = t.select_recnos();
                
                return _keep_track_table;
            }
            else
            {
                _keep_track_table = t.select(fields);
                cout << ptree << endl;
                _recnos = t.select_recnos();
                return _keep_track_table;
            }
        }

        else
        {
            vector<string> conditions = ptree["condition"];
            if (starflag == true)
            {
                fields = t.get_fields();
            }
            ptree.clear();
            _keep_track_table = t.select(fields, conditions);
            _recnos = t.select_recnos();
            return _keep_track_table;
        }
    }
    return _keep_track_table;
}


Table SQL::run_command(string commandstr)
{
    string temp;
    string pkey;
    vector<string>tempv;
    vector<string>tempvi;




    if (commandstr == "make" || commandstr == "create")
    {
        pkey = "table_name"; // my field table name will always have this key
        
        temp = ptree[ pkey].at(0); 
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
        _keep_track_table = t;

        return _keep_track_table;
    }
    else if (commandstr == "select")
    {
        //select 
        pkey = "table_name"; // my field table name will always have this key
        // cout << "ptree in command call: " << endl;
        // cout << ptree << endl;
        temp = ptree[pkey].at(0); //shoul only be one line 
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

