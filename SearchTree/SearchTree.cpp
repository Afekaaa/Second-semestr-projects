#include "SearchTree.h"


int SearchTree::getMaxKey() const
{
	return getMaxKey(m_root);
}

int SearchTree::getMaxKey(const Node* root) const
{
	if (!root)
	{
		throw std::invalid_argument("передан nullptr в функцию поиска максимума дерева, либо поддерева.");
		return NULL;
	}

	const Node* runner = root;

	while (runner->getRightChild())
	{
		runner = runner->getRightChild();
	}

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
	if (isEmpty())
		return m_root = new Node(key);
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

BinaryTree::Node * SearchTree::findNode(const int key) const
{
	if (isEmpty())
		return nullptr;

	return findNode(m_root, key);
}

BinaryTree::Node* SearchTree::findNode(Node* root, const int key) const
{
	if (!root)
		return nullptr;

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
	if (!(rootToBeDeleted = findNode(key)))
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
		else
			m_root = nullptr;

		delete rootToBeDeleted;

		return true;
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
				rootParent->setLeftChild(replacementRoot);
			else if (rootParent->getRightChild() == rootToBeDeleted)
				rootParent->setRightChild(replacementRoot);
		}
		else
			m_root = replacementRoot;

		delete rootToBeDeleted;

		return true;
	}
	else
	{
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
				rootParent->setLeftChild(replacementRoot);
			else if (rootParent->getRightChild() == rootToBeDeleted)
				rootParent->setRightChild(replacementRoot);
		}
		else
		{
			m_root = replacementRoot;
		}

		delete rootToBeDeleted;

		return true;
	}
}
BinaryTree::Node* SearchTree::getParent(Node* root) const
{
	if (root == m_root) 
		return nullptr;

	Node* parentRoot = m_root;

	while (true)
	{
		if (root->getKey() < parentRoot->getKey())
			if (parentRoot->getLeftChild() == root)
				return parentRoot;
			else
				parentRoot = parentRoot->getLeftChild();
		else
			if (parentRoot->getRightChild() == root)
				return parentRoot;
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

//int main()
//{
//	srand(time(0));
//
//	const int amountNode = 10;
//
//	SearchTree tree;
//
//	for (int i = 0; i < amountNode; ++i)
//	{
//		tree.addNode(rand() % 100);
//	}
//
//	tree.printTree(5, 3);
//
//	return 0;
//}