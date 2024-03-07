#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <cstring>
#include <iomanip>
#include "file_record.h"

using namespace std;

//utility functions
bool file_exists(const char filename[]);

void open_fileRW(fstream& f, const char filename[]); // throw(char*);
void open_fileW(fstream& f, const char filename[]);

//void confuse_me();
//void simple_test();



#endif