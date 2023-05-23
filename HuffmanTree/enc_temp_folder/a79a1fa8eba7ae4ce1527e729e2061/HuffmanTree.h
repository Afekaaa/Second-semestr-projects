#pragma once

#include <iostream>
#include <list>

struct SymbolCode
{
	char symbol;
	std::string code;
};

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
		void setLeftChild(const Node* leftChild);
		void setRightChild(const Node* rightCild);

		Node* operator + (const Node otherNode);
		Node* operator ++ ();

	private:
		std::string m_symbols = "\0";
		int m_frequency = 1;
		Node* m_leftChild = nullptr;
		Node* m_rightChild = nullptr;
	};

	HuffmanTree() = default;
	~HuffmanTree();

	std::string build(std::string textBeforEncryption);
	int encode(std::string textBeforEncryption, std::string* textAfterEncryption) const;
	bool decode(std::string textAfterEncryption, std::string* textBeforEncryption);

private:
	Node* m_root = nullptr;

	void createSortedNodes(std::list<Node*>& nodes, std::string textBeforEncryption) const;
	Node* getJoinedTwoNodes(Node* firstNode, Node* secondNode) const;
	void setNewNodeToList(std::list<Node*>& nodes, Node* newNode) const;
	bool symbolInSymbols(std::string symbols, char symbol) const;
	std::string getCode(std::list<SymbolCode> symbolsCode, const char symbol) const;
	void encodeSymbols(std::list<SymbolCode>& symbolsCode) const;

	std::string getEncryptionText(std::list<SymbolCode> symbolsCode, std::string textBeforEncryption);

	void clear();
	void clear(Node* root);
};

