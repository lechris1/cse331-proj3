#include <iostream>
using std::cout; using std::endl;

#include "HashTable.h"

int main() {

    // we prefer sizes that are power of 2 (helps with growing and shrinking)
    HashTable hashTable(5);

    hashTable.insert("abe", "sucks");
    hashTable.insert("project3", "is fun!");
    cout << "After inserting abe, project3:\n" << hashTable << endl;

    // insert a pre-existing element
    hashTable.insert("abe", "wut :(");
    cout << "After inserting abe:\n" << hashTable << endl;

    // remove an element
    hashTable.remove("abe");
    cout << "After deleting abe, table halfs:\n" << hashTable << endl;

    hashTable.insert("msu", "go green!");
    cout << "After inserting msu:\n" << hashTable << endl;
    hashTable.insert("fatema", "is awesome!");
    cout << "After inserting fatema, table gets doubled:\n" << hashTable << endl;
    hashTable.insert("onsay", "rocks!");
    cout << "After inserting onsay:\n" << hashTable << endl;
    hashTable.insert("cse331", "is important!");
    hashTable.insert("hashing!", "is very useful");
    hashTable.insert("scott", "kicks butt!");
    cout << "After inserting cse331,hashing,scott, table gets doubles:\n" << hashTable << endl;
    hashTable.insert("computer", "science");
    cout << "After inserting computer:\n" << hashTable << endl;
    hashTable.insert("science", "computer :O");
    cout << "After inserting science, table gets doubled:\n" << hashTable << endl;

    auto searchAbe = hashTable.get("computer");
    cout << "Searching: computer maps to "
         << (searchAbe == nullptr ? "NOT FOUND" : *searchAbe) << ".\n\n";
    auto searchOwen = hashTable.get("owen");
    cout << "Searching: bOwen is "
         << (searchOwen == nullptr ? "NOT FOUND" : *searchOwen) << ".\n\n";

    hashTable.remove("hashing!");
    cout << "After deleting 'hashing!' :( :\n" << hashTable << endl;

    auto searchComputer = hashTable.get("computer");
    cout << "Searching: computer maps to "
         << (searchComputer == nullptr ? "NOT FOUND" : *searchComputer) << ".\n\n";

    cout << "Number of items in the hash table: " << hashTable.size() << endl;

    hashTable.remove("msu");
    hashTable.remove("science");
    hashTable.remove("cse331");
    hashTable.remove("project3");
    cout << "\nAfter deleting msu,science,cse331,project3 table halves:\n" << hashTable << endl;
    cout << "Number of items in the hash table: " << hashTable.size() << endl;

    return 0;
}
