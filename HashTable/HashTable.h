#pragma once

#include <iostream>

class HashTable
{
public:
	class BlockOfChain
	{
	public:
		BlockOfChain();
		BlockOfChain(const int value, const int key);
		BlockOfChain(BlockOfChain& otherString);
		~BlockOfChain();

		bool isEmpty() const;
		void setEmpty(const bool empty);

		int value() const;
		int key() const;
		BlockOfChain* next();

		void setValue(const int value);
		void setKey(const int key);
		void setNext(const BlockOfChain* nextString);

	private:
		int m_value = 0;
		int m_key = 0;
		BlockOfChain* m_next = nullptr;
		bool m_empty = true;
	};

	HashTable();
	HashTable(const int * values, const int* keys, const int size);
	HashTable(HashTable& otherHashTable);
	~HashTable();

	int hash(const int key) const;
	int hash0(const int key) const;

	int size() const;

	void addElem(const int value, const int key);
	bool remove(const int value, const int key);
	bool contains(const int value, const int key);

	void show();

	HashTable & operator = (const HashTable otherHashTable);
	BlockOfChain*& operator [] (const int hash);

private:
	BlockOfChain** m_hashTable = nullptr;
	int m_size = 0;
};

