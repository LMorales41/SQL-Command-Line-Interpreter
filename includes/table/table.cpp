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

    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one

    string holds;

    int insert_index;
    vector<int> fieldindexes;
    for (int i = 0; i < fields.size(); i++)
    {
        holds = fields[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }

    string newname = name + to_string(serial);
    Table t (newname, fields);
    FileRecord r;
    fstream f;
    vectorstr row;
    
    open_fileRW(f, orig_bfilename.c_str());
    int i = 0;
    long bytes = r.read(f, i); //empty envelop to be filled by the FileRecord object


    while (bytes>0)
    {

        row = r.vectorized_record(fieldindexes);
        t.insert_into(row);
        recnos.push_back(i);
        i++;
        bytes = r.read(f, i);
    }
    f.close();
    
    t.recnos = recnos;
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
    }
    //cout << endl;

    f.close();
    return;
}

void Table::insert_into(vectorstr collection)
{  

    FileRecord r;
    fstream f;
    string _bfilename = name + ".bin";
    open_fileRW(f, _bfilename.c_str());
    r = FileRecord(collection);

    _recno = r.write(f);


    for (int i = 0; i < collection.size(); i++)
    {
        indices[i].insert(collection[i], _recno);
    }

    f.close();
    numRecords++;
    return;
}

Table Table::select_all()
{
    serial++;
    vector<int> fieldindexes;
    string holds;
    int insert_index;
    for (int i = 0; i < fieldNames.size(); i++)
    {
        holds = fieldNames[i];
        insert_index = fieldMap.get(holds);
        fieldindexes.push_back(insert_index);
    }
    string newname = name + to_string(serial);
    Table t(newname, fieldNames);
    string orig_bfilename = name + ".bin";
    FileRecord r;
    fstream f;
    open_fileRW(f, orig_bfilename.c_str());
    int i = 0;
    long bytes = r.read(f, i); //empty envelop to be filled by the FileRecord object
    vectorstr row;
    //cout << "start byte (long returned from r2.read(f,i)): " << bytes << endl;
    while (bytes>0)
    {
        //cout << i << "\t" << r << endl; //if I wanna change the look of this output, i need to change the
        //                         //outs operator for r2, to add spaces between each field
        row = r.vectorized_record(fieldindexes);
        t.insert_into(row);
        recnos.push_back(i);
        i++;
        bytes = r.read(f, i);
        //row = r.vectorized_record(fieldindexes);
        //t.insert_into(row);
        //cout << "loop byte (long returned from r2.read from the loop): " << bytes <<endl;
    }
    f.close();
    //t.recnos = recnos;
    return t;

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

    MMap<string, long>::Iterator itr; //this will help for >, < to serve as our sig value
    MMap<string, long>::Iterator itbegin =  indices[index].begin(); //start of the itr

    vector <long> field_recnos;
    if (oper == "=") 
    {
        
        field_recnos = indices[index].at(otherField); //returns value lists where key = otherField
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


    for (int i = 0 ; i < field_recnos.size(); i++)
    { 
        
        long temp = field_recnos[i];
        
        r.read(f, temp);
        //cout << "before assigning row" << endl;
        row = r.vectorized_record(fieldindexes); //this will change every loop

        t.insert_into(row); //inserts the row u are in!

    }


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


    string newname = name + to_string(serial); // new filename for table we are going to create

    Table t (newname, fields);
    //cout << "after creating new table" << endl;

    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one

    FileRecord r;
    fstream f;
    vectorstr row;
    open_fileRW(f, orig_bfilename.c_str());

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


        t.insert_into(row); //inserts the row u are in!

    }
    f.close();

    recnos = field_recnos; //assign it to the private variable
    t.recnos = field_recnos;
    //t.insert_into()
    return t;
}

Table Table::select(vectorstr fields, vectorstr conditions)
{

    shunting_yard sy1(conditions);
    //sy1.print_queue();
    Queue<Token*> post = sy1.get_postfix();

    RPN rpn1(post);
    rpn1.do_rpn_thing(fieldMap,indices);

    vector<long> field_recnos = rpn1.get_solution();
    //cout << "size for vec: " << field_recnos.size() << endl;
    sort(field_recnos.begin(), field_recnos.end());


    string newname = name + to_string(serial); // new filename for table we are going to create

    Table t (newname, fields);
    //cout << "after creating new table" << endl;

    //cout << "after looking through the maps" << endl;
    string orig_bfilename = name + ".bin"; //to read from existing .bin, not to write into new one

    FileRecord r;
    fstream f;
    vectorstr row;
    open_fileRW(f, orig_bfilename.c_str());

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


        t.insert_into(row); //inserts the row u are in!

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


    
    FileRecord r(fieldNames);
    fstream f;
    string _bfilename = name + ".bin";
    string _tfilename = name + "_fields.txt";
    // cout << "filename: " <<_bfilename.c_str() << endl;
    // cout << r << endl;
    //opening binary file
    open_fileW(f, _bfilename.c_str());


    f.close();


    //end of writing to binary file
    
    //writing to txt file
    open_fileRW(f, _tfilename.c_str());
    for (int i = 0; i < fieldNames.size(); i++) //will write a new fieldname to each line
    {
        f << fieldNames[i] << endl;
    }
    f.close();

    serial++;
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
        //recnos.push_back(i);
        //cout<<"record "<<i<<": "<<r2<<endl;
        row = r2.vectorized_record(fieldindexes);
        for (int z = 0; z< row.size(); z++)
        {
            indices[z].insert(row[z], i);
        }
        i++;
        numRecords++;


        bytes = r2.read(f, i);
    }
    f.close();



    
    return;
}