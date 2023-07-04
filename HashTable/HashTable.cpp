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

HashTable::HashTable(const int size)
{
	m_size = size + size * 0.1;
	m_hashTable = new Node * [m_size];

	for (int i = 0; i < m_size; ++i)
	{
		m_hashTable[i] = new Node();
	}
}

HashTable::HashTable(const int * values, const int* keys, const int lenMas, const int size)
{
	m_size = lenMas + lenMas * 0,1;
	m_hashTable = new Node*[m_size];

	for (int i = 0; i < lenMas; ++i)
		m_hashTable[i] = nullptr;

	for (int i = 0; i < lenMas; ++i)
	{
		int hash1 = hash(keys[i]);
		if (m_hashTable[hash1] == nullptr)
			m_hashTable[hash1] = new Node(values[i], keys[i]);
		else
		{
			Node* runner = m_hashTable[hash1];
			while (runner->next()) runner = runner->next();
			runner->setNext(new Node(values[i], keys[i]));
		}
	}
}

HashTable::HashTable(HashTable& otherHashTable)
{
	m_size = otherHashTable.size();
	m_hashTable = new Node*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		if (otherHashTable.m_hashTable[i])
			m_hashTable[i] = new Node(*(otherHashTable.m_hashTable[i]));
		else
			m_hashTable[i] = nullptr;
	}

}

HashTable::~HashTable()
{
	for (int i = 0; i < m_size; ++i)
	{
		if (!m_hashTable[i])
			continue;
		Node* firstPtr = m_hashTable[i];
		Node* secondPtr = firstPtr->next();

		while (secondPtr)
		{
			delete firstPtr;
			firstPtr = secondPtr;
			secondPtr = secondPtr->next();
		}

		delete firstPtr;
	}

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

	if (!m_hashTable[hash1])
	{
		m_hashTable[hash1] = new Node(value, key);
	}
	else if (m_hashTable[hash1]->isEmpty())
	{
		m_hashTable[hash1]->setValue(value);
		m_hashTable[hash1]->setKey(key);
		m_hashTable[hash1]->setEmpty(false);
	}
	else
	{
		Node* runner = m_hashTable[hash1];

		while (!runner->isEmpty())
		{
			if (runner->key() == key)
			{
				runner->value() = value;
				return;
			}
			else if (runner->next() == nullptr)
			{
				runner->setNext(new Node(value, key));
				return;
			}

			runner = runner->next();
		}
	}
}

bool HashTable::remove(const int value, const int key)
{
	if (!contains(value, key))
		return false;

	int hash1 = hash(key);

	Node* runner = m_hashTable[hash1];

	if (runner->key() == key)
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
			if (!runner->isEmpty() and runner->key() == key)
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
	Node* runner = m_hashTable[hash1];

	if (runner and !runner->isEmpty())
	{
		while (runner and !runner->isEmpty())
		{
			if (runner->key() == key and runner->value() == value)
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
		if (!m_hashTable[i])
			std::cout << i << "\t" << "nullptr\t nullptr\t nullptr\t" << std::endl;
		else if (m_hashTable[i]->isEmpty())
			std::cout << i << "\t" << "empty\t empty\t empty\t" << std::endl;
		else
		{
			std::cout << i << "\t" << m_hashTable[i]->value() << "\t" << m_hashTable[i]->key() << "\t";
			Node* runner = m_hashTable[i]->next();

			while (runner and !runner->isEmpty())
			{
				std::cout << runner->value() << " " << runner->key() << "\t";
				runner = runner->next();
			}
			std::cout << std::endl;
		}
	}
}

HashTable& HashTable::operator = (HashTable otherHashTable)
{
	if (otherHashTable.m_hashTable != m_hashTable)
	{
		for (int i = 0; i < m_size; ++i)
		{
			if (!m_hashTable[i])
				continue;
			Node* firstPtr = m_hashTable[i];
			Node* secondPtr = firstPtr->next();

			while (secondPtr)
			{
				delete firstPtr;
				firstPtr = secondPtr;
				secondPtr = secondPtr->next();
			}

			delete firstPtr;
		}
		delete[] m_hashTable;

		m_size = otherHashTable.size();

		m_hashTable = new Node * [m_size];
		for (int i = 0; i < m_size; i++)
		{
			if (otherHashTable.m_hashTable[i])
				m_hashTable[i] = new Node(*(otherHashTable.m_hashTable[i]));
			else
				m_hashTable[i] = nullptr;
		}
	}

	return *this;
}

int& HashTable::operator [] (const int key)
{
	int hash1 = hash(key);
	Node* runner = m_hashTable[hash1];

	while (runner and !runner->isEmpty())
	{
		if (runner->key() == key)
			return runner->value();

		runner = runner->next();
	}
}




