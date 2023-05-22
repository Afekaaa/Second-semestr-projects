#include "HuffmanTree.h"

HuffmanTree::Node::Node(const std::string symbols)
{
    for (int i = 0; symbols[i]; i++, m_symbols = symbols);
    m_symbols += '\0';
}

int HuffmanTree::Node::getFrequency() const
{
    return m_frequency;
}

std::string HuffmanTree::Node::getSymbols() const
{
    return m_symbols;
}

HuffmanTree::Node* HuffmanTree::Node::getLeftChild()
{
    return m_leftChild;
}

HuffmanTree::Node* HuffmanTree::Node::getRightChild()
{
    return m_rightChild;
}

void HuffmanTree::Node::setFrequency(const int frequency)
{
    m_frequency = frequency;
}

void HuffmanTree::Node::setLeftChild(Node* leftChild)
{
    delete m_leftChild;
    m_leftChild = new Node(leftChild->getSymbols());
}

void HuffmanTree::Node::setRightChild(Node* rightChild)
{
    delete m_rightChild;
    m_rightChild = new Node(rightChild->getSymbols());
}

HuffmanTree::Node* HuffmanTree::Node::operator + (Node* other)
{   
    Node* newNode = new Node(m_symbols + other->getSymbols());
    newNode->setFrequency(m_frequency + other->getFrequency());
    newNode->setLeftChild(this);
    newNode->setRightChild(other);
}