#ifndef SQL_H
#define SQL_H
#include <iostream>
#include <cstring>
#include "../table/table.h"
#include "../table/typedefs.h"
#include "../parser/parser.h"
#include "../parser/sqltypedefs.h"

using namespace std;

class SQL
{
    public:
        SQL(){}


        Table command(vectorstr commandline);



    private:

};






#endif