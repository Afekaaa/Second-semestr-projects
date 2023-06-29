#include "HashTableTester.h"


HashTableTester::HashTableTester(const bool useConsoleOutput)
{
    m_useConsoleOutput = useConsoleOutput;
	m_maxSize = 0;
}

void HashTableTester::test(const int size)
{
	if (size == 0)
		return;

    m_maxSize = size;

	constructor();
	addElemAndContains();
	remove();
	assign();
	squareBracketOperator();
}

void HashTableTester::addElemAndContains()
{
	HashTable table;
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	//умножаю на два, чтобы были внешние цепочки и вычитаю единицу, чтобы они точно были не у всех строк
	for (int i = 0; i < m_maxSize * 2 - 1; ++i)
	{
		table.addElem(i, i);
		values.push_back(i);
		anotherValues.push_back(-i);
		keys.push_back(i);

		checkPresenceOfElements(table, i, i);
		checkAbsenceOfElements(table, -i, i);
	}
	
	auto iterAnotherValues = anotherValues.begin();
	auto iterValues = values.begin();
	auto iterKeys = keys.begin();

	//замещаем старые значения - новыми.
	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterValues, ++iterKeys)
	{
		table.addElem(*iterAnotherValues, *iterKeys);

		checkPresenceOfElements(table, *iterAnotherValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);
	}
}

void HashTableTester::checkPresenceOfElements(HashTable table, const int value, const int key) const
{
	assert(table.contains(value, key));
}

void checkAbsenceOfElements(HashTable table, const int value, const int key)
{
	assert(!table.contains(value, key));
}

void HashTableTester::constructors()
{
	srand(time(0));
	const int masLen = m_maxSize * 2 - 1;
	int* masValues = new int[masLen];
	int* masKeys = new int[masLen];

	for (int i = 0; i < masLen; ++i)
	{
		masValues[i] = rand() % 20;
		masKeys[i] = i;
	}

	HashTable table(masValues, masKeys, masLen);

	for (int i = 0; i < masLen; ++i)
		checkPresenceOfElements(table, masValues[i], masKeys[i]);
}
