#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/sql/sql.h"
#include "../../includes/table/table.h"
#include "../../includes/parser/parser.h"
#include "../../includes/table/typedefs.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_tree(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }

  BPlusTree<int> bpt;
  BPlusTree<int> bptree;
  for (int i = 0; i < 100; i++)
  {

    // if (i == 10)
    // {
    //   bpt.insert(i);
    // }
    // if (i == 50)
    // {
    //   bpt.insert(i);
    // }
    bpt.insert(i);
  }
  cout << bpt << endl;
  cout << bpt.contains(2) << endl;
  cout << bpt.contains(1) << endl;
  cout << bpt.contains(4) << endl;
  cout << (bpt.get_existing(4)) << endl;
  cout << "what does the fox say: " <<(bpt.get_existing(100)) << endl;
  cout << "on something that exists: " << *(bpt.find_ptr(20)) << endl;
  cout << "about as real as my girlfriend: " << bpt.find_ptr(101) << endl;

  cout << "real as taxes: " << *bpt.find(69) << endl;

  cout << "amount of people that love me: ";
  bpt.find(-1);

  cout << bpt << endl;


  // bptree = bpt;
  // cout << bptree << endl;
  //this works
  // BPlusTree<int>::Iterator itr = bpt.begin();


  // cout << "testing iterators for base bpt: " << endl;
  // cout << *itr << endl;
  // itr++;
  // cout << *itr << endl;
  // itr++;
  // cout << *itr << endl;

  // cout << "testing the copy now: " << endl;
  // BPlusTree<int> bptree;
  // bptree.copy_tree(bpt);
  // itr = bptree.begin();
  // cout << *itr << endl;
  // itr++;
  // cout << *itr << endl;
  // itr++;
  // cout << *itr << endl;
  return true;
}

bool test_sql(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  SQL sql;
  Table students;
  Table books;
  Table orders;
  Table employees;

  vectorstr insertlines = 
  {
    "make table employees fields \"employee_id\" name salary",
    "insert employees values 101 \"John Doe\" 50000",
    "insert into employees values 102 \"Jane Smith\" 60000",
    "insert into employees values 103 \"Bob Johnson\" 55000",
    "create table students fields id name age",
    "insert into employees values 104 \"Alice Williams\" 70000",
    "insert employees values 105 \"Michael Johnson\" 55000",
    "insert into employees values 106 \"Emily Davis\" 62000",
    "insert employees values 107 \"Daniel White\" 48000",
    "make table books fields isbn title author price",
    "insert employees values 108 \"Olivia Martin\" 58000",
    "insert employees values 109 \"Matthew Turner\" 65000",
    "insert employees values 110 \"Sophia Harris\" 53000",
    "create table orders fields \"order_id\" quantity",
    "insert employees values 111 \"David Anderson\" 70000",
    "insert employees values 112 \"Emma Taylor\" 48000",
    "insert employees values 113 \"Christopher Lee\" 72000",
    "insert into employees values 114 \"Isabella Wright\" 55000",
    "insert into employees values 115 \"Ethan Martinez\" 59000",
    "insert employees values 116 \"Ava Rodriguez\" 67000",
    "insert employees values 117 \"Mia Clark\" 51000",
    "insert employees values 118 \"James Baker\" 63000",
    "insert employees values 119 \"Sophie Garcia\" 50000",
    "insert employees values 120 \"Logan Smith\" 55000",
    "insert employees values 121 \"Grace Walker\" 60000",
    "insert employees values 122 \"Jackson Wright\" 54000",
    "insert employees values 123 \"Chloe Davis\" 67000",
    "insert employees values 124 \"Lucas Taylor\" 52000",
    "insert employees values 125 \"Avery Turner\" 48000",
    "insert employees values 126 \"Zoe Wilson\" 55000",
    "insert employees values 127 \"Caleb Reed\" 71000",
    "insert employees values 128 \"Nora Martin\" 59000",
    "insert employees values 129 \"Henry Phillips\" 64000",
    "insert employees values 130 \"Lily Moore\" 53000"

  };
  employees = sql.command(insertlines[0]);
  for (int i =1 ; i < insertlines.size(); i++)
  {
    if (i == 4 )
    {
      students = sql.command(insertlines[i]);
      i++;
    }
    if (i == 9)
    {
      books = sql.command(insertlines[i]);
      i++;
    }
    if (i == 13)
    {
      orders = sql.command(insertlines[i]);
      i++;
    }
    sql.command(insertlines[i]);
  }
  cout << employees << endl;
  cout << students << endl;
  cout << orders << endl;
  cout << books << endl;


  return true;
}




TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_TREE, TestTree) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_tree(false));
}


// TEST(TEST_SQL, TestSql) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

//   EXPECT_EQ(1, test_sql(false));
// }




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

