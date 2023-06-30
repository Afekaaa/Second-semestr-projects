#include "HashTableTester.h"


HashTableTester::HashTableTester(bool useConsoleOutput)
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
	squareBracketOperator();
	assignAndCopy();

	std::cout << "Press any key to test destructor" << std::endl;
	getchar();

	destructor();
}

void HashTableTester::addElemAndContains() const
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

void HashTableTester::checkAbsenceOfElements(HashTable table, const int value, const int key) const
{
	assert(!table.contains(value, key));
}

void HashTableTester::constructor() const
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

void HashTableTester::destructor() const
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

	for (int i = 0; i < 1000; ++i)
	{
		HashTable* table = new HashTable(masValues, masKeys, masLen);
		delete table;
	}
	
}

void HashTableTester::remove() const
{
	HashTable table;
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	//умножаю на два, чтобы были внешние цепочки и вычитаю единицу, чтобы они точно были не у всех строк. Благодаря этому буудт проверены оба случая, которые рассматриваются в удалении некоторого значения из таблицы.
	for (int i = 0; i < m_maxSize * 2 - 1; ++i)
	{
		table.addElem(i, i);
		values.push_back(i);
		anotherValues.push_back(-i);
		keys.push_back(i);
	}
	
	auto iterAnotherValues = anotherValues.begin();
	auto iterValues = values.begin();
	auto iterKeys = keys.begin();
	
	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterValues, ++iterKeys)
	{
		table.remove(*iterAnotherValues, *iterKeys); //попытка удалить значения, не хранящиеся в таблице

		//проверка наличия всех неудаленных вершин
		for (auto secondIterValues = iterValues, secondIterKeys = iterKeys; secondIterValues != values.end(); ++secondIterValues, ++secondIterKeys)
		{
			checkPresenceOfElements(table, *secondIterValues, *secondIterKeys);
		}

		table.remove(*iterValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);

		if (m_useConsoleOutput)
			table.show();
	}
}

void HashTableTester::squareBracketOperator() const
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
	}

	auto iterAnotherValues = anotherValues.begin();
	auto iterValues = values.begin();
	auto iterKeys = keys.begin();

	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterValues, ++iterKeys)
	{
		table[*iterKeys] = *iterAnotherValues; 

		checkPresenceOfElements(table, *iterAnotherValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);
	}
}

void HashTableTester::assignAndCopy() const
{
	HashTable table1;
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	//умножаю на два, чтобы были внешние цепочки и вычитаю единицу, чтобы они точно были не у всех строк
	for (int i = 0; i < m_maxSize * 2 - 1; ++i)
	{
		table1.addElem(i, i);
		values.push_back(i);
		anotherValues.push_back(-i);
		keys.push_back(i);
	}

	HashTable table2(table1); // copy constructor

	checkAssignEquality(table1, table2, keys); //проверка на одинаковость всех элементов

	auto iterAnotherValues = anotherValues.begin();
	auto iterKeys = keys.begin();

	//изменяем table2
	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterKeys)
		table2[*iterKeys] = *iterAnotherValues;

	checkAssignInequality(table1, table2, keys); //убеждаемся, что изменение table2 не привело к изменению table1

	table1 = table2; // оператор присвояние

	checkAssignEquality(table1, table2, keys); //проверка на одинаковость всех элементов

	auto iterValues = values.begin();
	iterKeys = keys.begin();

	//изменяем table1
	for (; iterValues != values.end(); ++iterValues, ++iterKeys)
		table1[*iterKeys] = *iterValues;

	checkAssignInequality(table1, table2, keys); //убеждаемся, что изменение table1 не привело к изменению table2
}

void HashTableTester::checkAssignEquality(HashTable table1, HashTable table2, std::vector<int> keys) const
{
	for (auto key : keys)
		assert(table1[key] == table2[key]);
}

void HashTableTester::checkAssignInequality(HashTable table1, HashTable table2, std::vector<int> keys) const
{
	for (auto key : keys)
		assert(table1[key] != table2[key]);
}

#include <random>

int main()
{

	const int tableSize = 10;

	HashTableTester HTTester(true);
	HTTester.test(tableSize);

	return 0;
}