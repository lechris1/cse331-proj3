#include <iostream>
using std::cout;
using std::endl;
#include "gtest/gtest.h"
#include "src/HashTable.h"
#include <vector>
using std::vector;
#include <cmath>
#include <algorithm>
#include <fstream>

/** Testing for the Hash Table Project.
 */
class HashTableProjectTests : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
    }
  private:
    FRIEND_TEST(HashTableProjectTests, TestHashTableInstance);
    FRIEND_TEST(HashTableProjectTests, TestHashTableInsert);
    FRIEND_TEST(HashTableProjectTests, TestHashTableSingleElementTable);
    FRIEND_TEST(HashTableProjectTests, TestHashTableRemove);
    FRIEND_TEST(HashTableProjectTests, TestHashTableSearch);

    // virtual void TearDown() {}
};

/** Tests to make sure Hash Table can be Instantiated.
 */
TEST_F(HashTableProjectTests, TestHashTableInstance)
{
    // default ctor
    HashTable t(5);
    EXPECT_TRUE(t.mNumItems == 0) << "Empty HashTable should have zero items.";
		EXPECT_TRUE(t.mNumChains == 5) << "HashTable should have 5 chains if 5 is "
              "passed to the constructor.";

    for (int i = 0; i < t.mNumChains; i++)
    {
        EXPECT_EQ(t.mChainArray[i], nullptr) << "All of the chains should "
          "point to nullptr on initialization.";
    }
}

/** Tests for inserting into the Hash Table.
 */
TEST_F(HashTableProjectTests, TestHashTableInsert)
{
    // default ctor
    HashTable t(2);

    // inserting into an empty hashtable
    t.insert("test", "ing");
    EXPECT_TRUE(t.mChainArray[1] != nullptr) << "The key 'test' maps to chain #3.";
    EXPECT_TRUE(t.mChainArray[1]->mValue == "ing") << "The value 'ing' should "
                    "belong to the key 'test' in chain 3 index 0.";

    // inserting with the same key to overwrite the value
    t.insert("test", "123");
    EXPECT_TRUE(t.mChainArray[1]->mValue == "123") << "Inserting a key that "
                    "already exists should overwrite the old value.";

    // insert and cause a collision
    t.insert("collide!", "; )");
    EXPECT_TRUE(t.mChainArray[1]->mNext != nullptr) << "The key 'collide!' will"
                    " cause a collision which grows chain 3 by one.";
    EXPECT_TRUE(t.mChainArray[1]->mNext->mValue == "; )") << "A collision"
                    "should still insert the value normally.";

    // make one more insert to cause the table to grow
    t.insert("grow", "large");
    EXPECT_TRUE(t.mNumChains == 4) << "Inserting an item when n == m should"
                    "cause the table to grow to size 2m.";
    EXPECT_TRUE(t.mChainArray[2] != nullptr) << "The key 'grow' maps to chain #2.";
    EXPECT_TRUE(t.mChainArray[2]->mValue == "large") << "The value inserted "
                    "for key 'grow' should = 'large'.";
}

/** Tests for removing from the Hash Table.
 */
