#ifndef RPN_H
#define RPN_H


#include <iostream>
#include <cstring>
#include <algorithm>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/childtokens.h"
#include "../table/table.h"
#include "../bplustree/bplustree.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../table/typedefs.h"

using namespace std;

class RPN 
{
    public:
        RPN(){}
        RPN(Queue<Token*> queue)
        {
            postfix = queue;

        }

        //write a function that takes something like (12, age, =)
            //puts these into a stack, when I hit logicals and reltionals
        //returns a vector of longs
        //put that into a token solution
        void do_rpn_thing(Map <string, long>& fieldMap, vector<MMap<string, long>>& indices);
        vector<long> get_solution(); 
        
        vector<long> check_recnos(Map <string, long>& fieldMap, vector<MMap<string, long>>& indices, string field, string oper, string otherField);
        vector<long> or_function(vector<long> first, vector<long> second);
        vector<long> and_function(vector<long> first, vector<long> second);
        void get_bigger_first(vector<long>& one, vector<long>& two);
        void filter_repeats(vector<long>& vec);
    private:
        Queue<Token *> postfix; //this will be handed to me by shunting yard
                            //it is rpns job to handle this part

        Stack<Token *> solutionholder;

        Solution sltn;

        //dont think i need these? i pass by reference now 
        //tests run fine before commenting this if they break its cause of this
        // Map <string, long> fieldMap;
        // vector<MMap<string, long>> indices;
        
        

};

#endif