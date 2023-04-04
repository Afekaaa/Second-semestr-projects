#include "BinaryTree.h"

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

int BinaryTree::getHeight(Node* root) const
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

int BinaryTree::getAmountNode(Node* root) const
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

BinaryTree::Node* BinaryTree::addNode(Node* root, int key)
{
	if (!root)
		root = new Node(key);
	else if (rand() % 2)
		root->setLeftChild(addNode(root->getLeftChild(), key));
	else
		root->setRightChild(addNode(root->getRightChild(), key));
	
	return root;
}

bool deleteNode(int key);

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

std::vector<int> BinaryTree::getAllKeys(std::vector<int> binaryTreeValues = {}, Node* root = nullptr) const
{
	if (!root)
	{
		binaryTreeValues.push_back(root->getKey());
		binaryTreeValues = BinaryTree::getAllKeys(binaryTreeValues, root->getRightChild());
		binaryTreeValues = BinaryTree::getAllKeys(binaryTreeValues, root->getLeftChild());
	}

	return binaryTreeValues;
}

void BinaryTree::printTree() const
{

}

BinaryTree& operator= (const BinaryTree& other);