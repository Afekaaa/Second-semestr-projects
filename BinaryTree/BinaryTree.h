#include "Node.h"
#include <vector>

#pragma once


class BinaryTree
{
public:
	class Node
	{
	public:
		Node();
		Node(int key);
		~Node() = default;

		int getKey() const;
		void setKey(const int key);
		Node* getRightChild() const;
		Node* getLeftChild() const;

		void setRigthChild(Node* rightChild);
		void setLeftChild(Node* leftChild);

	private:
		int m_key;
		Node* m_rightChild = nullptr;
		Node* m_leftChild = nullptr;
		Node* m_parent = nullptr;
	};

	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();

	Node* getRoot() const;
	bool isEmpty() const;
	int getHeight() const;
	int getAmountNode(Node* root) const;

	void addNode();
	void deleteNode();
	void clear();

	std::vector<int> getAllKeys() const;
	void printTree() const;

	BinaryTree& operator= (const BinaryTree& other);


private:
	Node* m_root = nullptr;

};

