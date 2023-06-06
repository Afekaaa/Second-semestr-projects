#pragma once

#include <iostream>
class HashTable
{
public:
	class String
	{
	public:
		String();
		String(String& otherString);

		bool isEmpty() const;

		int key() const;
		String* next();

		void setKey(const int key);
		void setNext(const String* nextString);

	private:
		int m_key = 0;
		String* m_next = nullptr;
		
		bool m_empty = true;
	};

	HashTable();
	HashTable(HashTable& otherHashTable);
	~HashTable();

	int hash(const int hashBefore, const int i) const;
	int hash0(int key) const;

	int size() const;
	String* hashTable() const;

	void setElem(const int key);
	int delElem(const int key);
	bool contains(const int key);

	void show();

	HashTable& operator = (const HashTable otherHashTable);
	String*& operator [] (const int hash);

private:
	String** m_hashTable = nullptr;
	int m_size = 0;
	int m_hash0 = 0;
};

