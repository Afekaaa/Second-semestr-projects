#include "HashTable.h"

HashTable::BlockOfChain::BlockOfChain()
{
	m_value = 0;
	m_key = 0;
	m_next = nullptr;
	m_empty = true;
}

HashTable::BlockOfChain::BlockOfChain(const int value, const int key)
{
	m_value = value;
	m_key = key;
	m_empty = false;
	m_next = nullptr;
}

HashTable::BlockOfChain::BlockOfChain(BlockOfChain& otherString)
{
	if (!otherString.isEmpty())
	{
		m_value = otherString.value();
		m_key = otherString.key();
		m_empty = false;
	}

	m_next = nullptr;

	BlockOfChain* otherRunner = &otherString;
	BlockOfChain* thisRunner = this;

	while (otherRunner = otherRunner->next())
	{
		thisRunner->setNext(new BlockOfChain);
		thisRunner->setKey(otherRunner->key());
		thisRunner->setEmpty(false);
		thisRunner = thisRunner->next();
	}
}

HashTable::BlockOfChain::~BlockOfChain()
{
	if (m_next)
	{
		BlockOfChain* firstPtr = m_next;
		BlockOfChain* secondPtr = firstPtr->next();

		while (secondPtr)
		{
			delete firstPtr;
			firstPtr = secondPtr;
			secondPtr = secondPtr->next();
		}

		delete firstPtr;
	}

}

bool HashTable::BlockOfChain::isEmpty() const
{
	return m_empty;
}

void HashTable::BlockOfChain::setEmpty(const bool empty)
{
	m_empty = empty;
}

int HashTable::BlockOfChain::value() const
{
	if (!isEmpty())
		return m_value;
	else
		throw std::runtime_error("Попытка получить значение value из пустой хеш-таблицы.");
}

int HashTable::BlockOfChain::key() const
{
	if (!isEmpty())
		return m_key;
	else
		throw std::runtime_error("Попытка получить значение key из пустой хеш-таблицы.");
}

HashTable::BlockOfChain* HashTable::BlockOfChain::next()
{
	return m_next;
}

void HashTable::BlockOfChain::setValue(const int value)
{
	m_value = value;
}

void HashTable::BlockOfChain::setKey(const int key)
{
	m_key = key;
}

void HashTable::BlockOfChain::setNext(const BlockOfChain* nextString)
{
	m_next->setNext(nextString);
}