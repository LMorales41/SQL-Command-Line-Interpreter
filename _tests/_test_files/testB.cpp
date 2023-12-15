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
  bpt.insert(1);
  bpt.insert(2);
  bpt.insert(3);
  cout << bpt << endl;
  BPlusTree<int>::Iterator itr = bpt.begin();


  cout << "testing iterators for base bpt: " << endl;
  cout << *itr << endl;
  itr++;
  cout << *itr << endl;
  itr++;
  cout << *itr << endl;

  cout << "testing the copy now: " << endl;
  BPlusTree<int> bptree;
  bptree.copy_tree(bpt);
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
  vector<Table> holding = {students, books, orders, employees};
  vectorstr commandlines = 
  {
    "create table students fields id name age",
    "make table books fields isbn title author price",
    "create table orders fields \"order_id\" quantity",
    "make table employees fields \"employee_id\" name salary"
  };
  for (int i = 0; i < commandlines.size(); i++)
  {
    holding[i] = sql.command(commandlines[i]);
  }

  vectorstr insertlines = 
  {
    "insert employees values 101 \"John Doe\" 50000",
    "insert into employees values 102 \"Jane Smith\" 60000",
    "insert into employees values 103 \"Bob Johnson\" 55000",
    "insert into employees values 104 \"Alice Williams\" 70000"
  };
  for (int i =0 ; i < insertlines.size(); i++)
  {
    sql.command(insertlines[i]);
  }

  for (int i =0 ; i < holding.size(); i++)
  {
    cout << holding[i] << endl;
  }
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

// TEST(TEST_TREE, TestTree) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

//   EXPECT_EQ(1, test_tree(false));
// }


TEST(TEST_SQL, TestSql) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sql(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

