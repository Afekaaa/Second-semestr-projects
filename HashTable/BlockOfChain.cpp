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
	}

	m_next = nullptr;

	Node* otherRunner = &otherString;
	Node* thisRunner = this;

	while (otherRunner = otherRunner->next())
	{
		thisRunner->setNext(new Node);
		thisRunner->setKey(otherRunner->key());
		thisRunner->setEmpty(false);
		thisRunner = thisRunner->next();
	}
}

HashTable::Node::~Node()
{
	if (m_next)
	{
		Node* firstPtr = m_next;
		Node* secondPtr = firstPtr->next();

		while (secondPtr)
		{
			delete firstPtr;
			firstPtr = secondPtr;
			secondPtr = secondPtr->next();
		}

		delete firstPtr;
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
		throw std::runtime_error("Попытка получить значение value из пустой хеш-таблицы.");
}

int HashTable::Node::key() const
{
	if (!isEmpty())
		return m_key;
	else
		throw std::runtime_error("Попытка получить значение key из пустой хеш-таблицы.");
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