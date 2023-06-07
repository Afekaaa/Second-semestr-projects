#pragma once

#include <iostream>
class HashTable
{
public:
	class BlockOfChain
	{
	public:
		BlockOfChain();
		BlockOfChain(const int key);
		BlockOfChain(BlockOfChain& otherString);
		~BlockOfChain();

		bool isEmpty() const;
		void setEmpty(const bool empty);

		int key() const;
		BlockOfChain* next();

		void setKey(const int key);
		void setNext(const BlockOfChain* nextString);

	private:
		int m_key = 0;
		BlockOfChain* m_next = nullptr;
		bool m_empty = true;
	};

	HashTable();
	HashTable(const int* mas, const int size);
	HashTable(HashTable& otherHashTable);
	~HashTable();

	int hash(const int key) const;
	int hash0(const int key) const;

	int size() const;

	void setElem(const int key);
	bool delElem(const int key);
	bool contains(const int key);

	void show();

	HashTable& operator = (const HashTable otherHashTable);
	BlockOfChain*& operator [] (const int hash);

private:
	BlockOfChain** m_hashTable = nullptr;
	int m_size = 0;
};

