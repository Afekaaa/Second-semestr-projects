#include "SearchTree.h"
#include <iostream>

SearchTree::SearchTree(const SearchTree& other)
{
	m_root = new Node(*other.getRoot());
}
SearchTree::~SearchTree()
{
	clear(m_root);
}

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

	Node* runner;

	while (!(runner = root->getRightChild())) {}

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
		throw std::invalid_argument("передан nullptr в функцию поиска минимума дерева"); // Понять, где его ловить и нужно ли.
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

SearchTree& SearchTree::operator= (const SearchTree& other)
{
	if (m_root != other.getRoot())
	{
		BinaryTree::clear(m_root);
		m_root = new Node(*other.getRoot());
	}

	return *this;
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