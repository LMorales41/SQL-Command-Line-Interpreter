#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "typedefs.h"
#include "../bplustree/bplustree.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../stl_utils/vector_utilities.h"
#include "../queue/MyQueue.h"
#include "../binary_files/file_record.h"
#include "rpn.h"
#include "../shunting_yard/shunting_yard.h"



using namespace std;

class Table
{
public:
    static int serial;
    Table()
    {
        name = "";
        empty = true;
    }
    Table (const string& name, const vectorstr fieldnames) 
    {
        this->name = name;
        fieldNames = fieldnames;
        empty = false;
        make_file();
        make_structures();
        //serial++;
        // cout << "meanwhile in ctor: " << endl;
        // for (int i = 0; i < fieldNames.size(); i++)
        // {
        //     cout << fieldNames[i] << " ";
        // }
        // cout << endl;
        // cout << fieldMap << endl;
    }
    Table (const string& name)
    {
        this->name = name;
        empty = false;
        //i had read info return a vectorstr before to fill up the one in the object
        //fieldNames = read_info();
        read_info();
        // make_file();
        // make_structures();
        reindex();
        numRecords = get_numRecords();
        //serial++;
        // cout << "in table string only arg ctor: " << endl;
        // for (int i = 0; i < fieldNames.size();i++)
        // {
        //     cout << fieldNames[i] << " ";
        // }
        // cout << endl;
    }
    ~Table(){}

    void make_file(); //same as write_info?
    void read_info();

    int get_numRecords();
    void insert_into(vectorstr collection);
    Table select_all();

    Table select(vectorstr fields, string field , string oper , string otherField);
    Table select(vectorstr fields, Queue<Token*> post);
    Table select(vectorstr fields, vectorstr conditions);
    Table select(vectorstr fields);
    vector<long> select_recnos();
    vectorstr set_fields(vectorstr& field_names);
    vectorstr get_fields();
    void make_structures();
    void print_vector (vectorstr v) //personal, not used
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << endl;
        }
    }
    void reindex();
    friend ostream& operator<< (ostream& outs, const Table& t) //its goin
    {
        outs << endl;
        //fieldnames size doesnt work, I need a way to show the amount of records INSIDE the file?
        //perhaps another variable for this can work, probably is the best solution since
        //it can be tracked as I insert? <- idk if bad idea 
        //i wish i was born in the bc 9000 id rather gather fruit and kill mammoth with the boys
        outs << "Table name: " << t.name << ", records: " << t.numRecords << endl;
        outs << "record" << "\t";
        for (int i = 0; i < t.fieldNames.size(); i++)
        {
            outs << t.fieldNames[i] << "\t";
        }
        outs << endl;
        //outs << "recno before FileRecord : " << t._recno << endl;
        //this reads every record
        FileRecord r2;
        fstream f;
        
        //open the file for reading and writing.
        string _bfilename = t.name + ".bin";
        open_fileRW(f,_bfilename.c_str());
        int i = 0;
        long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
        //cout << "start byte (long returned from r2.read(f,i)): " << bytes << endl;
        while (bytes>0)
        {
            cout << i << "\t" << r2 << endl; //if I wanna change the look of this output, i need to change the
                                    //outs operator for r2, to add spaces between each field
            i++;
            bytes = r2.read(f, i);
            //cout << "loop byte (long returned from r2.read from the loop): " << bytes <<endl;
        }
        f.close();

        //checks inside of mmaps
        // cout << "inside of mmap: " << endl;

        // for (int j = 0; j < t.indices.size(); j++)
        // {
        //     outs << t.indices[j];
        //     outs << '\t';
        // }

        outs << endl;
        return outs;
        }
    Map <string, long> fieldMap;
    vector<MMap<string, long>> indices;
    vectorstr fieldNames;

private:    
    string name;
    

    vector <long> recnos;
    
    //fstream f;
    bool empty;
    long _recno = -1;
    int numRecords = 0;
    //FileRecord fr;
    
    //int last_record;
    
};






#endif