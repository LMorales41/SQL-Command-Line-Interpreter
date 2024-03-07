#ifndef FILE_RECORD_H
#define FILE_RECORD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include "utilities.h"
#include <cstring>
#include <iomanip>

using namespace std;



class FileRecord
{
    
public:
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    FileRecord()
    {
        //_record[0] = '\0';
        _record[0][0] = '\0';
        recno = -1;
    }

    FileRecord (string s)
    {
        fillNull();
        strncpy(_record[0], s.c_str(), MAX);
    }



    FileRecord(vector <string> str)
    {
        //software is shit.
        //          -The Russian guy in 
        //                   Ironman II
        fillNull();
        for (int i = 0; i < str.size(); i++)
        {
            strncpy(_record[i], str[i].c_str(), MAX);
        }
        recno = -1;
    }
    long write(fstream& outs);              //returns the FileRecord number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs, const FileRecord& r);
    static const int MAX = 100;
    char _record[MAX+1] [MAX+1];
    int recno;
    
    vector<string> vectorized_record (vector<int> fieldindexes)
    {
        string created = "";
        vector<string> row;
        int hold;
        for (int i = 0; i < fieldindexes.size(); i++)
        {
            hold = fieldindexes[i];
            created += _record[hold];
            row.push_back(created);
            created = "";
        }

        // for (int i = 0; i < MAX+1; i++)
        // {
        //     //cout << "test inside utar: " << endl;
        //     created += _record[i];
        //     if  (created == "")
        //     {
        //         return row;
        //     }
        //     row.push_back(created);
        //     created = "";
        // }
        return row;
    }
    
private:
    void fillNull()
    {
        for (int i = 0; i < MAX+1; i++)
        {
            _record[i][0] = '\0';
        }
    }
    
    
};





#endif