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
    }
    Table (const string& name)
    {
        this->name = name;
        empty = false;
        read_info();
        reindex();
        numRecords = get_numRecords();
        
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

        outs << "Table name: " << t.name << ", records: " << t.numRecords << endl;
        outs << "record" << "\t";
        for (int i = 0; i < t.fieldNames.size(); i++)
        {
            outs << t.fieldNames[i] << "\t";
        }
        outs << endl;

        FileRecord r2;
        fstream f;
        
        string _bfilename = t.name + ".bin";
        open_fileRW(f,_bfilename.c_str());
        int i = 0;
        long bytes = r2.read(f, i); 
        while (bytes>0)
        {
            cout << i << "\t" << r2 << endl; 
            i++;
            bytes = r2.read(f, i);
        }
        f.close();

        outs << endl;
        return outs;
        }
    Map <string, long> fieldMap;
    vector<MMap<string, long>> indices;
    vectorstr fieldNames;

private:    
    string name;
    vector <long> recnos;
    bool empty;
    long _recno = -1;
    int numRecords = 0;

    
};






#endif