#include "HashTable.h"

HashTable::Node::Node()
{
	m_value = 0;
	m_key = 0;
	m_next = nullptr;
	m_empty = true;
}

HashTable::Node::Node(const int value, const int key)
{
	m_value = value;
	m_key = key;
	m_empty = false;
	m_next = nullptr;
}

HashTable::Node::Node(Node& otherString)
{
	if (!otherString.isEmpty())
	{
		m_value = otherString.value();
		m_key = otherString.key();
		m_empty = false;
		m_next = nullptr;
	}
	else
	{
		m_value = 0;
		m_key = 0;
		m_empty = true;
		m_next = nullptr;
	}

	Node* otherRunner = otherString.next();
	Node* thisRunner = this;

	while (otherRunner)
	{
		if (otherRunner->isEmpty())
		{
			thisRunner->setNext(new Node());
			break;
		}
		else
		{
			int value = otherRunner->value();
			int key = otherRunner->key();

			thisRunner->setNext(new Node(otherRunner->value(), otherRunner->key()));
			thisRunner = thisRunner->next();
			otherRunner = otherRunner->next();
		}
	}

}

bool HashTable::Node::isEmpty() const
{
	return m_empty;
}

void HashTable::Node::setEmpty(const bool empty)
{
	m_empty = empty;
}

int& HashTable::Node::value()
{
	if (!isEmpty())
		return m_value;
	else
		throw std::range_error("Попытка получить значение value из пустого блока внешней цепочки");
}

int HashTable::Node::key() const
{
	if (!isEmpty())
		return m_key;
	else
		throw std::range_error("Попытка получить значение key из пустого блока внешней цепочки");
}

HashTable::Node* HashTable::Node::next()
{
	return m_next;
}

void HashTable::Node::setValue(const int value)
{
	m_value = value;
}

void HashTable::Node::setKey(const int key)
{
	m_key = key;
}

void HashTable::Node::setNext(Node* nextString)
{
	m_next = nextString;
}