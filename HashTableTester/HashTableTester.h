#pragma once

#include <vector>
#include <assert.h>
#include <random>
#include "..\HashTable\HashTable.h"

class HashTableTester
{
public:
	HashTableTester(bool useConsoleOutput);
	~HashTableTester() = default;
	void test(const int size);

private:
	int m_maxSize = 0;
	bool m_useConsoleOutput = false;
	
	void constructor() const;
	void destructor() const;
	void addElemAndContains() const;
	void remove() const;
	void squareBracketOperator() const;
	void assignAndCopy() const;

	void checkPresenceOfElements(HashTable table, const int value, const int key) const;
	void checkAbsenceOfElements(HashTable table, const int value, const int key) const;
	void checkAssignEquality(HashTable table1, HashTable table2, std::vector<int> keys) const;
	void checkAssignInequality(HashTable table1, HashTable table2, std::vector<int> keys) const;

};

