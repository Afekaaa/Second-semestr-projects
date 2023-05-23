#include "HuffmanTree.h"

HuffmanTree::Node::Node(const Node& other)
{
    m_symbols = other.getSymbols();
    m_frequency = other.getFrequency();
}

HuffmanTree::Node::Node(const std::string symbols)
{
    for (int i = 0; symbols[i]; i++, m_symbols = symbols);
    m_symbols += '\0';
}

HuffmanTree::Node::Node(const char symbol)
{
    m_symbols = std::string(1, symbol);
}

int HuffmanTree::Node::getFrequency() const
{
    return m_frequency;
}

std::string HuffmanTree::Node::getSymbols() const
{
    return m_symbols;
}

HuffmanTree::Node* HuffmanTree::Node::getLeftChild() const 
{
    return m_leftChild;
}

HuffmanTree::Node* HuffmanTree::Node::getRightChild()const 
{
    return m_rightChild;
}

void HuffmanTree::Node::setFrequency(const int frequency)
{
    m_frequency = frequency;
}

void HuffmanTree::Node::setLeftChild(const Node* leftChild)
{
    if (!m_leftChild)
        delete m_leftChild;
    m_leftChild = new Node(leftChild->getSymbols());
}

void HuffmanTree::Node::setRightChild(const Node* rightChild)
{
    if (!m_rightChild)
        delete m_rightChild;
    m_rightChild = new Node(rightChild->getSymbols());
}

HuffmanTree::Node* HuffmanTree::Node::operator + (const Node other)
{   
    Node* newNode = new Node(m_symbols + other.getSymbols());
    newNode->setLeftChild(this);
    newNode->setRightChild(&other);

    return newNode;
}

HuffmanTree::Node* HuffmanTree::Node::operator ++ ()
{
    m_frequency++;
    return this;
}
