#pragma once

#include <iostream>
#include <list>

class HuffmanTree
{
public:
	class Node 
	{
	public: 
		Node() = default;
		Node(const char symbol);
		Node(const std::string symbols);
		Node(const Node& other);
		~Node() = default;

		int getFrequency() const;
		std::string getSymbols() const;
		Node* getLeftChild() const;
		Node* getRightChild() const;

		void setFrequency(const int frequency);
		void setLeftChild(Node* leftChild);
		void setRightChild(Node* rightCild);

		Node* operator + (Node* otherNode);
		Node* operator ++ ();

	private:
		std::string m_symbols;
		int m_frequency = 1;
		Node* m_leftChild = nullptr;
		Node* m_rightChild = nullptr;
	};

	std::string build(std::string textBeforEncryption);
	int encode(std::string textBeforEncryption, std::string* textAfterEncryption) const;
	bool decode(std::string textAfterEncryption, std::string* textBeforEncryption);

private:
	Node* m_root = nullptr;

	void createNodes(std::list<Node*>& nodes, std::string textBeforEncryption);
	Node* getJoinedTwoNodes(Node* firstNode, Node* secondNode);
	void setNewNodeToList(std::list<Node*>& nodes, Node* newNode);
};

