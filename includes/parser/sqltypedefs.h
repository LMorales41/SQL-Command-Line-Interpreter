#ifndef SQL_TYPEDEFS_H
#define SQL_TYPEDEFS_H
#include "../bplustree/bplustree.h"
#include "../bplustree/btree_array_funcs.h"
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"

using namespace std;


typedef MMap <string, string> mmap_ss;

const int SELECT = 1;
const int SYMBOL = 2;
const int FROM = 3;
const int WHERE = 4;
const int RELATIONAL = 5;
const int LOGICAL = 6;
const int MAKE = 10;
const int TABLE = 11;
const int FIELDS = 12;
const int INSERT = 20;
const int INTO = 21;
const int VALUES = 22;
const int LPAREN = 23;
const int RPAREN = 24;
const int STAR = 25;




#endif