TEST_F(HashTableProjectTests, TestHashTableRemove)
{
    // test the shrinking
    //
    HashTable t(2);
	  // insert manually to avoid using HashTable::insert
    string testKeyStr = "test_remove";
	  auto hash = t.HashFunction(customStringPreHash(testKeyStr));
    auto node = new HashTable::ChainNode(customStringPreHash(testKeyStr), "work");
	  t.mChainArray[hash] = node;
    t.mNumItems++;

    // removing the single element to cause a shrink
    t.remove(testKeyStr);
    EXPECT_EQ(t.mNumChains, 1) << "Removing from a table of size 2 should shrink"
                    " the take to size 1.";

    // remove an element that is not in the table
    EXPECT_NO_THROW(t.remove("not there!")) << "Removing an item from the "
                "hash table that does not exist should do nothing.";

    // use the struct as a home for the nested function
	  struct tableWithChainOfSizeThree {
        static void makeChainWithSizeThree(HashTable &table) {
            string testKeyStr1 = "sample1";
            auto hash1 = table.HashFunction(customStringPreHash(testKeyStr1));
            auto node1 = new HashTable::ChainNode(customStringPreHash(testKeyStr1), "work1");
            table.mChainArray[hash1] = node1;
            table.mNumItems++;
//					  cout << table << endl;
            string testKeyStr2 = "is";
            auto hash2 = table.HashFunction(customStringPreHash(testKeyStr2));
            auto node2 = new HashTable::ChainNode(customStringPreHash(testKeyStr2), "work2");
            table.mChainArray[hash2]->mNext = node2;
            table.mNumItems++;
//					  cout << table << endl;

            string testKeyStr3 = "they";
            auto hash3 = table.HashFunction(customStringPreHash(testKeyStr3));
            auto node3 = new HashTable::ChainNode(customStringPreHash(testKeyStr3), "work3");
            table.mChainArray[hash3]->mNext->mNext = node3;
            table.mNumItems++;
//					  cout << table << endl;
        }
    };

  // make a table with chain size 3
  HashTable table(4);
  tableWithChainOfSizeThree::makeChainWithSizeThree(table);

  // remove item at the head
  table.remove("sample1");
  EXPECT_EQ(table.size(), 2) << "Removing one element from a table of size"
            " 3 should result in a table of size 2.";

  // the 1 is fixed from makeChainWithSizeThree
  EXPECT_EQ(table.mChainArray[1]->mValue, "work2") << "Removing the head of"
            " a chain of size > 1 should shift the chain left by one.";

  // start fresh to remove node in the center
  HashTable table2(4);
  tableWithChainOfSizeThree::makeChainWithSizeThree(table2);

  table2.remove("is");
  EXPECT_EQ(table2.mChainArray[1]->mNext->mValue, "work3") << "Removing "
            "node in the center of the chain should link the previous with"
            " the removed nodes next.";

  // start fresh to remove node at the tail
  HashTable table3(4);
  tableWithChainOfSizeThree::makeChainWithSizeThree(table3);

  table3.remove("they");
  EXPECT_EQ(table3.mChainArray[1]->mNext->mNext, nullptr) << "Removing the"
            " tail should cause the node before the tail to point to "
            "nullptr.";
}

/** Tests for table of size 1 (it is a special case for growing/shrinking)
 */
TEST_F(HashTableProjectTests, TestHashTableSingleElementTable) {
  // default ctor
  HashTable t(1);

  t.insert("single", "chain"); // does not grow yet
  // n >= (m/4) is true but if we have we will become size 0. I did
  // not think it would make sense for the hash table to ever become
  // size 0 but it may be more plausible if the size was permitted to
  t.remove("single");

  EXPECT_EQ(t.size(), 0) << "removing an element from a hashtable of "
            "size 1 should half to size 0.";

  EXPECT_EQ(t.mNumChains, 0) << "removing an element from a hashtable of "
            "size 1 should half the number of chains to 0.";

  // size zero should grow to 1
  t.insert("single", "chain"); // does not grow yet

  EXPECT_EQ(t.size(), 1) << "inserting an element into a hashtable of "
            "size 0 should grow the size to 1.";

  EXPECT_EQ(t.mNumChains, 1) << "inserting an element into a hashtable of "
            "size 0 should double the number of chains to 1.";
}

/** Tests for searching within the hash table.
 */
TEST_F(HashTableProjectTests, TestHashTableSearch)
{
    
    HashTable t(5);

    // inserting some values
    t.insert("computer", "science!");
    t.insert("ibrahim", "is smart!");
    t.insert("engineering", "is fun!");

    //value exists at the front of a chain
    EXPECT_EQ(t.get("computer"), &t.mChainArray[2]->mValue) << "Seaching for"
              " a value at the front of a chain should return a pointer to it";

    //value does not exist
    EXPECT_EQ(t.get("fatema"), nullptr) << "Seaching for"
              " a value that does not exist should return nullptr";

    //searching for an element at the middle of a chain
    EXPECT_EQ(t.get("ibrahim"), &t.mChainArray[2]->mNext->mValue) << "Seaching for"
              " a value at the middle of a chain should return a pointer to it";   

    //searching for an element at the end of a chain
    EXPECT_EQ(t.get("engineering"), &t.mChainArray[2]->mNext->mNext->mValue) << "Seaching for"
              " a value at the end of a chain should return a pointer to it"; 

}
