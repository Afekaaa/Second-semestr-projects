#pragma once 

#include <vector> 
#include <iostream> 
#include <random> 

class BinaryTree
{
public:
	class Node;

	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	virtual ~BinaryTree();

	bool isEmpty() const;
	bool keyInTree(const int key) const;

	Node* getRoot() const;
	int getHeight() const;
	int getHeight(const Node* root) const;
	int getAmountNode() const;
	int getAmountNode(const Node* root) const;

	virtual int getMaxKey() const;
	virtual int getMinKey() const;

	virtual int getMaxKey(const Node* root) const;
	virtual int getMinKey(const Node* root) const;

	virtual Node* addNode(const int key);
	virtual Node* addNode(Node* root, const int key);

	virtual bool remove(const int key);

	void clear();
	void clear(Node* root);
	void clearAllTree();

	std::vector<int> getAllKeys() const;
	std::vector<int> getAllKeys(const Node* root, std::vector<int> binaryTreeValues = {}) const;

	void printTree();
	void printTree(Node* root, int marginLeft, int levelSpacing) const;
	void printTree(int marginLeft, int levelSpacing) const;

	BinaryTree& operator= (const BinaryTree& other);
protected:
	Node* m_root = nullptr;

private:
	int getMinKey(const Node* root, const int key) const;
	int getMaxKey(const Node* root, const int key) const;

	void remove(Node* root, int key);
	void deleteRoot(Node* parentRoot, Node* node);
	void deleteMRoot();
	void setAnyLeafParent(Node*& leafParent, Node*& leaf);
};

class BinaryTree::Node
{
public:
	Node();
	Node(const Node& other);
	Node(const int key);
	~Node() = default;

	int getKey() const;
	void setKey(const int key);
	Node* getRightChild() const;
	Node* getLeftChild() const;
	int getAmountChildren() const;

	void setRightChild(Node* rightChild);
	void setLeftChild(Node* leftChild);
private:
	int m_key = 0;
	Node* m_rightChild = nullptr;
	Node* m_leftChild = nullptr;
};