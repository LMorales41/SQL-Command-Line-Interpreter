#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cstring>
#include "../bplustree/bplustree.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../bplustree/btree_array_funcs.h"
#include "../tokenizer/constants.h"
#include "../tokenizer/stokenize.h"
#include "../tokenizer/state_machine_functions.h"
#include "../token/token.h"
#include "sqltypedefs.h"

using namespace std;

class Parser
{
    public:

        Parser()
        {
            if (map_table_initialized == false)
            {
                make_table();
                // make_map();
                map_table_initialized = true;
            }
            make_map();

        }
        Parser(char* s);
        vector<string> tokenize(char* s); // returns the non edited string vector 
        void make_table();
        void make_map();
        mmap_ss get_parse_tree();
        mmap_ss parse_tree();
        void set_string(char* s);
        vector <string> input_q; //tokenized vector of strings from the char array we are handed
        string removeQuotes(string& original);

    private:
        static bool map_table_initialized;
        Map<string, int> keywords; //string =  keyword, int = column # for that keyword
        //mmap_ss ptree; //keyword = string, value returned = string
        static int _table[MAX_ROWS][MAX_COLUMNS]; //state machine

};





#endif