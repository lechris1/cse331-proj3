/**
 * \author Christopher Le
 * \netid lechris1
 * \brief Implement a HashTable with an array of chainnodes
 *
 * \file HashTable.h
 */

/** DO NOT MODIFY THE LINE BELOW THIS. IT WILL BE USED FOR TESTING. */
//#define UNIT_TEST

// C++ code
#include <iostream>
#include <vector>
#include <string>
#include <math.h>       // floor()
#include <iomanip>
#include <cmath>
#include <ostream>
#include "Exceptions.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostream;

/**
 * We're using a custom hash so that all students end up with the same results. std::hash varies.
 *
 * @param data String to hash
 * @return The hash of data.
 */
uint64_t customStringPreHash(string &data) {
	uint64_t hash = 0;

	for (auto &ch : data) {
		hash += ch;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 7);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}


class HashTable {
#if defined(UNIT_TEST)
	FRIEND_TEST(HashTableProjectTests, TestHashTableSingleElementTable);
	FRIEND_TEST(HashTableProjectTests, TestHashTableInstance);
	FRIEND_TEST(HashTableProjectTests, TestHashTableInsert);
	FRIEND_TEST(HashTableProjectTests, TestHashTableRemove);
	FRIEND_TEST(HashTableProjectTests, TestHashTableSearch);
#endif
public:
	HashTable(size_t m);

	~HashTable();

	/// Delete copy/default/= ctor
	HashTable() = delete;

	HashTable(const HashTable &table) = delete;

	void operator=(const HashTable &table) = delete;

	void insert(string key, string value);

	void remove(string key);

	const string *get(string value) const;

	size_t size() const { return mNumItems; };

	friend ostream &operator<<(ostream &out, const HashTable &table) {
		for (size_t i = 0;
				 i < table.mNumChains; i++) {    // visit every chain in mChainArray
			out << "chain " << i << ": ";
			ChainNode *current = table.mChainArray[i];
			if (current == nullptr) {
				out << "EMPTY" << endl;
			} else {
				while (current != nullptr) {
					out << *current << " ---> ";
					current = current->next();
				}
				out << "END" << endl;
			}
		}
		return out;
	}

private:
	/**
	 * An item in a single chain, analogous to a node in a linked list.
	 * There is no need to modify this class.
	 */
	class ChainNode {
#if defined(UNIT_TEST)
	FRIEND_TEST(HashTableProjectTests, TestHashTableInstance);
	FRIEND_TEST(HashTableProjectTests, TestHashTableInsert);
	FRIEND_TEST(HashTableProjectTests, TestHashTableRemove);
	FRIEND_TEST(HashTableProjectTests, TestHashTableSearch);
	FRIEND_TEST(HashTableProjectTests, TestHashTableSingleElementTable);
#endif
	friend class HashTable;

	public:
		ChainNode(uint64_t key, string Value) :
				mHashedKey(key), mValue(Value), mNext(nullptr) {}

		ChainNode(ChainNode const &data) :
				mHashedKey(data.mHashedKey), mValue(data.mValue),
				mNext(data.mNext) {}

		// delete default ctor =op
		ChainNode() = delete;

		void operator=(const ChainNode &node) = delete;

		friend ostream &operator<<(ostream &out, const ChainNode &table) {
			out << "(" << table.mHashedKey << ", " << table.mValue << ")";
			return out;
		}

		ChainNode *next() const { return mNext; }

	private:
		/// The internal key (hash) of this item
		uint64_t mHashedKey;

		/// The value held by this item
		string mValue;

		/// Pointer to the next item in the chain
		ChainNode *mNext;
	};

	/// The current size of the hash table (number of chains). This value represents
	size_t mNumChains;                 // also known as m

	/// How many key-value pairs are in the hashtable
	size_t mNumItems;                // also know as n

	/// all of the chains, stored as an array of pointers
	ChainNode **mChainArray;

	uint64_t HashFunction(uint64_t key) const;

	void Double();

	void Shrink();

	void Rehash(size_t originalSize);
};

/**
 * Builds empty HashTable with a total m chains. All chains will be empty. m must be positive.
 * m: number of chains
 */
HashTable::HashTable(size_t m) : mNumChains(m), mNumItems(0), mChainArray(new ChainNode*[m]) {
	//initialize each chain to nullptrs
	for (size_t i = 0; i < m; i++)
	{
		mChainArray[i] = nullptr;
	}
}

/**
 * Add a key-value pair to the HashTable.
 * key: key
 * value: value of key
 */
void HashTable::insert(string key, string value) {
	//check for HashTable of size 0
	if (mNumChains == 0)
	{
		Double();
	}

	ChainNode* kv = new ChainNode(customStringPreHash(key), value); //new node for key and value
	ChainNode* whichchain = mChainArray[HashFunction(customStringPreHash(key))]; //find chain with hashedkey

	//insert if chain is empty
	if (!whichchain) {
		mChainArray[HashFunction(customStringPreHash(key))] = kv;
		mNumItems++;
	}
	//overwrite or insert at tail
	else {
		//iterate through chain
		while (whichchain) //check if ptr is nullptr
		{
			//if key already exists, value is overwritten with new value
			if (whichchain->mHashedKey == kv->mHashedKey)
			{
				whichchain->mValue = kv->mValue;
				delete kv; //kv isn't needed anymore
				return;
			}
			//insert at tail
			else if (!(whichchain->next()))
			{
				//when chain doesn't contain kv, insert at tail of chain
				whichchain->mNext = kv;
				mNumItems++;
				whichchain = whichchain->next(); //go to kv in chain
			}
			whichchain = whichchain->next(); //go to next node in chain
		}
	}

	//GROW
	if (mNumItems > mNumChains)
		Double();
}

