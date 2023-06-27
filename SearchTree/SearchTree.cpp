#include "SearchTree.h"
#include <iostream>


int SearchTree::getMaxKey() const
{
	return getMaxKey(m_root);
}

int SearchTree::getMaxKey(const Node* root) const
{
	if (!root)
	{
		throw std::invalid_argument("передан nullptr в функцию поиска максимума дерева"); // Понять, где его ловить и нужно ли.
		return NULL;
	}

	const Node* runner = root;

	while (!(runner = runner->getRightChild())) {}

	return runner->getKey();
}

int SearchTree::getMinKey() const
{
	return getMinKey(m_root);
}
int SearchTree::getMinKey(const Node* root) const
{
	if (!root)
	{
		throw std::invalid_argument("передан nullptr в функцию поиска минимума дерева"); 
		return NULL;
	}

	Node* runner;

	while (!(runner = root->getLeftChild())){}

	return runner->getKey();
}

BinaryTree::Node* SearchTree::addNode(const int key)
{
	return addNode(m_root, key);
}
BinaryTree::Node* SearchTree::addNode(Node* root, const int key)
{
	if (!root)
	{
		root = new Node(key);
	}
	else if (key < root->getKey())
	{
		root->setLeftChild(addNode(root->getLeftChild(), key));
	}
	else
	{
		root->setRightChild(addNode(root->getRightChild(), key));
	}

	return root;
}

BinaryTree::Node* SearchTree::findNode(Node* root, const int key) const
{

	if (key < root->getKey())
	{
		return findNode(root->getLeftChild(), key);
	}
	else if (key > root->getKey())
	{
		return findNode(root->getRightChild(), key);
	}

	return root;
}

/*SearchTree& SearchTree::operator= (const SearchTree& other)
{
	if (m_root != other.getRoot())
	{
		BinaryTree::clear(m_root);
		m_root = new Node(*other.getRoot());
	}

	return *this;
}*/

bool SearchTree::remove(const int key)
{
	Node* rootToBeDeleted;
	if (!(rootToBeDeleted = findNode(m_root, key)))
		return false;

	Node* rootParent = getParent(rootToBeDeleted);

	if (rootToBeDeleted->getAmountChildren() == 0)
	{
		if (rootParent)
		{
			if (rootParent->getLeftChild() == rootToBeDeleted)
				rootParent->setLeftChild(nullptr);
			else if (rootParent->getRightChild() == rootToBeDeleted)
				rootParent->setRightChild(nullptr);
		}

		delete rootToBeDeleted;
	}
	else if (rootToBeDeleted->getAmountChildren() == 1)
	{
		Node* replacementRoot = nullptr;

		if (rootToBeDeleted->getLeftChild())
			replacementRoot = rootToBeDeleted->getLeftChild();
		else
			replacementRoot = rootToBeDeleted->getRightChild();

		if (rootParent)
		{
			if (rootParent->getLeftChild() == rootToBeDeleted)
				rootParent->setLeftChild(nullptr);
			else if (rootParent->getRightChild() == rootToBeDeleted)
				rootParent->setRightChild(nullptr);
		}

		delete rootToBeDeleted;
	}
	else
	{
		//1. Find replacementRoot
		//2. Find parentReplacementRoot
		//

		Node* replacementRoot = getReplacementRoot(rootToBeDeleted);
		Node* parentReplacementRoot = getParent(replacementRoot);

		if (parentReplacementRoot == rootToBeDeleted)
		{
			replacementRoot->setLeftChild(rootToBeDeleted->getLeftChild());
		}
		else
		{
			parentReplacementRoot->setLeftChild(replacementRoot->getRightChild());
			replacementRoot->setLeftChild(rootToBeDeleted->getLeftChild());
			replacementRoot->setRightChild(rootToBeDeleted->getRightChild());
		}

		if (rootParent)
		{
			if (rootParent->getLeftChild() == rootToBeDeleted)
				rootParent->setLeftChild(nullptr);
			else if (rootParent->getRightChild() == rootToBeDeleted)
				rootParent->setRightChild(nullptr);
		}

		delete rootToBeDeleted;
	}
}
BinaryTree::Node* SearchTree::getParent(Node* root) const
{
	Node* parentRoot = m_root;

	if (root == parentRoot) return nullptr;

	while (true)
	{
		if (root->getKey() < parentRoot->getKey())
			if (parentRoot->getLeftChild() == root)
				break;
			else
				parentRoot = parentRoot->getLeftChild();
		else
			if (parentRoot->getRightChild() == root)
				break;
			else
				parentRoot = parentRoot->getRightChild();
	}
}
BinaryTree::Node* SearchTree::getReplacementRoot(Node* root) const
{
	Node* runner = root->getRightChild();
	while (runner->getLeftChild()) runner = runner->getLeftChild();

	return runner;
}

int main()
{
	SearchTree tree;
	tree.addNode(10);

	SearchTree newTree;
	newTree = tree;

	std::cout << newTree.getRoot();

	return 0;
}