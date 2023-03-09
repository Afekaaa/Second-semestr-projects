#include <iostream>
#include <fstream>

#include <random>


int getRandomNumber(const int maxNumberValue);
bool createFileWithRandomNumber(const std::string fileName, const int amountNumbers, const int maxNumbersValue);

bool isFileContainsSortedArray(const std::string& fileName);


std::ofstream* createSupportFiles(const std::string fileName, const int fibonacciNumberOrder); // рализовать возврат массива вспомогательных файлов

int* getFirstIdealPartition(const int fibonacciNumberOrder);
int* getFirstMissingSegments(const int fibonacciNumberOrder);

int* getNextIdealPartition(const int * idealPartition, const int fibNumOrder);
int* getNextMissingSegments(int* missingSegments, const int* idealPartition, const int* newIdealPartition, const int fibNumOrder);
void createNextMissingSegmentsAndIdealPartition(int* missingSegments, int*& idealPartition, const int fibNumOrder);

void fileSorting(const std::string fileName, const int fibonacciNumberOrder); // реализовать многофазную сортировку


int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, const int fibonacciNumberOrder = 2);


int main()
{
    std::string fileName = "fileOfNumbers.txt";
    const int amountNumbers = 100;
    const int maxNumbersValue = 10000;
    const int amountTests = 1;
    int fibonacciNumberOrder = 5;

    for (int i = 1; i < amountTests + 1; ++i)
    {
        switch (createFileAndStartSorting(fileName, amountNumbers, maxNumbersValue, fibonacciNumberOrder))
        {
        case 1:
            std::cout << i << ". File was sorted" << std::endl;
            break;
        case -1: 
            std::cout << i << ". File wasn't created" << std::endl;
            break;
        case -2:
            std::cout << i << ". File wasn't sorted" << std::endl;
            break;

        }

    }

    return 0;
}

void printMas(int* mas, int len) 
{
    for (int i = 0; i < len; ++i) 
    {
        std::cout << mas[i] << " ";
    }

    std::puts("");
}

int getRandomNumber(int maxNumbersValue) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxNumbersValue);
    return dis(gen);
}
bool createFileWithRandomNumber(const std::string fileName, const int amountNumbers, const int maxNumbersValue) 
{
    srand(time(0));

    std::ofstream fileOfNumbers(fileName);

    if (!fileOfNumbers.is_open())
        return false;
    
    for (int i = 0; i < amountNumbers; ++i) 
    {
        fileOfNumbers << " " << getRandomNumber(maxNumbersValue);
    }

    fileOfNumbers.close();

    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) 
{
    int numberA;
    int numberB;
    std::ifstream fileOfNumbers(fileName);

    fileOfNumbers >> numberA;
    while (fileOfNumbers >> numberB) 
    {
        if (numberA > numberB)
            return false;

        numberA = numberB;
    }

    return true;
}

int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, int fibonacciNumberOrder)
{
    if (!createFileWithRandomNumber(fileName, amountNumbers, maxNumbersValue))
        return -1;

    fileSorting(fileName, fibonacciNumberOrder);

    if (!isFileContainsSortedArray(fileName))
    {
        return -2;
    }

    return 1;
}

int* getFirstIdealPartition(const int fibonacciNumberOrder) 
{
    int* idealPartition = new int[fibonacciNumberOrder];

    for (int i = 0; i < fibonacciNumberOrder; ++i) 
        idealPartition[i] = 1;

    return idealPartition;
}
int* getFirstMissingSegments(const int fibonacciNumberOrder) 
{
    int* missingSegments = new int[fibonacciNumberOrder];
    for (int i = 0; i < fibonacciNumberOrder; ++i)
        missingSegments[i] = 1;

    return missingSegments;
}

int* getNextIdealPartition(const int * idealPartition, const int fibNumOrder)
{
    int tmpIdealPart0 = idealPartition[0];

    int* newIdealPartition = new int[fibNumOrder];

    for (int i = 0; i < fibNumOrder - 1; ++i)
        newIdealPartition[i] = tmpIdealPart0 + idealPartition[i + 1];

    newIdealPartition[fibNumOrder - 1] = tmpIdealPart0;

    return newIdealPartition;
}
int* getNextMissingSegments(int* missingSegments, const int * idealPartition, const int* newIdealPartition, const int fibNumOrder)
{
    for (int i = 0; i < fibNumOrder; ++i) 
        missingSegments[i] += newIdealPartition[i] - idealPartition[i];  

    return missingSegments;
}

void createNextMissingSegmentsAndIdealPartition(int* missingSegments, int*& idealPartition, const int fibNumOrder)
{
    int* newIdealPartition = getNextIdealPartition(idealPartition, fibNumOrder);
    missingSegments = getNextMissingSegments(missingSegments, idealPartition, newIdealPartition, fibNumOrder);

    delete idealPartition;
    idealPartition = newIdealPartition;
}

std::ofstream* createSupportFiles(const std::string fileName, const int fibonacciNumberOrder) 
{
    int* idealPartition = getFirstIdealPartition(fibonacciNumberOrder);
    int* missingSegments = getFirstMissingSegments(fibonacciNumberOrder);

    std::ofstream* file = new std::ofstream[fibonacciNumberOrder];


    createNextMissingSegmentsAndIdealPartition(missingSegments, idealPartition, fibonacciNumberOrder);

    delete[] idealPartition;
    delete[] missingSegments;
    return file;
    
}

void fileSorting(const std::string fileName, const int fibonacciNumberOrder)
{
    std::ofstream* supFiles = createSupportFiles(fileName, fibonacciNumberOrder); //вернуть массив указателей на файлы для многофазной сортировки
    return;
}

