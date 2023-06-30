#include "HashTable.h"

HashTable::HashTable()
{
	m_size = 7;
	m_hashTable = new Node*[m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_hashTable[i] = new Node();
	}
}



HashTable::HashTable(const int * values, const int* keys, const int size)
{
	m_size = size + size * 0,1;
	m_hashTable = new Node*[m_size];
	
	for (int i = 0; i < m_size; ++i)
	{
		int hash1 = hash(keys[i]);
		m_hashTable[hash1] = new Node(values[i], keys[i]);
	}
}

HashTable::HashTable(HashTable& otherTable)
{
	m_size = otherTable.size();
	m_hashTable = new Node*[m_size];
	for (int i = 0; i < m_size; i++)
		m_hashTable[i] = new Node(*(otherTable.m_hashTable[i]));
}

HashTable::~HashTable()
{
	for (int i = 0; i < m_size; ++i)
		delete m_hashTable[i];

	delete[] m_hashTable;
}

int HashTable::hash0(const int key) const
{
	if (key < 0)
		return m_size - std::abs(key) % m_size;
	return key % m_size;
}

int HashTable::hash(const int key) const
{
	const float a = (std::sqrt(5) - 1) / 2;
	int hash = int((hash0(key) * m_size) * a) % m_size;

	return hash;
}

int HashTable::size() const
{
	return m_size;
}

void HashTable::addElem(const int value, const int key)
{
	int hash1 = hash(key);

	if (m_hashTable[hash1]->isEmpty())
	{
		m_hashTable[hash1]->setValue(value);
		m_hashTable[hash1]->setKey(key);
	}
	else
	{
		Node* runner = m_hashTable[hash1];

		while (runner->next())
		{
			if (runner->key() == key)
			{
				runner->setValue(value);
				return;
			}
			runner = runner->next();
		}

		if (runner->key() == key)
		{
			runner->setValue(value);
			return;
		}

		runner->setNext(new Node(value, key));
	}
}

bool HashTable::remove(const int value, const int key)
{
	if (!contains(value, key))
		return false;

	int hash1 = hash(key);

	Node* runner = m_hashTable[hash1];

	if (runner->value() == value)
	{
		m_hashTable[hash1] = runner->next();
		delete runner;

		return true;
	}
	else 
	{
		Node* secondRunner = runner;
		runner = runner->next();

		while (true)
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

	return false;
}

bool HashTable::contains(const int value, const int key)
{
	int hash1 = hash(key);

	if (!m_hashTable[hash1]->isEmpty())
	{
		Node* runner = m_hashTable[hash1];

		while (runner)
		{
			if (runner->value() == value and !runner->isEmpty())
				return true;
			runner = runner->next();
		}
	}
	return false;
}

void HashTable::show()
{
	std::cout << "Hash\t" << "Value\t" << "Key\t" << "Next\t" << std::endl;

	for (int i = 0; i < m_size; i++)
	{
		if (m_hashTable[i]->isEmpty())
			std::cout << i << "\t" << "empty\t empty\t empty\t" << std::endl;
		else
		{
			std::cout << i << "\t" << m_hashTable[i]->value() << "\t" << m_hashTable[i]->key() << "\t";
			Node* runner = m_hashTable[i]->next();

			while (runner)
				std::cout << runner->value() << " " << runner->key() << "\t";

			std::cout << std::endl;
		}
	}
}

HashTable& HashTable::operator = (HashTable otherHashTable)
{
	if (otherHashTable.m_hashTable != m_hashTable)
	{
		for (int i = 0; i < m_size; ++i)
			delete m_hashTable[i];
		delete[] m_hashTable;

		m_size = otherHashTable.size();

		m_hashTable = new Node * [m_size];
		for (int i = 0; i < m_size; i++)
			m_hashTable[i] = new Node(*(otherHashTable.m_hashTable[i]));
	}

	return *this;
}

int& HashTable::operator [] (const int key)
{
	int hash1 = hash(key);
	Node* runner = m_hashTable[hash1];

	while (runner->next() and !runner->next()->isEmpty())
	{
		if (runner->key() == key)
			return runner->value();

		runner = runner->next();
	}
}




