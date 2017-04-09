/**
 * \author YOUR_NAME
 * \netid YOUR_NETID
 * \brief ENTER_DESCRIPTION
 *
 * \file HashTable.h
 */

/** DO NOT MODIFY THE LINE BELOW THIS. IT WILL BE USED FOR TESTING. */
#define UNIT_TEST

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
 * Complete the following function and add a function comment header.
 */
HashTable::HashTable(size_t m) : mNumChains(m), mNumItems(0) {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
void HashTable::insert(string key, string value) {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
void HashTable::remove(string key) {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
const string *HashTable::get(string key) const {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
uint64_t HashTable::HashFunction(uint64_t key) const {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
void HashTable::Double() {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
void HashTable::Shrink() {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
void HashTable::Rehash(size_t originalSize) {
	throw MissingImplementationException();
}

/**
 * Complete the following function and add a function comment header.
 */
HashTable::~HashTable() {
	throw MissingImplementationException();
}
