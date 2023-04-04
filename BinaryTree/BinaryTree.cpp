#include "BinaryTree.h"

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

int BinaryTree::getHeight() const
{

}
int BinaryTree::getAmountNode(Node* root) const
{
	int counterNode = 0;

	if (root != nullptr)
	{
		getAmountNode(root->getLeftChild());
		getAmountNode(root->getRightChild());

		counterNode++;
	}

	return counterNode;
}

void addNode();
void deleteNode();
void clear();

std::vector<int> getAllKeys() const;
void printTree() const;

BinaryTree& operator= (const BinaryTree& other);