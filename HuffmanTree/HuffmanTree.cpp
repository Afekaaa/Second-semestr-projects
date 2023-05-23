#include "HuffmanTree.h"


std::string HuffmanTree::build(std::string textBeforEncryption)
{
	std::list<Node*> nodes;

	createNodes(nodes, textBeforEncryption);

	nodes.sort([](Node* first, Node* second)
		{
			return first->getFrequency() < second->getFrequency();
		});

	while (nodes.size() != 1)
	{
		auto firstNode = nodes.begin();
		auto secondNode = nodes.begin()++;

		Node* newNode = getJoinedTwoNodes(*firstNode, *secondNode);

		setNewNodeToList(nodes, newNode);
		nodes.erase(firstNode, secondNode);
	}

	m_root = nodes.front();
	std::list<SymbolCode> symbolsCode;

	for (int i = 0; m_root->getSymbols()[i]; i++)
	{
		auto treeIter = m_root;

		std::string symbolCode;
		char symbol = m_root->getSymbols()[i];

		while (treeIter->getLeftChild() or treeIter->getRightChild())
		{
			if (symbolInSymbols(treeIter->getLeftChild()->getSymbols(), symbol)) {
				treeIter = treeIter->getLeftChild();
				symbolCode += '0';
			}
			else
			{
				treeIter = treeIter->getRightChild();
				symbolCode += '1';
			}
		}

		symbolsCode.push_back({ symbol, symbolCode });
	}

	std::string textAfterEncryption;

	for (int i = 0; textBeforEncryption[i]; i++)
	{
		textAfterEncryption += getCode(symbolsCode, textBeforEncryption[i]);
	}

	return textAfterEncryption;
}

void HuffmanTree::createNodes(std::list<Node*>& nodes, std::string textBeforEncryption) const
{
	int T[256] = { 0 };

	for (int i = 0; textBeforEncryption[i]; i++)
	{
		if (!T[textBeforEncryption[i]])
		{
			T[textBeforEncryption[i]] = 1;
			nodes.push_back(new Node(textBeforEncryption[i]));
		}
		else
		{
			auto iter = nodes.begin();

			for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
			{
				if ((*iter)->getSymbols()[0] == textBeforEncryption[i])
				{
					(*iter)++;
				}
			}
		}
	}
}

HuffmanTree::Node* HuffmanTree::getJoinedTwoNodes(Node* firstNode, Node* secondNode) const
{
	Node* newNode = new Node(*(*firstNode + *secondNode));
	return newNode;
}

void HuffmanTree::setNewNodeToList(std::list<Node*>& nodes, Node* newNode) const
{
	auto posNode = nodes.begin();
	auto nextNode = posNode++;

	while ((*posNode)->getFrequency() < (*nextNode)->getFrequency())
	{
		posNode++;
		nextNode++;
	}
		
	nodes.insert(posNode, newNode);
}

bool HuffmanTree::symbolInSymbols(std::string symbols, char symbol) const
{
	for (int i = 0; symbols[i]; i++)
	{
		if (symbols[i] == symbol)
			return true;
	}

	return false;
}

std::string HuffmanTree::getCode(std::list<SymbolCode> symbolsCode, const char symbol) const
{
	for (auto iter : symbolsCode)
	{
		if (iter.symbol == symbol)
			return iter.code;
	}
}