#include "parser.h"

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser(char* s)
{
  //cout << "tokenize" << endl;
  tokenize(s);
  //cout << "make map" << endl;
  make_map();
  //cout << "make table" << endl;
  make_table();
  //cout << "getptree" << endl;
  get_parse_tree();
  //ptree.print_lookup();
  //cout << "not this?" << endl;
  // cout << "my sentence: " << endl;
  // for (int i = 0; i < input_q.size(); i++)
  // {
  //   cout << input_q[i] << " ";
  // }
  // cout << endl;
  // cout << "my ptree: " << endl;
  // cout << ptree << endl;
  // for (int i = 0; i < tokenized.size(); i++)
  // {
  //   cout << tokenized[i] << " ";
  // }
  // cout << endl;
  
}

void Parser::set_string(char* s)
{
  //same thing as constructorly nearly
  tokenize(s);
  //destroy whatever tree we had before
  ptree.clear();

  get_parse_tree();
}

vector<string> Parser::tokenize(char* s)
{
  //fill vector with all parts of the string
  input_q.clear();
  vector<string> temp;
  STokenizer stk(s);
  Token t;
  stk>>t;
  while(stk.more())
  {
    //process token here...
    //cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
    temp.push_back(t.get_string()); //

    t = Token();
    stk>>t;
  }


  //remove unwanted parts
  string removeq = "";
  for (int i = 0; i < temp.size(); i++)
  {
    if (temp[i] == " " || temp[i] == "," || temp[i] == "\"" || temp[i] == "\t" || temp[i] == "\n")
    {
      
    }
    else
    {
      removeq = temp[i];
      if (removeq[0] == '"')
      {
        removeq = removeq.substr(1);
      }
      input_q.push_back(removeq);
    }
  }
  // for (int i = 0; i < input_q.size(); i++)
  // {
  //   cout << input_q[i] << endl;

  // }
  return temp; //raw unedited
}

void Parser::make_map()
{

  keywords.insert("from", FROM);
  keywords.insert("where", WHERE); 
  keywords.insert("table", TABLE);
  keywords.insert("fields", FIELDS);
  keywords.insert("values", VALUES);
  keywords.insert("symbol", SYMBOL);
  keywords.insert("(", LPAREN);
  keywords.insert(")", RPAREN);

  //all commands
  keywords.insert("select", SELECT);
  keywords.insert("insert", INSERT);
  keywords.insert("into", INTO);
  keywords.insert("make", MAKE);
  keywords.insert("create", MAKE);
  
  //all relational strings
  keywords.insert(">", RELATIONAL);
  keywords.insert("<", RELATIONAL);
  keywords.insert("=", RELATIONAL);
  keywords.insert(">=", RELATIONAL);
  keywords.insert("<=", RELATIONAL);

  //all logical strings
  keywords.insert("and", LOGICAL);
  keywords.insert("or", LOGICAL);




}

void Parser::make_table() //add this back in if it doesnt work -> (int _table[][MAX_COLUMNS])
{
    init_table(_table); 
    //fail states/not success states
    // mark_fail(_table, 0);
    // mark_fail (_table, 5); 

    //success states
    // mark_success(_table, 1);
    // mark_success(_table, 2);
    // mark_success(_table, 3);
    // mark_success(_table,4);
    // mark_success (_table, 6);


    //can also be select lname from student where age < 10 and fname > ape


    // //what state each char will lead to
    //selects
    mark_success(_table, 4); //select lname from student ^^
    mark_success(_table, 8); //select lname from student where age < 10 ^^

    mark_cell(0, _table, SELECT, 1); //command $select
    mark_cell(1, _table, SYMBOL, 2); //field $lname
    mark_cell(2,_table,  SYMBOL, 2);//if any other fields $fname
    mark_cell (2, _table, FROM, 3 ); //from -useless $from
    mark_cell (3, _table, SYMBOL, 4);//table_name $student
    mark_cell (4, _table, WHERE, 5 ); //where -useless $where
    mark_cell (5, _table, LPAREN, 5);
    mark_cell (5, _table, SYMBOL, 6); //lhs comparison $age
    mark_cell (6, _table, RELATIONAL, 7); // >, <, = , <= $<
    mark_cell (7, _table, SYMBOL, 8); //rhs comparison -complete $10
    mark_cell (8, _table, RPAREN, 8);
    mark_cell (8, _table, LOGICAL, 9); //union/intersection sends me back to lhs stage $and
    mark_cell (9, _table, LPAREN, 9);
    mark_cell (9, _table, SYMBOL, 6);
            //last used is 9
    //make
    mark_success(_table, 14);//make table student fields lname, fname
    mark_cell(0, _table, MAKE, 10); //command  $make
    mark_cell(10, _table, TABLE, 11); //table -useless $table
    mark_cell(11, _table, SYMBOL, 12); //table_name $student
    mark_cell(12, _table, FIELDS, 13); //fields -useless $fields
    mark_cell(13, _table, SYMBOL, 14); //fieldnames $ lname , $fname, $age
    mark_cell(14, _table, SYMBOL, 14); // more fieldnames $ id, major
      //last used is 14

    //insert
    mark_success(_table, 24); //insert into student values John 
    mark_cell(0, _table, INSERT, 20); //command $insert
    mark_cell(20, _table, INTO, 21); //into -useless $into
    mark_cell (21, _table, SYMBOL, 22); //table_name $student
    mark_cell (22, _table, VALUES, 23); //values -useless $values
    mark_cell (23, _table, SYMBOL, 24); //valuenames $John, Smith, 23
    mark_cell (24, _table, SYMBOL, 24); //other valuenames $cs, Pasadena
      //last used is 23


  //shake child
}


void Parser::get_parse_tree()
{
  string strng;
  int state = 0;
  int column;
  for (int i = 0; i < input_q.size(); i++)
  {
    strng = input_q[i];
    if (!keywords.contains(strng))
    {
      column = keywords.get("symbol");
    }
    else 
    {
      column = keywords.get(strng);
    }

    state = _table[state][column];

    //to bugfix and build
    // cout << "string: " << strng << endl;
    // cout << "column: " << column << endl;
    // cout << "state: " << state << endl;
    switch (state)
    {
      case 1:
        ptree.insert("command", strng); //this is select
        break;
      case 2:
        ptree.insert("fields", strng);
        break;
      case 4:
        ptree.insert("table_name", strng);
        break;
      case 5:
        if (strng == "(") {ptree.insert("condition", strng); break;}
        ptree.insert("where", "yes"); //where moment
        break;
      case 6:
        ptree.insert("condition", strng);
        break;
      case 7:
        ptree.insert("condition", strng);
        break;
      case 8:
        ptree.insert("condition", strng);
        break;
      case 9:
        ptree.insert("condition", strng);
        break;

      case 10:
        ptree.insert("command", strng);
        break;
      case 12:
        ptree.insert("table_name", strng);
        break;
      case 14:
        ptree.insert("col", strng);
        break;

      case 20:
        ptree.insert("command", strng);
        break;
      case 22:
        ptree.insert("table_name", strng);
        break;
      case 24:
        ptree.insert("values", strng);

      default:
        break;
    }
  }
}

mmap_ss Parser::parse_tree()
{
  return ptree;
}