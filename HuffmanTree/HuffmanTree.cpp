#include "HuffmanTree.h"


HuffmanTree::~HuffmanTree()
{
	clear();
}

std::string HuffmanTree::build(std::string textBeforEncryption)
{
	std::list<Node*> nodes;
	createSortedNodes(nodes, textBeforEncryption);

	if (m_root)
		clear();

	m_root = nodes.front();
	std::list<SymbolCode> symbolsCode;

	encodeSymbols(symbolsCode);
	std::string textAfterEncryption = getEncryptionText(symbolsCode, textBeforEncryption);

	return textAfterEncryption;
}

int HuffmanTree::encode(std::string textBeforEncryption, std::string* textAfterEncryption) const
{
	return textAfterEncryption->size() / (textBeforEncryption.size() * 8) * 100;
}

bool HuffmanTree::decode(std::string textAfterEncryption, std::string* textBeforEncryption) 
{
	std::string newTextAfterEncryption = build(*textBeforEncryption);

	if (textAfterEncryption == newTextAfterEncryption)
	{
		return true;
	}

	return false;
}

void HuffmanTree::createSortedNodes(std::list<Node*>& nodes, std::string textBeforeEncryption) const
{
	int T[256] = { 0 };

	for (int i = 0; textBeforeEncryption[i]; i++)
	{
		//std::cout << textBeforeEncryption[i]  << " number is " << T[textBeforeEncryption[i]] << std::endl;
		if (!T[textBeforeEncryption[i]])
		{
			T[textBeforeEncryption[i]] = 1;
			nodes.push_back(new Node(textBeforeEncryption[i]));
		}
		else
		{
			for (auto iter: nodes)
			{
				if (iter->getSymbols()[0] == textBeforeEncryption[i])
				{
					iter->setFrequency(iter->getFrequency() + 1);
					break;
				}
			}
		}
	}

	nodes.sort([](Node* first, Node* second)
		{
			return first->getFrequency() < second->getFrequency();
		});

	while (nodes.size() != 1)
	{
		auto firstNode = nodes.begin();
		auto secondNode = ++nodes.begin();

		Node* newNode = getJoinedTwoNodes(*firstNode, *secondNode); // выделение памяти
		setNewNodeToList(nodes, newNode);
		nodes.erase(firstNode, ++secondNode);
	}
}

HuffmanTree::Node* HuffmanTree::getJoinedTwoNodes(Node* firstNode, Node* secondNode) const
{
	std::string newSymbols = secondNode->getSymbols().append(firstNode->getSymbols());
	Node* newNode = new Node(newSymbols);
	newNode->setFrequency(firstNode->getFrequency() + secondNode->getFrequency());
	newNode->setLeftChild(firstNode);
	newNode->setRightChild(secondNode);

	return newNode;
}

void HuffmanTree::encodeSymbols(std::list<SymbolCode>& symbolsCode) const 
{

	for (int i = 0; m_root->getSymbols()[i]; i++)
	{
		std::string symbolCode;

		auto treeIter = m_root;
		char symbol = m_root->getSymbols()[i];

		while (treeIter->getLeftChild() or treeIter->getRightChild())
		{
			if (symbolInSymbols(treeIter->getLeftChild()->getSymbols(), symbol)) {
				treeIter = treeIter->getLeftChild();
				symbolCode += "0";
			}
			else
			{
				treeIter = treeIter->getRightChild();
				symbolCode += "1";
			}
		}

		symbolsCode.push_back({ symbol, symbolCode });
	}
}

void HuffmanTree::setNewNodeToList(std::list<Node*>& nodes, Node* newNode) const
{
	auto posNode = nodes.begin();

	while (posNode != nodes.end() and (*posNode)->getFrequency() < newNode->getFrequency())
		posNode++;

	if (posNode != nodes.end())
		nodes.insert(posNode, newNode);
	else
		nodes.push_back(newNode);
}

std::string HuffmanTree::getEncryptionText(std::list<SymbolCode> symbolsCode, std::string textBeforEncryption)
{
	std::string textAfterEncryption;

	for (int i = 0; textBeforEncryption[i]; i++)
	{	
		textAfterEncryption += getCode(symbolsCode, textBeforEncryption[i]);
	}

	return textAfterEncryption;
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

void HuffmanTree::clear()
{
	if (!m_root)
		clear(m_root);
}

void HuffmanTree::clear(Node* root)
{
	if (root->getLeftChild())
		clear(root->getLeftChild());
	if (root->getRightChild())
		clear(root->getRightChild());

	delete root;
}

int main()
{
	std::string textBeforEncode = "There was a green grasshopper in the grass\0";
	//std::cout << textBeforEncode.size();

	HuffmanTree encodeText;
	std::cout << encodeText.build(textBeforEncode) << std::endl;

	return 0;
}