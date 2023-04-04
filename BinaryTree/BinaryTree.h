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
		Node(const Node& other);
		Node(const int key);
		~Node() = default;

		int getKey() const;
		void setKey(const int key);
		Node* getRightChild() const;
		Node* getLeftChild() const;
		int getAmountChildren() const;

		void setRightChild(Node * rightChild);
		void setLeftChild(Node * leftChild);

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
	int getHeight(const Node * root) const;
	int getAmountNode(const Node * root) const;
	bool keyInTree(const int key) const;

	Node* addNode(Node* root, const int key);
	bool deleteNode(const int key);
	void clear(Node* root);

	std::vector<int> getAllKeys(const Node * root, std::vector<int> binaryTreeValues) const;
	void printTree() const;

	BinaryTree& operator= (const BinaryTree& other);


private:
	Node* m_root = nullptr;

};

