#pragma once

#include <vector>
#include <assert.h>
#include <random>
#include "..\HashTable\HashTable.h"

struct Block
{
	int value;
	int key;
};

class HashTableTester
{
public:
	HashTableTester(const bool useConsoleOutput);

	void test(const int size);

private:
	bool m_useConsoleOutput;
	int m_maxSize;

	void constructors();
	void addElemAndContains();
	void remove();
	void assign();
	void squareBracketOperator();

	void checkPresenceOfElements(HashTable table, const int value, const int key) const;
	void checkAbsenceOfElements(HashTable table, const int value, const int key);
	void checkRemove() const;
	void checkAssign() const;
	void checkSquareBracketOperator() const;
};

