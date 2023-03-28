﻿#include <iostream>
#include <fstream>

#include <string>

#include <random>


int getRandomNumber(const int maxNumberValue);
bool createFileWithRandomNumber(const std::string fileName, const int amountNumbers, const int maxNumbersValue);


bool isFileContainsSortedArray(const std::string& fileName);


std::string getFileName(const int number);


bool missingSegmentsIsEmpty(const int* missingSegments, const int fibonacciNumberOrder);

void writeNextSortedSegment(std::ifstream* generalFile, std::fstream*& files, int& x1, int& x2, const int fileNumber, const int fibNum);
void splittingFiles(std::string fileName, std::fstream *& files, const int fibonacciNumberOrder);
std::fstream* createSupportFiles(const std::string fileName, const int fibonacciNumberOrder); 

int* getFirstIdealPartition(const int fibonacciNumberOrder);
int* getFirstMissingSegments(const int fibonacciNumberOrder);
std::fstream* getMassiveOfstreamFiles(const int fibonacciNumberOrder);

int* getNextIdealPartition(const int * idealPartition, const int fibNumOrder);
int* getNextMissingSegments(int* missingSegments, const int* idealPartition, const int* newIdealPartition, const int fibNumOrder);
void createNextMissingSegmentsAndIdealPartition(int* missingSegments, int*& idealPartition, const int fibNumOrder);


void fusionFiles(std::fstream& filesForSort, const int fibonacciNumberOrder);

void fileSorting(const std::string fileName, const int fibonacciNumberOrder);
int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, const int fibonacciNumberOrder = 2);


int main()
{

    std::string fileName = "fileOfNumbers.txt";
    const int amountNumbers = 10;
    const int maxNumbersValue = 100;
    const int amountTests = 1;
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
        fileOfNumbers << " " << getRandomNumber(maxNumbersValue);

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


std::string getFileName(const int number) 
{
    return "C:\\Users\\Zykov Vladimir\\source\\repos\\Second semestr projects\\Second semestr projects\\Second semestr projects\\file" + std::to_string(number) + ".txt";
}


bool missingSegmentsIsEmpty(const int* missingSegments, const int fibonacciNumberOrder)
{
    for (int i = 0; i < fibonacciNumberOrder; ++i)
    {
        if (missingSegments[i] > 0)
            return false;
    }

    return true;
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


std::fstream* getMassiveOfstreamFiles(const int fibonacciNumberOrder)
{
    int quantitySupportFiles = fibonacciNumberOrder + 1;
    std::fstream* files = new std::fstream[quantitySupportFiles];

    for (int i = 0; i < quantitySupportFiles; ++i)
    {
        std::string fileName = getFileName(i);
        std::cout << fileName << std::endl;
        files[i].open(getFileName(i), std::ios::out);

        if (!files[i].is_open())
        {
            std::cerr << "file " << i << " not opened" << std::endl;
            exit(0);
        }

    }

    return files;
}

void writeNextSortedSegment(std::ifstream* generalFile, std::fstream*& files, int& x1, int& x2, const int fileNumber, const int fibNum)
{
    files[fileNumber] << " " << x1;

    if (!generalFile->eof())
    {
        (*generalFile) >> x2;

        while (x2 >= x1 and !generalFile->eof())
        {
            files[fileNumber] << " " << x2;
            x1 = x2;
            (*generalFile) >> x2;
        }
    }
}

void splittingFiles(std::string fileName, std::fstream *& files, const int fibonacciNumberOrder)
{
    int firstElem, secondElem;
    int* idealPartition = getFirstIdealPartition(fibonacciNumberOrder);
    int* missingSegments = getFirstMissingSegments(fibonacciNumberOrder);
    int quantitySupportFiles = fibonacciNumberOrder + 1;
    int fileNumber = 1;

    std::ifstream* generalFile = new std::ifstream(fileName);

    (*generalFile) >> firstElem;

    writeNextSortedSegment(generalFile, files, firstElem, secondElem, fileNumber, fibonacciNumberOrder);
    files[fileNumber] << " " << -1;
    missingSegments[fileNumber - 1]--;
    firstElem = secondElem;

    while (!generalFile->eof())
    {
        for (fileNumber = 1; fileNumber < quantitySupportFiles; ++fileNumber)
        {
            for (; missingSegments[fileNumber - 1] > 0 and !generalFile->eof(); --missingSegments[fileNumber - 1])
            {
                writeNextSortedSegment(generalFile, files, firstElem, secondElem, fileNumber, fibonacciNumberOrder);

                if (secondElem >= firstElem and generalFile->eof())
                {
                    files[fileNumber] << " " << secondElem << " " << -1;
                }
                else if (secondElem < firstElem and generalFile->eof()) 
                {
                    files[fileNumber] << " " << -1;
                    if (missingSegments[fileNumber - 1] > 1)
                    {
                        --missingSegments[fileNumber - 1];
                        files[fileNumber] << " " << secondElem << " " << -1;
                    }
                    else
                    {
                        --missingSegments[fileNumber % fibonacciNumberOrder];
                        files[fileNumber % fibonacciNumberOrder + 1] << " " << secondElem << " " << -1;
                    }
                }
                else if (!generalFile->eof() and secondElem < firstElem) //можно просто оставить else
                {
                    files[fileNumber] << " " << -1;
                }
                firstElem = secondElem;
            }

            std::cout << fileNumber << ": ";
            std::cout << missingSegments[fileNumber - 1] << std::endl;
        }

        if (missingSegmentsIsEmpty and !generalFile->eof())
            createNextMissingSegmentsAndIdealPartition(missingSegments, idealPartition, fibonacciNumberOrder);
        
    }


    for (fileNumber = 1; fileNumber < fibonacciNumberOrder + 1; ++fileNumber)
    {
        for (; missingSegments[fileNumber - 1] > 0; --missingSegments[fileNumber - 1])
        {
            files[fileNumber] << " " << -1;
            std::cout << fileNumber;
        }
    }

    generalFile->close();
    delete[] idealPartition;
    delete[] missingSegments;
}

std::fstream* createSupportFiles(const std::string fileName, const int fibonacciNumberOrder)
{
    std::fstream* files = getMassiveOfstreamFiles(fibonacciNumberOrder); 
    splittingFiles(fileName, files, fibonacciNumberOrder);
    
    for (int i = 0; i < fibonacciNumberOrder + 1; ++i)
        files[i].close();

    return files;
}


void fileSorting(const std::string fileName, const int fibonacciNumberOrder)
{
    std::fstream* filesForSort = createSupportFiles(fileName, fibonacciNumberOrder); // запись всегда ведется в supFiles[0]

    //fusionFiles(filesForSort, fibonacciNumberOrder);

    return;
}