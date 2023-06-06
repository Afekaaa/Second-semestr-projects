#include "HashTable.h"

HashTable::String::String()
{
	m_next = nullptr;
	m_key = 0;
	m_empty = true;
}

HashTable::String::String(String& otherString)
{
	if (!otherString.isEmpty())
		m_key = otherString.key();
	m_next = nullptr;

	String* otherRunner = &otherString;
	String* thisRunner = this;

	while (otherRunner = otherRunner->next())
	{
		thisRunner->setNext(new String);
		thisRunner->setKey(otherRunner->key());
		thisRunner = thisRunner->next();
	}
}

bool HashTable::String::isEmpty() const
{
	return m_empty;
}

int HashTable::String::key() const
{
	if (!isEmpty())
		return m_key;
	else
		throw std::runtime_error("text");
}

HashTable::String* HashTable::String::next()
{
	return m_next;
}

void HashTable::String::setKey(const int key)
{
	m_key = key;
}

void HashTable::String::setNext(const String* nextString)
{
	m_next->setNext(nextString);
}