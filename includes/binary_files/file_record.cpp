#include "file_record.h"




long FileRecord::write(fstream &outs)
 {
    //r.write(f); //take the FileRecord r and write it into file f
    //  and return the FileRecord number of this FileRecord

    //write to the end of the file.
    outs.seekg(0, outs.end);


    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    //outs.write(&FileRecord[0], sizeof(FileRecord));

    for (int i = 0; i < MAX+1; i++)
    {
        outs.write(_record[i], sizeof(_record[i]));
    }

    return pos/sizeof(_record);  //FileRecord number
}

long FileRecord::read(fstream &ins, long recno){
    //returns the number of bytes read.
    //    r.read(f, 6);
    //    cout<<r<<endl;
    //cout << "before setting pos" << endl;
    long pos= recno * sizeof(_record);
    //cout <<"before seekg" << endl;
    ins.seekg(pos, ios_base::beg);

    //ins.read(&_FileRecord[0], sizeof(_FileRecord))
    
    //cout <<"before read " << endl;
    ins.read(&_record[0][0], sizeof(_record));

    
    //don't you want to mark the end of  the cstring with null?
    //_FileRecord[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:
    //  for (int i = 0; i < MAX+1; i++)
    //  {
    //      _FileRecord[i][ins.gcount()] = '\0';
    //  }
    //cout << "before null char thingy" << endl;
    //_record[MAX][ins.gcount()] = '\0';
    //cout << "return issue" << endl;
    return ins.gcount();

}
ostream& operator <<(ostream& outs,const FileRecord& r)
{
    for (int i = 0; i < r.MAX+1; i++)
    {
        outs<< r._record[i] << "\t";
    }
   //outs << " ";
    return outs;
}