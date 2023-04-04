#include "BinaryTree.h"

BinaryTree::Node::Node()
{
	m_key = 0;
}

BinaryTree::Node::Node(int key)
{
	m_key = key;
}

int BinaryTree::Node::getKey() const
{
	return m_key;
}

void BinaryTree::Node::setKey(int key)
{
	m_key = key;
}

BinaryTree::Node* BinaryTree::Node::getRightChild() const
{
	return m_rightChild;
}

BinaryTree::Node* BinaryTree::Node::getLeftChild() const
{
	return m_leftChild;
}

void BinaryTree::Node::setRigthChild(Node* rightChild)
{
	m_rightChild = rightChild;
}
void BinaryTree::Node::setLeftChild(Node* leftChild)
{
	m_leftChild = leftChild;
}