/**
 * Remove a key-value pair from the HashTable.
 * key: key to remove
 */
void HashTable::remove(string key) {
	//check for HashTable of size 0
	if (mNumChains == 0)
		return;

	uint64_t hashedkey = customStringPreHash(key);
	ChainNode* whichchain = mChainArray[HashFunction(hashedkey)]; //find chain with hashedkey

	//empty chain has nothing to remove
	if (!whichchain)
	{
		return;
	}
	//if found key is first node, remove
	else if (whichchain && (whichchain->mHashedKey == hashedkey))
	{
		mChainArray[HashFunction(hashedkey)] = whichchain->mNext;
		mNumItems--;
	}
	//find key to remove
	else
	{
		//iterate through chain
		while (whichchain->next()) //check if ptr is nullptr
		{
			//remove node
			if (whichchain->next()->mHashedKey == hashedkey)
			{
				ChainNode* node = whichchain->next()->next();
				delete whichchain->mNext; //remove node
				whichchain->mNext = node; //point to next node
				mNumItems--;
				break;
			}
			whichchain = whichchain->next(); //go to next node in chain
		}
	}
	//SHRINK
	if (mNumItems <= mNumChains / 4)
		Shrink();
	return;
}

/**
 * Returns a pointer to the value of the key in the HashTable if found, otherwise returns nullptr.
 * key: key of value to find
 */
const string *HashTable::get(string key) const {
	//check for HashTable of size 0
	if (mNumChains == 0)
		return nullptr;

	uint64_t hashedkey = customStringPreHash(key);
	ChainNode* whichchain = mChainArray[HashFunction(hashedkey)]; //find chain with hashedkey

	//iterate through chain
	while (whichchain) //check if next is nullptr
	{
		//return ptr to value
		if (whichchain->mHashedKey == hashedkey)
			return &(whichchain->mValue);
		whichchain = whichchain->next(); //next node
	}
	return nullptr;
}

/**
 * Returns index of the chain key should be mapped to according to the division method.
 * key: prehashed key
 */
uint64_t HashTable::HashFunction(uint64_t key) const {
	return key % mNumChains;
}

/**
 * Grows the Hash Table such that m = 2m.
 */
void HashTable::Double() {
	size_t og = mNumChains;
	mNumChains *= 2;

	//check for HashTable of size 0
	if (mNumChains == 0)
		mNumChains = 1;

	Rehash(og);
}

/**
 * Shrinks the Hash Table such that m = m/2.
 */
void HashTable::Shrink() {
	size_t og = mNumChains;
	mNumChains /= 2;
	Rehash(og);
}

/**
 * Rehashes the items in the Hash Table to align with the current HashFunction.
 * originalSize: size of old chainarray to iterate through
 */
void HashTable::Rehash(size_t originalSize) {
	ChainNode **newChainArray = new ChainNode*[mNumChains]; //new ChainArray
	//init to nullptr
	for (size_t i = 0; i < mNumChains; i++)
	{
		newChainArray[i] = nullptr;
	}

	//iterate through chainarray
	for (size_t i = 0; i < originalSize; i++)
	{
		ChainNode* whichchain = mChainArray[i]; //current chain
		//iterate through chain
		while (whichchain)
		{
			//rehash node
			ChainNode* newchain = newChainArray[HashFunction(whichchain->mHashedKey)];

			//insert at start of chain
			if (!newchain)
			{
				ChainNode* node = whichchain;
				newChainArray[HashFunction(node->mHashedKey)] = node;
				whichchain = whichchain->next(); //next node in oldchain
				newChainArray[HashFunction(node->mHashedKey)]->mNext = nullptr;
			}
			//insert at tail
			else
			{
				//go to tail of new chain
				while (newchain->next())
				{
					newchain = newchain->next(); //go to next node in chain
				}
				ChainNode* node = whichchain;
				newchain->mNext = node; //reassign ChainNode to newChainArray
				whichchain = whichchain->next(); //next node in oldchain
				newchain->next()->mNext = nullptr;
			}
		}
	}

	delete[] mChainArray; //reallocate memory for newChainArray, but keep nodes
	mChainArray = newChainArray;
}

/**
 * HashTable Destructor
 */
HashTable::~HashTable() {
	//iterate through mChainArray
	for (size_t i = 0; i < mNumChains; i++)
	{
		ChainNode* & whichchain = mChainArray[i];
		//iterate through chain
		while (whichchain)
		{
			ChainNode* head = whichchain->next(); //save pointer to next node
			delete whichchain; //delete node
			whichchain = head;
		}
	}
	delete[] mChainArray;
}
