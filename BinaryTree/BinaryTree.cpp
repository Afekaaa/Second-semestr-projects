#include "BinaryTree.h"  


BinaryTree::BinaryTree(const BinaryTree& other)
{
	m_root = new Node(*other.getRoot());
}

BinaryTree::~BinaryTree()
{
	clear(m_root);
}

bool BinaryTree::isEmpty() const
{
	if (!m_root)
		return true;

	return false;
}

BinaryTree::Node* BinaryTree::getRoot() const
{
	return m_root;
}

int BinaryTree::getHeight() const
{
	return getHeight(m_root);
}

int BinaryTree::getHeight(const Node* root) const
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
int BinaryTree::getAmountNode() const
{
	return getAmountNode(m_root);
}
int BinaryTree::getAmountNode(const Node* root) const
{
	int counterNode = 0;

	if (root)
	{
		if (root->getLeftChild())
			counterNode += getAmountNode(root->getLeftChild());
		if (root->getRightChild())
			counterNode += getAmountNode(root->getRightChild());

		counterNode++;
	}

	return counterNode;
}

int BinaryTree::getMinKey(const Node* root) const
{
	if (!root)
	{
		throw std::invalid_argument("передан nullptr в функцию поиска минимума дерева, либо поддерева.");
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
		throw std::invalid_argument("передан nullptr в функцию поиска максимума дерева, либо поддерева.");
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

int BinaryTree::getMaxKey() const
{
	return getMaxKey(m_root);
}
int BinaryTree::getMinKey() const
{
	return getMinKey(m_root);
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

BinaryTree::Node* BinaryTree::addNode(int key)
{
	if (isEmpty())
		return m_root = new Node(key);

	return addNode(m_root, key);
}

BinaryTree::Node* BinaryTree::addNode(Node* root, const int key)
{
	srand(time(0));

	while (true)
	{
		if (rand() % 2)
		{
			if (root->getRightChild() == nullptr)
			{
				root->setRightChild(new Node(key));
				return root->getRightChild();
			}
			else
				root = root->getRightChild();
		}
		else
		{
			if (root->getLeftChild() == nullptr)
			{
				root->setLeftChild(new Node(key));
				return root->getLeftChild();
			}

			else
				root = root->getLeftChild();
		}
	}
}

bool BinaryTree::remove(const int key)
{
	if (!keyInTree(key))
		return false;

	if (m_root->getKey() == key)
		deleteMRoot();
	else
		remove(m_root, key);

	return true;
}

void BinaryTree::remove(Node* root, int key)
{
	if (root->getLeftChild())
	{
		if (root->getLeftChild()->getKey() == key)
			deleteRoot(root, root->getLeftChild());
		else
			remove(root->getLeftChild(), key);
	}
	if (root->getRightChild())
	{
		if (root->getRightChild()->getKey() == key)
			deleteRoot(root, root->getRightChild());
		else
			remove(root->getRightChild(), key);
	}
}

void BinaryTree::deleteMRoot()
{
	if (m_root->getAmountChildren() == 0)
	{
		delete m_root;
		m_root = nullptr;
	}
	else 
	{
		Node* leafParent = m_root;
		Node* leaf = nullptr;

		setAnyLeafParent(leafParent, leaf);

		if (leafParent == m_root)
		{
			m_root = leaf;
			delete leafParent;
		}
		else
		{
			if (leafParent->getRightChild())
				leafParent->setRightChild(nullptr);
			else if (leafParent->getLeftChild())
				leafParent->setLeftChild(nullptr);

			leaf->setLeftChild(m_root->getLeftChild());
			leaf->setRightChild(m_root->getRightChild());

			delete m_root;
			m_root = leaf;
		}
	}
}

void BinaryTree::deleteRoot(Node* rootParent, Node* root)
{
	if (root->getAmountChildren() == 0)
	{
		if (rootParent->getLeftChild() == root)
			rootParent->setLeftChild(nullptr);
		else if (rootParent->getRightChild() == root)
			rootParent->setRightChild(nullptr);

		delete root;
	}
	else if (root->getAmountChildren() == 1)
	{
		Node* replacementRoot = nullptr;

		if (root->getLeftChild())
			replacementRoot = root->getLeftChild();
		else
			replacementRoot = root->getRightChild();

		if (rootParent->getLeftChild() == root)
			rootParent->setLeftChild(replacementRoot);
		else if (rootParent->getRightChild() == root)
			rootParent->setRightChild(replacementRoot);

		delete root;
	}
	else
	{
		Node* leafParent = root;
		Node* replacementRoot = nullptr;

		setAnyLeafParent(leafParent, replacementRoot);

		if (leafParent->getLeftChild() == replacementRoot)
			leafParent->setLeftChild(nullptr);
		else if (leafParent->getRightChild() == replacementRoot)
			leafParent->setRightChild(nullptr);

		replacementRoot->setRightChild(root->getRightChild());
		replacementRoot->setLeftChild(root->getLeftChild());

		if (rootParent->getLeftChild() == root)
			rootParent->setLeftChild(replacementRoot);
		else if (rootParent->getRightChild() == root)
			rootParent->setRightChild(replacementRoot);

		delete root;
	}
}

void BinaryTree::setAnyLeafParent(Node*& leafParent, Node*& leaf)
{
	while (true)
	{
		if (leafParent->getLeftChild())
		{
			if (leafParent->getLeftChild()->getAmountChildren() == 0)
			{
				leaf = leafParent->getLeftChild();
				break;
			}
			else if (leafParent->getLeftChild()->getAmountChildren() != 0)
			{
				leafParent = leafParent->getLeftChild();
			}
		}

		if (leafParent->getRightChild())
		{
			if (leafParent->getRightChild()->getAmountChildren() == 0)
			{
				leaf = leafParent->getRightChild();
				break;
			}
			else if (leafParent->getRightChild()->getAmountChildren() != 0)
			{
				leafParent = leafParent->getRightChild();
			}
		}
	}
}

void BinaryTree::clear()
{
	clear(m_root);
	m_root = nullptr;
}

void BinaryTree::clear(Node* root)
{
	if (!root)
		return;

	if (root->getRightChild())
	{
		clear(root->getRightChild());
	}

	if (root->getLeftChild())
	{
		clear(root->getLeftChild());
	}

	delete root;
}

std::vector<int> BinaryTree::getAllKeys() const
{
	return getAllKeys(m_root);
}

std::vector<int> BinaryTree::getAllKeys(const Node* root, std::vector<int> binaryTreeValues) const
{
	if (root)
	{
		binaryTreeValues.push_back(root->getKey());
		binaryTreeValues = BinaryTree::getAllKeys(root->getRightChild(), binaryTreeValues);
		binaryTreeValues = BinaryTree::getAllKeys(root->getLeftChild(), binaryTreeValues);
	}

	return binaryTreeValues;
}

void BinaryTree::printTree()
{
	printTree(5, 3);
}

void BinaryTree::printTree(Node* root, int marginLeft, int levelSpacing) const
{

	if (root == nullptr)
		return;


	printTree(root->getRightChild(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
	printTree(root->getLeftChild(), marginLeft + levelSpacing, levelSpacing);

}

void BinaryTree::printTree(int marginLeft, int levelSpacing) const
{
	printTree(m_root, marginLeft, levelSpacing);
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