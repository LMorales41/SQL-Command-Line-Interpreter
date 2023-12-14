#include "table.h"

int Table::serial = 0; //static variable, changes based on file number (to create new files everytime)

int Table::get_numRecords()
{
    FileRecord r2;
    fstream f;
    string _bfilename = name + ".bin";
    open_fileRW(f,_bfilename.c_str());
    int i = 0;
    long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    //cout << "start byte (long returned from r2.read(f,i)): " << bytes << endl;
    while (bytes>0)
    {
        //cout<< i<<": "<<r2<<endl; //if I wanna change the look of this output, i need to change the
                                //outs operator for r2, to add spaces between each field
        i++;
        bytes = r2.read(f, i);
        //cout << "loop byte (long returned from r2.read from the loop): " << bytes <<endl;
    }
    f.close();
    return i;
}


Table Table::select(vectorstr fields)
{
    serial++;
    cout << "calls select with no conditions only fields" << endl;
    for (int i = 0; i < fields.size(); i++)
    {
        cout << fields[i] << endl;
    }
    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one
    //I now have the long vector with all recno locations
    //simply read binary file at the recnos from here, and turn them into a vector
    string holds;
    int insert_index;
    vector<int> fieldindexes;
    for (int i = 0; i < fields.size(); i++)
    {
        holds = fields[i];
        //cout << "holds: " << holds << endl;
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    string newname = name + to_string(serial);
    Table t (newname, fields);
    FileRecord r;
    fstream f;
    vectorstr row;

    for (int i = 0 ; i < recnos.size(); i++)
    { 
        
        long temp = recnos[i];
        
        r.read(f, temp);
        //cout << "before assigning row" << endl;
        row = r.vectorized_record(fieldindexes); //this will change every loop

        t.insert_into(row); //inserts the row u are in!
        //should be completely finished wiht table once loop ends!

        //cout << "this is the vector created from pos " << field_recnos[i] << ": " <<endl;
        //this is to check wtf is inside row bc idk 
        // for (int j = 0; j < row.size(); j++)
        // {
        //     //cout << "in row: ";
        //     cout << j << ":" <<row[j] << " " << endl;
        // }
    }

    return t;
}


void Table::read_info() //opens txt file, populates fieldNames vector with info from file
{
    fstream f;
    
    string _tfilename = name + "_fields.txt";
    vectorstr temp;
    string tempstr;
    ifstream file (_tfilename);

    //open_fileW(f, _tfilename.c_str());

    //int i = 0;
    while (getline(file, tempstr))
    {
        fieldNames.push_back(tempstr);
        //cout << temp[i] << " ";
        //i++;
    }
    //cout << endl;

    f.close();
    return;
}

void Table::insert_into(vectorstr collection)
{   //fields = fname, lname, age
    //row = {"Joe", "Gomez", "20"};
    //cout << "seg fault here" << endl;
    FileRecord r;
    fstream f;
    string _bfilename = name + ".bin";
    open_fileRW(f, _bfilename.c_str());
    r = FileRecord(collection);
    // cout << "the vector i pass into insert_into" << endl;
    // cout << "the size of it: " << collection.size() << endl;
    // print_vector(collection);
    //cout << "writing this vector" << endl;
    // cout << "table name: " << name << endl;
    // cout << "is writing into the following file: " << _bfilename << endl;
    _recno = r.write(f);
    //recnos.push_back(_recno);
    // cout << "recnos after inserting: " << endl;
    //cout << "recno: " <<_recno << endl;
    // cout << "collection size: " << recnos.size() << endl;
    // for (int i = 0; i < recnos.size(); i++)
    // {
    //     cout << recnos[i] << " ";
    // }
    //cout << endl;
    for (int i = 0; i < collection.size(); i++)
    {
        //MPair <string, long> temp (collection[i], _recno); <- being inserted
        indices[i].insert(collection[i], _recno);
    }

    f.close();
    numRecords++;
    return;
}

Table Table::select_all()
{
    // serial++;
    // string newname = name + to_string(serial); // new filename for table we are going to create
    // //cout << newname << endl;
    // Table t (newname, fieldNames);
    // //Table t (newname); //new table is constructed with the parameters
    // //now create a record of people based on field then performing whatever oper does
    // //ex. if given lname(field) = (oper) yao (otherField) then we grab records from Yaos
    // //cout << "index: " << index <<endl;
    // //cout << fieldMap << endl;
    // int insert_index;
    // string holds;
    // vector<int> fieldindexes;
    // for (int i = 0; i < fieldNames.size(); i++)
    // {
    //     holds = fieldNames[i];
    //     insert_index = fieldMap.get(holds);
    //     fieldindexes.push_back(insert_index);
    // }
    // vector<long>field_recnos = select_recnos();
    // // cout << "field_recnos: " << endl;
    // // for (int i = 0; i < field_recnos.size(); i++)
    // // {
    // //     cout << field_recnos[i] << endl;
    // // }
    // // cout << "end of records" << endl;
    // //cout << "after looking through the maps" << endl;
    // string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one
    // //I now have the long vector with all recno locations
    // //simply read binary file at the recnos from here, and turn them into a vector
    // FileRecord r;
    // fstream f;
    // vectorstr row;
    // open_fileRW(f, orig_bfilename.c_str());
    // //test for recnos (as of 12:12pm wed dec 6 it works please dont stop working i miss my cats please dont stop working)
    // // //cout << "after opening file, before recnos vector" << endl;
    
    // // cout << "these are the record numbers(location) of the desired field '" << otherField << "'" << endl;
    // //cout << "before recnos loop" << endl;
    // //cout << "in recnos: ";
    // // cout << name << " table recnos: " << endl;
    // // for (int i = 0; i < field_recnos.size(); i++)
    // // {
    // //     cout << field_recnos[i] << " ";
    // // }
    // // cout << endl;
    // // cout << "before I begin inserting this is what the table looks like " << endl;
    // // cout << t << endl;

    // for (int i = 0 ; i < field_recnos.size(); i++)
    // { 
        
    //     long temp = field_recnos[i];
        
    //     r.read(f, temp);
    //     //cout << "before assigning row" << endl;
    //     row = r.vectorized_record(fieldindexes); //this will change every loop

    //     t.insert_into(row); //inserts the row u are in!
    //     //should be completely finished wiht table once loop ends!

    //     //cout << "this is the vector created from pos " << field_recnos[i] << ": " <<endl;
    //     //this is to check wtf is inside row bc idk 
    //     // for (int j = 0; j < row.size(); j++)
    //     // {
    //     //     //cout << "in row: ";
    //     //     cout << j << ":" <<row[j] << " " << endl;
    //     // }
    // }
    // //check row but outside of loop to see exactly what it looks like to a normal human being
    // //this will only show the LAST record pulled, nothing else here
    // // i like trtles
    // // for (int j = 0; j < row.size(); j++)
    // // {
    // //     //cout << "in row: ";
    // //     cout << j << ":" <<row[j] << " " << endl;
    // // }
    // //end of skibidi

    // f.close();
    // //recnos = field_recnos; //assign it to the private variable
    // t.recnos = recnos;
    //t.insert_into()
    //return select(fieldNames);
    return *this;

}


//creates new table using the 2 arg constructor (creates a file due to this)
//creates recno vector of locations that fit the oper values  
//ex. grabs location of all records where lname (field) = (oper) tueni (otherField) and puts in long vectr
//reads at these locations from the bfile of the table that called this function
//inserts the records read into the new table's file
Table Table::select(vectorstr fields, string field , string oper , string otherField)
{
    serial++; //to ensure new file every time

    //cout << "serial: " <<serial << endl;
    //cout << "at start" << endl;
    string newname = name + to_string(serial); // new filename for table we are going to create
    //cout << newname << endl;
    Table t (newname, fields);
    //Table t (newname); //new table is constructed with the parameters
    //now create a record of people based on field then performing whatever oper does
    //ex. if given lname(field) = (oper) yao (otherField) then we grab records from Yaos
    int index = fieldMap.get(field);
    //cout << "index: " << index <<endl;
    //cout << fieldMap << endl;
    int insert_index;
    string holds;
    vector<int> fieldindexes;
    for (int i = 0; i < fields.size(); i++)
    {
        holds = fields[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    //ghetto way of checking what to grab (oper)
    //cout << indices[index] << endl;
    MMap<string, long>::Iterator itr; //this will help for >, < to serve as our sig value
    MMap<string, long>::Iterator itbegin =  indices[index].begin(); //start of the itr

    //these functions will populate field_recnos with recnos
    //these recnos are locations in our bin file where we find the records
    vector <long> field_recnos;
    if (oper == "=") 
    {
        //cout << otherField << endl;
        
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
    else
    {
        cout << "oper is not valid" << endl;
        return t;
    }
    
    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one
    //I now have the long vector with all recno locations
    //simply read binary file at the recnos from here, and turn them into a vector
    FileRecord r;
    fstream f;
    vectorstr row;
    open_fileRW(f, orig_bfilename.c_str());
    //test for recnos (as of 12:12pm wed dec 6 it works please dont stop working i miss my cats please dont stop working)
    // //cout << "after opening file, before recnos vector" << endl;
    
    // cout << "these are the record numbers(location) of the desired field '" << otherField << "'" << endl;
    //cout << "before recnos loop" << endl;
    //cout << "in recnos: ";
    // cout << name << " table recnos: " << endl;
    // for (int i = 0; i < field_recnos.size(); i++)
    // {
    //     cout << field_recnos[i] << " ";
    // }
    // cout << endl;
    // cout << "before I begin inserting this is what the table looks like " << endl;
    // cout << t << endl;

    for (int i = 0 ; i < field_recnos.size(); i++)
    { 
        
        long temp = field_recnos[i];
        
        r.read(f, temp);
        //cout << "before assigning row" << endl;
        row = r.vectorized_record(fieldindexes); //this will change every loop

        t.insert_into(row); //inserts the row u are in!
        //should be completely finished wiht table once loop ends!

        //cout << "this is the vector created from pos " << field_recnos[i] << ": " <<endl;
        //this is to check wtf is inside row bc idk 
        // for (int j = 0; j < row.size(); j++)
        // {
        //     //cout << "in row: ";
        //     cout << j << ":" <<row[j] << " " << endl;
        // }
    }
    //check row but outside of loop to see exactly what it looks like to a normal human being
    //this will only show the LAST record pulled, nothing else here
    // i like trtles
    // for (int j = 0; j < row.size(); j++)
    // {
    //     //cout << "in row: ";
    //     cout << j << ":" <<row[j] << " " << endl;
    // }
    //end of skibidi

    f.close();
    recnos = field_recnos; //assign it to the private variable
    t.recnos = field_recnos;
    //t.insert_into()
    return t;
}



Table Table::select(vectorstr fields, Queue<Token*> post)
{
    //cout << "size of fields that I am being handed: " << fields.size() <<endl;

    RPN rpn1(post);
    rpn1.do_rpn_thing(fieldMap,indices);
    vector<long> field_recnos = rpn1.get_solution();
    sort(field_recnos.begin(), field_recnos.end());
    // cout << "field recnos: " << endl;
    // cout << "size: " << field_recnos.size() << endl;
    // for (int i = 0; i < field_recnos.size(); i++)
    // {
    //     cout << "f_r: " << field_recnos[i] << endl;
    // }
    //so far it has everthing I need? ok runs fine

    string newname = name + to_string(serial); // new filename for table we are going to create
    //cout << newname << endl;
    // cout << "field_recnos: " << endl;
    // cout << "size: " << field_recnos.size() << endl;
    // for (int i = 0; i < field_recnos.size();i++)
    // {
    //     cout << "i: " << i << endl;
    //     cout << field_recnos[i] << endl;
    // }
    // cout << endl;
    //cout << "before creating new table" << endl;
    Table t (newname, fields);
    //cout << "after creating new table" << endl;

    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one
    //I now have the long vector with all recno locations
    //simply read binary file at the recnos from here, and turn them into a vector
    FileRecord r;
    fstream f;
    vectorstr row;
    open_fileRW(f, orig_bfilename.c_str());
    //test for recnos (as of 12:12pm wed dec 6 it works please dont stop working i miss my cats please dont stop working)
    // //cout << "after opening file, before recnos vector" << endl;
    
    // cout << "these are the record numbers(location) of the desired field '" << otherField << "'" << endl;
    //cout << "before recnos loop" << endl;
    //cout << "in recnos: ";
    // cout << name << " table recnos: " << endl;
    // for (int i = 0; i < field_recnos.size(); i++)
    // {
    //     cout << field_recnos[i] << " ";
    // }
    // cout << endl;
    // cout << "before I begin inserting this is what the table looks like " << endl;
    // cout << t << endl;
    // // cout << "before I begin the loop this is the size of recnos: " << field_recnos.size() <<endl;
    // cout << "here are my fields and their index :" << endl;
    // cout << "size of fieldnames: " <<t.fieldNames.size() << endl;
    // for (int l = 0; l < t.fieldNames.size();l++ )
    // {
    //     cout << l << ": " << t.fieldNames[l] << endl;
    // }
    int insert_index;
    string holds;
    vector<int> fieldindexes;
    for (int i = 0; i < fields.size(); i++)
    {
        holds = fields[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    for (int i = 0 ; i < field_recnos.size(); i++)
    { 
        
        long temp = field_recnos[i];
        
        r.read(f, temp);
        //cout << "before assigning row" << endl;
        row = r.vectorized_record(fieldindexes); //this will change every loop
        // cout << "this is row: " << endl;
        // for (int l = 0; l < row.size(); l++)
        // {
        //     cout << row [l] << " ";
        // }
        // cout << endl;

        t.insert_into(row); //inserts the row u are in!
        //should be completely finished wiht table once loop ends!

        //cout << "this is the vector created from pos " << field_recnos[i] << ": " <<endl;
        //this is to check wtf is inside row bc idk 
        // for (int j = 0; j < row.size(); j++)
        // {
        //     //cout << "in row: ";
        //     cout << j << ":" <<row[j] << " " << endl;
        // }
    }
    f.close();

    recnos = field_recnos; //assign it to the private variable
    t.recnos = field_recnos;
    //t.insert_into()
    return t;
}

Table Table::select(vectorstr fields, vectorstr conditions)
{
    //cout << "size of fields that I am being handed: " << fields.size() <<endl;
    //out << "size of conditions I am being handed: " << conditions.size() << endl;
    shunting_yard sy1(conditions);
    //sy1.print_queue();
    Queue<Token*> post = sy1.get_postfix();
    // Queue<Token*> copy = sy1.get_postfix();
    // int copysize = copy.size();
    // cout << "this is postfix: " << endl;
    // for (int i = 0; i < copysize; i++)
    // {
    //     cout << *copy.pop() << " ";
    // }
    //cout << endl;
    RPN rpn1(post);
    rpn1.do_rpn_thing(fieldMap,indices);

    vector<long> field_recnos = rpn1.get_solution();
    //cout << "size for vec: " << field_recnos.size() << endl;
    sort(field_recnos.begin(), field_recnos.end());
    // cout << "field recnos: " << endl;
    // cout << "size: " << field_recnos.size() << endl;
    // for (int i = 0; i < field_recnos.size(); i++)
    // {
    //     cout << "f_r: " << field_recnos[i] << endl;
    // }
    //so far it has everthing I need? ok runs fine

    string newname = name + to_string(serial); // new filename for table we are going to create
    //cout << newname << endl;
    // cout << "field_recnos: " << endl;
    // cout << "size: " << field_recnos.size() << endl;
    // for (int i = 0; i < field_recnos.size();i++)
    // {
    //     cout << "i: " << i << endl;
    //     cout << field_recnos[i] << endl;
    // }
    // cout << endl;
    //cout << "before creating new table" << endl;
    Table t (newname, fields);
    //cout << "after creating new table" << endl;

    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one
    //cout << "reads from this binary file " << orig_bfilename << endl;
    //I now have the long vector with all recno locations
    //simply read binary file at the recnos from here, and turn them into a vector
    FileRecord r;
    fstream f;
    vectorstr row;
    open_fileRW(f, orig_bfilename.c_str());
    //test for recnos (as of 12:12pm wed dec 6 it works please dont stop working i miss my cats please dont stop working)
    // //cout << "after opening file, before recnos vector" << endl;
    
    // cout << "these are the record numbers(location) of the desired field '" << otherField << "'" << endl;
    //cout << "before recnos loop" << endl;
    //cout << "in recnos: ";
    // cout << name << " table recnos: " << endl;
    // for (int i = 0; i < field_recnos.size(); i++)
    // {
    //     cout << field_recnos[i] << " ";
    // }
    // cout << endl;
    // cout << "before I begin inserting this is what the table looks like " << endl;
    // cout << t << endl;
    // // cout << "before I begin the loop this is the size of recnos: " << field_recnos.size() <<endl;
    // cout << "here are my fields and their index :" << endl;
    // cout << "size of fieldnames: " <<t.fieldNames.size() << endl;
    // for (int l = 0; l < t.fieldNames.size();l++ )
    // {
    //     cout << l << ": " << t.fieldNames[l] << endl;
    // }
    int insert_index;
    string holds;
    vector<int> fieldindexes;
    for (int i = 0; i < fields.size(); i++)
    {
        holds = fields[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    for (int i = 0 ; i < field_recnos.size(); i++)
    { 
        
        long temp = field_recnos[i];
        
        r.read(f, temp);
        //cout << "before assigning row" << endl;
        row = r.vectorized_record(fieldindexes); //this will change every loop
        // cout << "this is row: " << endl;
        // for (int l = 0; l < row.size(); l++)
        // {
        //     cout << row [l] << " ";
        // }
        // cout << endl;

        t.insert_into(row); //inserts the row u are in!
        //should be completely finished wiht table once loop ends!

        //cout << "this is the vector created from pos " << field_recnos[i] << ": " <<endl;
        //this is to check wtf is inside row bc idk 
        // for (int j = 0; j < row.size(); j++)
        // {
        //     //cout << "in row: ";
        //     cout << j << ":" <<row[j] << " " << endl;
        // }
    }
    f.close();

    recnos = field_recnos; //assign it to the private variable
    t.recnos = field_recnos;
    //t.insert_into()
    return t;
}


vector<long> Table::select_recnos()
{
    return recnos;
}

vectorstr Table::set_fields(vectorstr& field_names)
{
    fieldNames = field_names;
    return fieldNames;
}

vectorstr Table::get_fields ()
{
    return fieldNames;
}

void Table::make_file()
{

    //writing fieldNames vector into files
    // for (int i = 0; i < fieldNames.size(); i++)
    // {
    //     cout << fieldNames[i] << " ";
    // }

    //vector <string> test = {"katsu", "bagel", "small cat"};
    
    FileRecord r(fieldNames);
    fstream f;
    string _bfilename = name + ".bin";
    string _tfilename = name + "_fields.txt";
    // cout << "filename: " <<_bfilename.c_str() << endl;
    // cout << r << endl;
    //opening binary file
    open_fileW(f, _bfilename.c_str());
    //open_fileW(f, _bfilename.c_str()); //this is to pass basic test
    // _recno = r.write(f);
    // cout << "wrote into record: " << _recno << endl;

    f.close();


    //end of writing to binary file
    
    //writing to txt file
    open_fileRW(f, _tfilename.c_str());
    for (int i = 0; i < fieldNames.size(); i++) //will write a new fieldname to each line
    {
        f << fieldNames[i] << endl;
    }
    f.close();
    //end of writing to txt file

    // tests

    // FileRecord r2;
    // open_fileRW(f, _bfilename.c_str());
    // r2.read(f, _recno);
    // cout << "r2 read: " << r2 << endl;
    // f.close();
    // serial++;
}

void Table::make_structures()
{
    //cout << "make structs " << endl;

    for (int i = 0; i < fieldNames.size(); i++)
    {
        //cout << "it: " <<i << endl;
        fieldMap.insert(fieldNames[i], i);
    }


    MMap <string, long> temp;
    

    for (int i = 0; i < fieldNames.size();i++) //push back something into vector!!!
    {
        indices.push_back(temp);
    }
    //indices;
    //cout << fieldMap << endl;
    //cout << "successfully returns" << endl;
    return;
}

void Table::reindex()
{
    make_structures();

    //populate each mmap

    vectorstr row; 
    FileRecord r2;
    fstream f;
    
    //open the file for reading and writing.
    string _bfilename = name + ".bin";
    open_fileRW(f,_bfilename.c_str());
    int insert_index;
    string holds;
    vector<int> fieldindexes;
    for (int i = 0; i < fieldNames.size(); i++)
    {
        holds = fieldNames[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    long i = 0;
    long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    //cout << "start byte (long returned from r2.read(f,i)): " << bytes << endl;
    while (bytes>0)
    {
        //cout<<"record "<<i<<": "<<r2<<endl;
        row = r2.vectorized_record(fieldindexes);
        for (int z = 0; z< row.size(); z++)
        {
            indices[z].insert(row[z], i);
        }
        i++;
        //check row
        // cout << "row inside my ctor: " << endl;
        // for (int i = 0; i < row.size(); i++)
        // {
        //     cout << row[i] << endl;
        // }

        bytes = r2.read(f, i);
        //cout << "loop byte (long returned from r2.read from the loop): " << bytes <<endl;
    }
    f.close();



    
    return;
}