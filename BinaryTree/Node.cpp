#include "BinaryTree.h"

BinaryTree::Node::Node()
{
	m_key = 0;
}

BinaryTree::Node::Node(Node& other)
{
	m_key = other.getKey();
	
	if (other.getRightChild())
		m_rightChild = new Node(*other.getRightChild());
	if (other.getLeftChild())
		m_leftChild = new Node(*other.getLeftChild());
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

void BinaryTree::Node::setRightChild(Node* rightChild)
{
	m_rightChild = rightChild;
}
void BinaryTree::Node::setLeftChild(Node* leftChild)
{
	m_leftChild = leftChild;
}