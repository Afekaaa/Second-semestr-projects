#include <iostream>
#include <fstream>

#include <string>

#include <random>


int getRandomNumber(const int maxNumberValue);
bool createFileWithRandomNumber(const std::string fileName, const int amountNumbers, const int maxNumbersValue);

bool isFileContainsSortedArray(const std::string& fileName);


std::string getFileName(const int number);


bool missingSegmentsIsEmpty(const int* missingSegments, const int fibonacciNumberOrder);

void writeNextSortedSegment(std::ifstream* generalFile, std::fstream** files, int& x1, int& x2, const int fileNumber, const int fibNum);
void splittingFiles(std::string fileName, std::fstream ** files, const int fibonacciNumberOrder);
std::fstream** createSupportFiles(const std::string fileName, const int fibonacciNumberOrder); 

int* getFirstIdealPartition(const int fibonacciNumberOrder);
int* getFirstMissingSegments(const int fibonacciNumberOrder);
std::fstream** getMassiveOfstreamFiles(const int fibonacciNumberOrder);

int* getNextIdealPartition(const int * idealPartition, const int fibNumOrder);
int* getNextMissingSegments(int* missingSegments, const int* idealPartition, const int* newIdealPartition, const int fibNumOrder);
void createNextMissingSegmentsAndIdealPartition(int* missingSegments, int*& idealPartition, const int fibNumOrder);


int fusionFiles(std::fstream** filesForSort, const int fibonacciNumberOrder);
void fusionOneSortedSegment(std::fstream** filesForSort, const int numberOfFiles);
void shiftFilesOneRight(std::fstream** filesForSort, int numberOfIteration, const int numberOfFiles);


void openFilesForSort(std::fstream** filesForSort, const int quantitySupportFiles);

int fileSorting(const std::string fileName, const int fibonacciNumberOrder);
int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, const int fibonacciNumberOrder = 2);


