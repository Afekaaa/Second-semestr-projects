#include <iostream>
#include "HashTable.h"

HashTable::HashTable()
{
	m_size = 7;
	m_hashTable = new BlockOfChain*[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_hashTable[i] = new BlockOfChain();
	}
}

HashTable::HashTable(const int* mas, const int size)
{
	m_size = size + 10;
	m_hashTable = new BlockOfChain*[m_size];
	
	for (int i = 0; i < size; ++i)
	{
		m_hashTable[i] = new BlockOfChain(mas[i]);
	}

	for (int i = size; i < m_size; ++i)
	{
		m_hashTable[i] = new BlockOfChain;
	}
}

HashTable::HashTable(HashTable& otherHashTable)
{
	m_size = otherHashTable.size();
	m_hashTable = new BlockOfChain*[m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_hashTable[i] = new BlockOfChain(*otherHashTable[i]);
	}
	
}

HashTable::~HashTable()
{
	for (int i = 0; i < m_size; ++i)
	{
		delete m_hashTable[i];
	}

	delete m_hashTable;
}

int HashTable::hash0(int key) const
{
	if (key < 0)
		return m_size - std::abs(key) % m_size;
	return key % m_size;
}

int HashTable::hash(const int hashBefore, const int i) const
{
	const float a = (std::sqrt(5) - 1) / 2;
	int hash = int((hashBefore * m_size) * a) % m_size;

	return hash;
}

int HashTable::size() const
{
	return m_size;
}

void HashTable::setElem(const int key)
{
	int hash = hash0(key);

	if (m_hashTable[hash]->isEmpty())
		m_hashTable[hash]->setKey(key);
	else
	{
		BlockOfChain* runner = m_hashTable[hash];
		while (runner = runner->next());

		runner = new BlockOfChain(key);
	}
}

bool HashTable::delElem(const int key)
{
	if (!contains(key))
		return false;

	int hash = hash0(key);

	if (!m_hashTable[hash]->isEmpty())
	{
		BlockOfChain* runner = m_hashTable[hash];

		if (runner->key() == key)
		{
			BlockOfChain* tmpPointer = runner->next();
			delete runner;
			m_hashTable[hash] = tmpPointer;

			return true;
		}

		else if ((runner = runner->next())->key() == key)
		{	
			m_hashTable[hash] = runner->next();
			delete runner;

			return true;
		}

		else 
		{
			runner = runner->next();
			BlockOfChain* secondRunner = m_hashTable[hash];

			while (runner)
			{
				if (runner->key() == key)
				{
					secondRunner->setNext(runner->next());
					delete runner;

					return true;
				}

				runner = runner->next();
				secondRunner = secondRunner->next();
			}
		}
	}

	return false;
}

bool HashTable::contains(const int key)
{
	int hash = hash0(key);

	if (!m_hashTable[hash]->isEmpty())
	{
		BlockOfChain* runner = m_hashTable[hash];

		while (runner)
		{
			if (runner->key() == key and !runner->isEmpty())
				return true;
			runner = runner->next();
		}
	}
	return false;
}

void HashTable::show()
{
	std::cout << "Hash\t" << "Key\t" << "Next\t" << std::endl;

	for (int i = 0; i < m_size; i++)
	{
		if (m_hashTable[i]->isEmpty())
			std::cout << i << "\t" << "empty\t empty\t" << std::endl;
		else
		{
			std::cout << i << "\t" << m_hashTable[i]->key() << "\t";
			BlockOfChain* runner = m_hashTable[i]->next();

			while (runner)
				std::cout << runner->key() << "\t";

			std::cout << std::endl;
		}

	}
}

HashTable& HashTable::operator = (HashTable otherHashTable)
{
	m_size = otherHashTable.size();
	delete [] m_hashTable;

	//HashTable(otherHashTable);

	return *this;
}

HashTable::BlockOfChain*& HashTable::operator [] (const int hash)
{
	if (hash >= 0 and hash < m_size)
		return m_hashTable[hash];
}

#include <random>

int main()
{
	srand(time(0));
	const int lenMas = 10;
	int* mas = new int[lenMas];

	for (int i = 0; i < lenMas; ++i)
		mas[i] = rand() % 100;

	HashTable T(mas, lenMas);

}
