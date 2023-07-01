#pragma once

#include <iostream>

class HashTable
{
public:
	class Node
	{
	public:
		Node();
		Node(const int value, const int key);
		Node(Node& otherString);
		~Node() = default;

		bool isEmpty() const;
		void setEmpty(const bool empty);

		int& value();
		int key() const;
		Node* next();

		void setValue(const int value);
		void setKey(const int key);
		void setNext(Node* nextString);

	private:
		int m_value = 0;
		int m_key = 0;
		Node* m_next = nullptr;
		bool m_empty = true;
	};

	HashTable();
	HashTable(const int size);
	HashTable(const int* values, const int* keys, const int lenMas, const int size);
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
	int& operator [] (const int key);

private:
	Node** m_hashTable = nullptr;
	int m_size = 0;
};


