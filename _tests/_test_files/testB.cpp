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

bool test_sql(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  string str = "make table employee fields  last,       first,         dep,      salary, year";
  SQL sql;
  sql.command(str);
  str =  "select * from employee";
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_SQL, TestSql) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_sql(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

