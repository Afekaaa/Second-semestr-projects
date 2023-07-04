#include "HashTableTester.h"


HashTableTester::HashTableTester(bool useConsoleOutput)
{
	m_useConsoleOutput = useConsoleOutput;
	m_maxSize = 0;
}
#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)

void HashTableTester::test(const int size)
{
	if (size == 0)
		return;

    m_maxSize = size;

	constructorAndContains();
	addElem();
	removeAndShow();
	squareBracketOperator();
	assignAndCopy();

	//std::cout << "Press any key to test destructor" << std::endl;
	//getchar();

	destructor();
}

void HashTableTester::addElem() const
{
	HashTable* table = new HashTable(m_maxSize);
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	for (int i = 1; i < m_maxSize * 2; ++i)
	{
		table->addElem(i, i);
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
		table->addElem(*iterAnotherValues, *iterKeys);

		checkPresenceOfElements(table, *iterAnotherValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);
	}

	delete table;
}

void HashTableTester::checkPresenceOfElements(HashTable* table, const int value, const int key) const
{
	assert(table->contains(value, key));
}

void HashTableTester::checkAbsenceOfElements(HashTable* table, const int value, const int key) const
{
	assert(!table->contains(value, key));
}

void HashTableTester::constructorAndContains() const
{
	srand(time(0));
	const int lenMas = m_maxSize * 2 - 1;
	int* masValues = new int[lenMas];
	int* masKeys = new int[lenMas];

	for (int i = 0; i < lenMas; ++i)
	{
		masValues[i] = rand() % 20;
		masKeys[i] = i;
	}

	HashTable* table = new HashTable(masValues, masKeys, lenMas, m_maxSize);

	for (int i = 0; i < lenMas; ++i)
		checkPresenceOfElements(table, masValues[i], masKeys[i]);

	delete table;
	delete[] masValues;
	delete[] masKeys;
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

	for (int i = 0; i < 1000; ++i) //смотреть утечку памяти
	{
		HashTable* table = new HashTable(masValues, masKeys, masLen, m_maxSize);
		delete table;
	}
	
	delete[] masValues;
	delete[] masKeys;
}

void HashTableTester::removeAndShow() const
{
	HashTable* table = new HashTable(m_maxSize);
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	for (int i = 1; i < m_maxSize * 2; ++i)
	{
		table->addElem(i, i);
		values.push_back(i);
		anotherValues.push_back(-i);
		keys.push_back(i);
	}
	
	auto iterAnotherValues = anotherValues.begin();
	auto iterValues = values.begin();
	auto iterKeys = keys.begin();
	
	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterValues, ++iterKeys)
	{
		if (m_useConsoleOutput)
		{
			table->show();
			std::cout << std::endl << "Hash: " << table->hash(*iterKeys) << ", value/key: " << *iterValues << "/" << *iterKeys << std::endl;
		}
			

		table->remove(*iterAnotherValues, *iterKeys); //попытка удалить значения, не хранящиеся в таблице

		//проверка наличия всех неудаленных вершин
		for (auto secondIterValues = iterValues, secondIterKeys = iterKeys; secondIterValues != values.end(); ++secondIterValues, ++secondIterKeys)
			checkPresenceOfElements(table, *secondIterValues, *secondIterKeys);

		table->remove(*iterValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);
	}

	delete table;
}

void HashTableTester::squareBracketOperator() const
{
	HashTable* table = new HashTable(m_maxSize);
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	for (int i = 1; i < m_maxSize * 2; ++i)
	{
		table->addElem(i, i);
		values.push_back(i);
		anotherValues.push_back(-i);
		keys.push_back(i);
	}

	auto iterAnotherValues = anotherValues.begin();
	auto iterValues = values.begin();
	auto iterKeys = keys.begin();

	for (; iterAnotherValues != anotherValues.end(); ++iterAnotherValues, ++iterValues, ++iterKeys)
	{
		table->operator[](*iterKeys) = *iterAnotherValues; 

		checkPresenceOfElements(table, *iterAnotherValues, *iterKeys);
		checkAbsenceOfElements(table, *iterValues, *iterKeys);
	}

	delete table;
}

void HashTableTester::assignAndCopy() const
{
	HashTable table1;
	std::vector<int> values;
	std::vector<int> anotherValues;
	std::vector<int> keys;

	for (int i = 1; i < m_maxSize * 2; ++i)
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
		table2.operator[](*iterKeys) = *iterAnotherValues;

	checkAssignInequality(table1, table2, keys); //убеждаемся, что изменение table2 не привело к изменению table1

	table1 = table2; // оператор присвояние

	checkAssignEquality(table1, table2, keys); //проверка на одинаковость всех элементов

	auto iterValues = values.begin();
	iterKeys = keys.begin();

	//изменяем table1
	for (; iterValues != values.end(); ++iterValues, ++iterKeys)
		table1.operator[](*iterKeys) = *iterValues;

	checkAssignInequality(table1, table2, keys); //убеждаемся, что изменение table1 не привело к изменению table2
}

void HashTableTester::checkAssignEquality(HashTable table1, HashTable table2, std::vector<int> keys) const
{
	for (auto key : keys)
		assert(table1.operator[](key) == table2.operator[](key));
}

void HashTableTester::checkAssignInequality(HashTable table1, HashTable table2, std::vector<int> keys) const
{
	for (auto key : keys)
		assert(table1.operator[](key) != table2.operator[](key));
}

int main()
{
	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	bool usePrint = false;
	for (int i = 0; i < 100; ++i)
	{
		const int tableSize = i;
		HashTableTester HTTester(usePrint);
		HTTester.test(tableSize);
	}


	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	_CrtMemDumpAllObjectsSince(&_ms);
	return 0;
}