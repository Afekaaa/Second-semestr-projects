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

		std::string& getCode();

		void setSymbols(std::string symbols);
		void setFrequency(const int frequency);
		void setLeftChild(const Node* leftChild);
		void setRightChild(const Node* rightCild);

	private:
		std::string m_symbols;
		std::string m_code;
		int m_frequency = 1;
		Node* m_leftChild = nullptr;
		Node* m_rightChild = nullptr;
	};

	HuffmanTree() = default;
	~HuffmanTree();

	void build(std::string textBeforEncryption);
	float encode(std::string textBeforEncryption, std::string* textAfterEncryption);
	bool decode(std::string textAfterEncryption, std::string* textBeforEncryption);

private:
	Node* m_root = nullptr;

	void createSortedNodes(std::list<Node*>& nodes, std::string textBeforEncryption) const;
	Node* getJoinedTwoNodes(Node* firstNode, Node* secondNode) const;
	void setNewNodeToList(std::list<Node*>& nodes, Node* newNode) const;
	bool symbolInSymbols(std::string symbols, char symbol) const;
	std::string getCode(const char symbol) const;
	void encodeSymbols() const;

	bool createEncryptionText(std::string& textAfterEncryption, std::string textBeforEncryption);
	bool createTextAfterDecoding(std::string& textAfterDecoding, std::string textAfterEncryption);

	void clear();
	void clear(Node* root);
};