int main()
{

    std::string fileName = "fileOfNumbers.txt";
    const int amountNumbers = 20;
    const int maxNumbersValue = 100;
    const int amountTests = 1000;
    int fibonacciNumberOrder = 2;


    for (int i = 1; i < amountTests + 1; ++i)
    {
        switch (createFileAndStartSorting(fileName, amountNumbers, maxNumbersValue, fibonacciNumberOrder))
        {
        case 1:
            //std::cout << i << ". File was sorted" << std::endl;
            break;
        case -1: 
            std::cout << i << ". File wasn't created" << std::endl;
            break;
        case -2:
            std::cout << i << ". File wasn't sorted" << std::endl;
            exit(0);
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
    std::ifstream sortedFile(fileName);

    sortedFile >> numberA;
    while (sortedFile >> numberB)
    {
        if (numberA > numberB and numberB != -1)
            return false;

        if (numberB != -1)
            numberA = numberB;
    }

    sortedFile.close();

    return true;
}


void openFilesForSort(std::fstream** filesForSort, const int quantitySupportFiles)
{
    for (int i = 0; i < quantitySupportFiles; ++i)
    {
        filesForSort[i]->open(getFileName(i));

        if (!filesForSort[i]->is_open())
        {
            std::cerr << "file " << i << " not opened (fusion)" << std::endl;
            exit(0);
        }
    }
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
bool missingSegmentsIsTrue(int* missingSegments, const int fibonacciNumberOrder)
{
    for (int i = 0; i < fibonacciNumberOrder; ++i)
    {
        if (missingSegments[i] < 0)
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


std::fstream** getMassiveOfstreamFiles(const int fibonacciNumberOrder)
{
    int quantitySupportFiles = fibonacciNumberOrder + 1;
    std::fstream** files = new std::fstream* [quantitySupportFiles];

    for (int i = 0; i < quantitySupportFiles; ++i)
    {
        //std::string fileName = getFileName(i);
        //std::cout << fileName << std::endl;
        files[i] = new std::fstream(getFileName(i), std::ios::out);

        if (!files[i]->is_open())
        {
            std::cerr << "file " << i << " not opened" << std::endl;
            exit(0);
        }

    }

    return files;
}

void writeNextSortedSegment(std::ifstream* generalFile, std::fstream** files, int& x1, int& x2, const int fileNumber, const int fibNum)
{
    (*files[fileNumber]) << " " << x1;

    if (!generalFile->eof())
    {
        (*generalFile) >> x2;

        while (x2 >= x1 and !generalFile->eof())
        {
            (*files[fileNumber]) << " " << x2;
            x1 = x2;
            (*generalFile) >> x2;
        }
    }
}

bool splittingTests(std::fstream** files, int* idealPartition, int* missingSegments, const int fibNum)
{
    for (int i = 1; i < fibNum + 1; ++i)
    {
        files[i]->open(getFileName(i), std::ios::in);
    }

    int counterMinusOne = 0;
    int x1;
    int i = 1;

    while (i < fibNum + 1)
    {
        while ((*files[i]) >> x1)
            if (x1 == -1)
                counterMinusOne++;
        if (counterMinusOne != missingSegments[i - 1])
        {
            //std::cout << "ihgbqe;ijb;qeijvb;qe kjb;qekfjb;qdkfjb;dqkjbf;kjsbskj;b;skjdb;skjfb;sdkjfb;skdjbs;dkfjb" << std::endl;
            std::cout << i << ": " << counterMinusOne << " != " << missingSegments[i - 1];
            exit(0);
        }
        i++;
    }

    return true;
}

void splittingFiles(std::string fileName, std::fstream** files, const int fibonacciNumberOrder)
{
    int firstElem, secondElem;
    int* idealPartition = getFirstIdealPartition(fibonacciNumberOrder);
    int* missingSegments = getFirstMissingSegments(fibonacciNumberOrder);
    int quantitySupportFiles = fibonacciNumberOrder + 1;
    int fileNumber = 1;

    std::ifstream* generalFile = new std::ifstream(fileName);

    (*generalFile) >> firstElem;

    writeNextSortedSegment(generalFile, files, firstElem, secondElem, fileNumber, fibonacciNumberOrder);
    (*files[fileNumber]) << " " << -1;
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
                    (*files[fileNumber]) << " " << secondElem << " " << -1;
                }
                else if (secondElem < firstElem and generalFile->eof()) 
                {
                    (*files[fileNumber]) << " " << -1;
                    if (missingSegments[fileNumber - 1] > 1)
                    {
                        --missingSegments[fileNumber - 1];
                        (*files[fileNumber]) << " " << secondElem << " " << -1;
                    }
                    else
                    {
                        --missingSegments[fileNumber % fibonacciNumberOrder];
                        (*files[fileNumber % fibonacciNumberOrder + 1]) << " " << secondElem << " " << -1;
                    }
                }
                else if (!generalFile->eof() and secondElem < firstElem) //можно просто оставить else
                {
                    (*files[fileNumber]) << " " << -1;
                }
                firstElem = secondElem;
            }

            //std::cout << fileNumber << ": ";
            //std::cout << missingSegments[fileNumber - 1] << std::endl;
        }

        if (missingSegmentsIsEmpty(missingSegments, fibonacciNumberOrder) and !generalFile->eof())
            createNextMissingSegmentsAndIdealPartition(missingSegments, idealPartition, fibonacciNumberOrder);
        
    }

    if (!missingSegmentsIsTrue(missingSegments, fibonacciNumberOrder))
        createNextMissingSegmentsAndIdealPartition(missingSegments, idealPartition, fibonacciNumberOrder);


    for (fileNumber = 1; fileNumber < fibonacciNumberOrder + 1; ++fileNumber)
    {
        for (; missingSegments[fileNumber - 1] > 0; --missingSegments[fileNumber - 1])
        {
            (*files[fileNumber]) << " " << -1;
           // std::cout << fileNumber;
        }
    }

    //splittingTests(files, idealPartition, missingSegments, fibonacciNumberOrder);

    generalFile->close();
    delete[] idealPartition;
    delete[] missingSegments;
}

std::fstream** createSupportFiles(const std::string fileName, const int fibonacciNumberOrder)
{
    std::fstream** files = getMassiveOfstreamFiles(fibonacciNumberOrder); 
    splittingFiles(fileName, files, fibonacciNumberOrder);
    
    for (int i = 0; i < fibonacciNumberOrder + 1; ++i)
        files[i]->close();

    return files;
}


int fusionFiles(std::fstream** filesForSort, const int fibonacciNumberOrder)
{
    int numberOfFiles = fibonacciNumberOrder + 1;
    int indexOfIteration = 0;

    filesForSort[0]->open(getFileName(0), std::ios::out);

    for (int i = 1; i < numberOfFiles; ++i)
        filesForSort[i]->open(getFileName(i), std::ios::in);

    for (int i = 0; i < numberOfFiles; ++i)
    {
        if (!filesForSort[i]->is_open())
        {
            std::cout << "UTFCYGVHJOB:HGUYCGHFXUDZFXGCKVHLGJ:HXDUCFBH";
        }
    }

    while (!filesForSort[2]->eof())
    {
        while (!filesForSort[fibonacciNumberOrder]->eof())
        {
            //слить один отрезок из каждого файла. fusionOneSortedSegment(std::fstream** filesForSort, const int numberOfFiles)
           // std::cout << "1. first while" << std::endl;
            fusionOneSortedSegment(filesForSort, fibonacciNumberOrder);
            //std::cout << "2. first while" << std::endl;
        }

        shiftFilesOneRight(filesForSort, indexOfIteration, numberOfFiles);
        indexOfIteration++;
        //std::cout << "second while" << std::endl;
    }

    for (int i = 0; i < numberOfFiles; ++i)
        filesForSort[i]->close();

    //std::cout << numberOfFiles - 1 - ((indexOfIteration - 2)% numberOfFiles) << std::endl;

    return numberOfFiles - 1 - ((indexOfIteration - 2) % numberOfFiles);
}

int* getElemsFromFiles(std::fstream** filesForSort, const int fibonacciNumberOrder)
{
    int* elemsFromFiles = new int[fibonacciNumberOrder];

    for (int i = 0; i < fibonacciNumberOrder; ++i)
        (*filesForSort[i + 1]) >> elemsFromFiles[i];

    return elemsFromFiles;
}

int firstElemFromFilesNotIsMinusOne(int* elementsFromFiles, const int fibonacciNumberOrder)
{
    for (int i = 0; i < fibonacciNumberOrder; ++i)
    {
        if (elementsFromFiles[i] != -1)
            return i + 1;
    }

    return 0;
}

int getIndexOfMinElem(int *elementsFromFiles, const int numberOfFirstElemNotIsMinusOne, const int fibonacciNumberOrder)
{
    int indexOfMinElem = numberOfFirstElemNotIsMinusOne - 1;
    int minElem = elementsFromFiles[indexOfMinElem];

    for (int i = numberOfFirstElemNotIsMinusOne; i < fibonacciNumberOrder; ++i)
    {
        if (elementsFromFiles[i] < minElem and elementsFromFiles[i] != -1)
        {
            minElem = elementsFromFiles[i];
            indexOfMinElem = i;
        }
    }

    return indexOfMinElem;
}

void fusionOneSortedSegment(std::fstream** filesForSort, const int fibonacciNumberOrder)
{
    int* elementsFromFiles = getElemsFromFiles(filesForSort, fibonacciNumberOrder);
    int indexOfMinElem;
    int numberOfFirstElemNotIsMinusOne;

    while (numberOfFirstElemNotIsMinusOne = firstElemFromFilesNotIsMinusOne(elementsFromFiles, fibonacciNumberOrder))
    {
        indexOfMinElem = getIndexOfMinElem(elementsFromFiles, numberOfFirstElemNotIsMinusOne, fibonacciNumberOrder);
        //std::cout << indexOfMinElem << " : " << elementsFromFiles[indexOfMinElem] << std::endl;
        (*filesForSort[0]) << " " << elementsFromFiles[indexOfMinElem];
        (*filesForSort[indexOfMinElem + 1]) >> elementsFromFiles[indexOfMinElem];
    }

    (*filesForSort[0]) << " " << -1;
    
}

void shiftFilesOneRight(std::fstream** filesForSort, int indexOfIteration, const int numberOfFiles)
{
    std::fstream* tmpFstreamPtr = filesForSort[numberOfFiles - 1];

    for (int i = numberOfFiles - 1; i > 0; --i)
        filesForSort[i] = filesForSort[i - 1];

    filesForSort[0] = tmpFstreamPtr;

    filesForSort[0]->close();
    filesForSort[1]->close();

    filesForSort[0]->open(getFileName(numberOfFiles - 1 - (indexOfIteration % numberOfFiles)), std::ios::out); // max, max - 1, ..., max - max + 1, 0, max, ...
    //std::cout << "Iteration index: " << indexOfIteration << ". F0 = " << numberOfFiles - 1 - (indexOfIteration % numberOfFiles) << std::endl;
    filesForSort[1]->open(getFileName(numberOfFiles - 1 - (indexOfIteration + numberOfFiles - 1) % numberOfFiles), std::ios::in); // 0, max, max - 1, ..., max - max + 1, 0, max, ...
    //std::cout << "Iteration index: " << indexOfIteration << ". F1 = " << numberOfFiles - 1 - (indexOfIteration + numberOfFiles - 1) % numberOfFiles << std::endl;
}


int fileSorting(const std::string fileName, const int fibonacciNumberOrder)
{
    std::fstream** filesForSort = createSupportFiles(fileName, fibonacciNumberOrder); // запись всегда ведется в supFiles[0]
    int numberSortedFiles = fusionFiles(filesForSort, fibonacciNumberOrder);
    return numberSortedFiles;
}


int createFileAndStartSorting(const std::string fileName, const int amountNumbers, const int maxNumbersValue, int fibonacciNumberOrder)
{
    if (!createFileWithRandomNumber(fileName, amountNumbers, maxNumbersValue))
        return -1;

    int numberSortedFiles = fileSorting(fileName, fibonacciNumberOrder);

    if (!isFileContainsSortedArray(getFileName(numberSortedFiles)))
    {
        return -2;
    }

    return 1;
}