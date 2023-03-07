#include <iostream>
#include <fstream>

#include <random>


int getRandomNumber(const int maxNumberValue);
bool createFileWithRandomNumber(const std::string fileName, const int amountNumbers, const int maxNumbersValue);

bool isFileContainsSortedArray(const std::string& fileName);

int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, const int fibonacciNumberOrder = 2);

std::ofstream createSupportsFile(const std::string fileName, const int fibonacciNumberOrder); // рализовать возврат массива вспомогательных файлов


int* getNextIdealPartition(); //реазлизовать возварт массива идеальных разбиений для слудющей итерации разбиения файла на вспомогательные

void fileSorting(const std::string fileName, const int fibonacciNumberOrder); // реализовать многофазную сортировку


int main()
{
    std::string fileName = "fileOfNumbers.txt";
    const int amountNumbers = 100;
    const int maxNumbersValue = 10000;
    const int amountTests = 10;
    int fibonacciNumberOrder = 2;

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

void fileSorting(const std::string fileName, int fibonacciNumberOrder)
{
    std::ofstream supFiles = createSupportsFile(fileName, fibonacciNumberOrder); //вернуть массив файлов для многофазной сортировки
    return;
}

