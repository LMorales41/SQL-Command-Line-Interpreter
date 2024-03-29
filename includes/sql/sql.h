#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <cstring>
#include <vector>
#include "../table/table.h"
#include "../table/typedefs.h"
#include "../parser/parser.h"
#include "../parser/sqltypedefs.h"
#include "../bplustree/bplustree.h"
#include "../bplustree/btree_array_funcs.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../bplustree/set_class.h"
#include "../stl_utils/vector_utilities.h"
using namespace std;

const string table_name = "table_name";
const string command = "command";
const string col = "col";
const string values = "values";
const string fields = "fields";
const string condition = "condition";

class SQL
{
    public:
        SQL(){}
            

        Table command(string commandline);
        void get_keys();
        vector<long> select_recnos()
        {
            //cout << "size of this vector is: " << recnos.size() << endl;
            return _recnos;
        }
        Table run_command(string commandstr);
        vector<long> _recnos;
        
    private:
        Parser prsr;
        mmap_ss ptree;
        vector<string>values;
        vector<string>keys;
        vector<vector<string>> queries;
        Table _keep_track_table;
        
};






#endif