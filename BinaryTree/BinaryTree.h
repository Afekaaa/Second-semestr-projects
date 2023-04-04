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
		Node(Node& other);
		Node(int key);
		~Node() = default;

		int getKey() const;
		void setKey(const int key);
		Node* getRightChild() const;
		Node* getLeftChild() const;

		void setRightChild(Node* rightChild);
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
	int getHeight(Node* root) const;
	int getAmountNode(Node* root) const;

	Node* addNode(Node* root, int key);
	bool deleteNode(int key);
	void clear(Node* root);

	std::vector<int> getAllKeys(std::vector<int> binaryTreeValues, Node* root) const;
	void printTree() const;

	BinaryTree& operator= (const BinaryTree& other);


private:
	Node* m_root = nullptr;

};

