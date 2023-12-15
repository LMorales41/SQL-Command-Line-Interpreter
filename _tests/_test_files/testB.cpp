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
  vector<string> commandstrngs = 
  {
    "make table company fields name, location, industry, revenue",
    "insert into company values Microsoft, Seattle, Technology, 143015",
    // "select name, industry, revenue from company",
    // "select * from company where revenue > 100000",
    // "select * from company where location like 'S%'",
    "make table project fields name, startyear, endyear, budget",
    "insert into project values WebApp, 2021, 2023, 50000",
    "select * from company",
    "select * from project"


  };
  //string str = "create table loo's fields   22.2,       name1,         name2,      gen, color";
  SQL sql;
  Table t;

  for (int i = 0;i < commandstrngs.size(); i++)
  {
    cout << "==========================================================" << endl;
    cout << "running this command: " << commandstrngs[i] << endl;
    //cout << sql.command(commandstrngs[i]) << endl;
    cout << (t = sql.command(commandstrngs[i])) << endl;
    cout << "basic_test: records selected: "<<sql.select_recnos() << endl;
    cout << "==========================================================" << endl;
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

