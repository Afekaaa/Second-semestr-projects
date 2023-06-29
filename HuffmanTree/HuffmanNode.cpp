#include "HuffmanTree.h"

HuffmanTree::Node::Node(const Node& other)
{
    m_symbols = other.getSymbols();
    m_frequency = other.getFrequency();
}

HuffmanTree::Node::Node(const std::string symbols)
{
    m_symbols = symbols;
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

std::string& HuffmanTree::Node::getCode()
{
    return m_code;
}

void HuffmanTree::Node::setSymbols(std::string symbols)
{
    m_symbols = symbols;
}

void HuffmanTree::Node::setFrequency(const int frequency)
{
    m_frequency = frequency;
}

void HuffmanTree::Node::setLeftChild(const Node* leftChild)
{
    if (leftChild)
    {
        if (m_leftChild)
            delete m_leftChild;
        m_leftChild = new Node(leftChild->getSymbols());
        m_leftChild->setFrequency(leftChild->getFrequency());
        m_leftChild->setRightChild(leftChild->getRightChild());
        m_leftChild->setLeftChild(leftChild->getLeftChild());
    }
    else
        m_leftChild = nullptr;
}

void HuffmanTree::Node::setRightChild(const Node* rightChild)
{
    if (rightChild)
    {
        if (m_rightChild)
            delete m_rightChild;
        m_rightChild = new Node(rightChild->getSymbols());
        m_rightChild->setFrequency(rightChild->getFrequency());
        m_rightChild->setRightChild(rightChild->getRightChild());
        m_rightChild->setLeftChild(rightChild->getLeftChild());
    }
    else
        m_rightChild = nullptr;
}

