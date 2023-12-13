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

using namespace std;

class SQL
{
    public:
        SQL(){}
            

        Table command(string commandline);
        void get_keys();
        vector<long> select_recnos(){return recnos;}
        Table run_command(string commandstr);

    private:
        mmap_ss ptree;
        vector<string>values;
        vector<string>keys;
        vector<vector<string>> queries;
        vector<long> recnos;
};






#endif