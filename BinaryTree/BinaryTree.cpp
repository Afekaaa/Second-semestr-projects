#include "BinaryTree.h"
#include <iostream>
#include <random>

BinaryTree::BinaryTree(const BinaryTree& other)
{
	m_root = new Node(*other.getRoot());
}

BinaryTree::~BinaryTree()
{
	clear(m_root);
}

BinaryTree::Node* BinaryTree::getRoot() const
{
	return m_root;
}

bool BinaryTree::isEmpty() const
{
	if (!m_root)
		return true;

	return false;
}

int BinaryTree::getHeight(const Node * root) const
{
	int rightHeight = 0;
	int leftHeight = 0;
	int maxHeight = 0;

	if (root)
	{
		rightHeight += getHeight(root->getRightChild());
		leftHeight += getHeight(root->getLeftChild());

		if (rightHeight > leftHeight)
			maxHeight = rightHeight;
		else
			maxHeight = leftHeight;

		maxHeight++;
	}

	return maxHeight;
}

int BinaryTree::getAmountNode(const Node * root) const
{
	int counterNode = 0;

	if (root)
	{
		counterNode += getAmountNode(root->getLeftChild());
		counterNode += getAmountNode(root->getRightChild());	

		counterNode++;
	}

	return counterNode;
}

int BinaryTree::getMinKey(const Node* root) const
{
	if (!root)
	{
		std::cerr << "Tree is empty" << std::endl;
		exit(0);
	}

	return getMinKey(root, root->getKey());
}

int BinaryTree::getMinKey(const Node* root, const int key) const
{
	if (!root)
		return key;

	int minKey = root->getKey();
	int rightMinKey = getMinKey(root->getRightChild(), minKey);
	int leftMinKey = getMinKey(root->getLeftChild(), minKey);

	return std::min({ minKey, rightMinKey, leftMinKey });
}

int BinaryTree::getMaxKey(const Node* root) const
{
	if (!root)
	{
		std::cerr << "Tree is empty" << std::endl;
		exit(0);
	}

	return getMaxKey(root, root->getKey());
}

int BinaryTree::getMaxKey(const Node* root, const int key) const
{
	if (!root)
		return key;

	int maxKey = root->getKey();
	int rightMaxKey = getMaxKey(root->getRightChild(), maxKey);
	int leftMaxKey = getMaxKey(root->getLeftChild(), maxKey);

	return std::min({ maxKey, rightMaxKey, leftMaxKey });
}

bool BinaryTree::keyInTree(const int key) const
{
	std::vector<int> binaryTreeValues = getAllKeys(m_root, binaryTreeValues);

	for (int i = 0; i < binaryTreeValues.size(); ++i)
	{
		if (key == binaryTreeValues[i])
			return true;
	}

	return false;
}

BinaryTree::Node* BinaryTree::addNode(Node* root, const int key)
{
	srand(time_t(0));
	if (!root)
		root = new Node(key);
	else if (rand() % 2)
		root->setLeftChild(addNode(root->getLeftChild(), key));
	else
		root->setRightChild(addNode(root->getRightChild(), key));
	
	return root;
}

bool BinaryTree::deleteNode(const int key)
{
	if (!keyInTree(key))
	{
		return false;
	}
	
}

void BinaryTree::clear(Node* root)
{
	if (!root)
		return;

	if (root->getRightChild())
	{
		clear(root->getRightChild());
		delete root->getRightChild();
	}

	if (root->getLeftChild())
	{
		clear(root->getLeftChild());
		delete root->getLeftChild();
	}

	delete root;
}

std::vector<int> BinaryTree::getAllKeys(const Node * root = nullptr, std::vector<int> binaryTreeValues = {}) const
{
	if (!root)
	{
		binaryTreeValues.push_back(root->getKey());
		binaryTreeValues = BinaryTree::getAllKeys(root->getRightChild(), binaryTreeValues);
		binaryTreeValues = BinaryTree::getAllKeys(root->getLeftChild(), binaryTreeValues);
	}

	return binaryTreeValues;
}

void BinaryTree::printTree() const
{

}

BinaryTree& BinaryTree::operator= (const BinaryTree& other)
{
	if (m_root != other.getRoot())
	{
		clear(m_root);
		m_root = new Node(*other.getRoot());
	}

	return *this;
}

void BinaryTree::clearAllTree()
{
	clear(m_root);
	m_root = nullptr;
}