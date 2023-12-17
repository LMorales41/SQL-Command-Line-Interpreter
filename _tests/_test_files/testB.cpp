#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/sql/sql.h"
#include "../../includes/table/table.h"
#include "../../includes/parser/parser.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/shunting_yard/shunting_yard.h"
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

  //BPlusTree<int> bpt;
  //time to test mmap
  MMap <int, int> bpt;
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
    bpt.insert(i, i+1);
  }
  cout << bpt << endl;
  cout << bpt.contains(2) << endl;
  cout << bpt.contains(1) << endl;
  cout << bpt.contains(4) << endl;
  // cout << (bpt.get_existing(4)) << endl;
  // cout << "what does the fox say: " <<(bpt.get_existing(100)) << endl;
  // cout << "on something that exists: " << *(bpt.find_ptr(20)) << endl;
  // cout << "about as real as my girlfriend: " << bpt.find_ptr(101) << endl;

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
  bool debug2 = false;
  if(debug)
  {
    SQL sql;
    Table t;
    Table playerTable;
    Table clubsTable;
    vectorstr commands = {
      "make table players fields fname, lname, age, position, team",
      "insert into players values Julian, Marin, 17, Winger, \"18AA\"",
      "insert into players values Adam, Scott, 17, Winger, \"18AA\"",
      "insert into players values Jared, Padilla, 18, Center, \"18AA\"",
      "insert into players values Anthony, Aceves, 17, Defense, \"18AA\"",
      "insert into players values Jayden, Deguzman, 16, Defense, \"16AA\"",
      "insert into players values Aiden, Zakaria, 16, Center, \"16AA\"",
      "insert into players values Collin, \"O'Brian\", 15, Winger, \"16AA\"",
      "insert into players values Rafe, Armstrong, 16, Defense, \"16AA\"",
      "insert into players values Taiki, Schneider, 16, Winger, \"16AA\"",
      "insert into players values Garion, Barber, 16, Center, \"16AA\"",
      "insert into players values Sebastian, Benavente, 16, Winger, \"16AA\"",
      "insert into players values Liam, Carson, 11, Defense, \"12B\"",
      "insert into players values Damien, Boucher, 11, Center, \"12B\"",
      "insert into players values Bella, Gao, 11, Winger, \"12B\"",
      "insert into players values Reagan, Ludlow, 11, Winger, \"12B\"",
      "insert into players values Patrick, Guerra, 12, Defense, \"12B\"",
      "insert into players values Qnoxx, \"Decker-Knealing\", 11, Winger, \"12B\"",
      "make table clubs fields name, numTeams, championships, \"year founded\"",
      "insert into clubs values Empire, 10, 06, 2010",
      "insert into clubs values \"Jr. Kings\", 20, 45, 1996",
      "insert into clubs values Wave, 16, 25, 2002",
      "insert into clubs values \"Jr. Ducks\", 22, 40, 1998",
      "insert into clubs values Bears, 18, 17, 1999",
      "insert into clubs values \"Maple Leafs\", 08, 03, 2004",
      "insert into clubs values OC, 12, 08, 2008"
    };
    for(int i = 0; i < commands.size(); i++)
    {
      cout << ">" << commands[i] << endl;
      t = sql.command(commands[i]);
      if(i == 17)
        playerTable = t;
      // cout << "__________\n\n" << t << "________\n"; //inserts and makes work
    }
    clubsTable = t;
    cout << playerTable << "______\n\n" << clubsTable << "\n_____\n";
    vectorstr select_commands = {
      // "select lname, age, fname from players where lname > G and fname < H or age <= 16"
      "select * from clubs",
      "select name from clubs where \"year founded\" <= 2001 and \"year founded\" > 2001",//and
      "select fname from players where position = Defense or age >= 17 and fname > J",//or and
      "select fname, lname from players where fname > H and lname < K and position = Defense",//and and
      "select team, fname from players where fname > J and fname < T or team >= \"16\" and age <= 17",//and or and
      "select lname, fname, age from players where position = Winger or age >=16 and position = Defense or lname < N",//or and or
      "select * from players where age > 19 or fname > J",//empty or full solution
      "select * from players where age <= 17 or fname = Alex",//full or empty
      "select * from players where age > 19 or fname = Alex",//empty or empty
      "select * from players where age > 19 and fname > J",//empty and full
      "select lname, fname, position from players where age <= 17 and fname = Alex",//full and empty
      "select lname, fname, position from players where age > 18 and fname = Alex",//empty and empty
      "select lname, fname, position from players where (age <= 16 or fname > J and (lname > D)) and position = Defense"
    };

    for(int i = 0; i < select_commands.size(); i++)
    {
      cout << "\n_____________\n\n" << ">" << select_commands[i] << endl << sql.command(select_commands[i]);
      cout << sql.select_recnos() << "_________\n\n";
    }
    
  }

  return true;
}
// bool test_one(bool debug = false)
// {
//   Table t ("game", {"name, year, rating"});
//   SQL sql;
//   vectorstr row = {"pokemon", "1986", "E"};
//   t.insert_into(row);
  
//   string line = "select * from game where year > 2000";
//   cout << sql.command(line) << endl;
//   return true;
// }

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

  EXPECT_EQ(1, test_sql(true));
}

// TEST(TEST_ONE, TestOne)
// {
//   EXPECT_EQ(1, test_one(false));
// }



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

