#include "HuffmanTree.h"


HuffmanTree::~HuffmanTree()
{
	clear();
}

void HuffmanTree::build(std::string textBeforEncryption)
{
	std::list<Node*> nodes;
	createSortedNodes(nodes, textBeforEncryption);

	if (m_root)
		clear();

	m_root = nodes.front();
}

int HuffmanTree::encode(std::string textBeforEncryption, std::string* textAfterEncryption)
{
	if (!m_root)
		build(textBeforEncryption);

	bool successfulEncoding = createEncryptionText(*textAfterEncryption, textBeforEncryption);
	if (successfulEncoding)
		return textAfterEncryption->size() / (textBeforEncryption.size() * 8) * 100;
	else
		return -1;
}

bool HuffmanTree::decode(std::string textAfterEncryption, std::string* textAfterDecoding) 
{
	return createTextAfterDecoding(*textAfterDecoding, textAfterEncryption);
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

void HuffmanTree::encodeSymbols() const 
{
	for (int i = 0; m_root->getSymbols()[i]; i++)
	{
		auto treeIter = m_root;
		char symbol = m_root->getSymbols()[i];

		while (treeIter->getLeftChild() or treeIter->getRightChild())
		{
			if (symbolInSymbols(treeIter->getLeftChild()->getSymbols(), symbol)) {
				treeIter = treeIter->getLeftChild();
				treeIter->getCode() += "0";
			}
			else
			{
				treeIter = treeIter->getRightChild();
				treeIter->getCode() += "1";
			}
		}
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

bool HuffmanTree::createEncryptionText(std::string& textAfterEncryption, std::string textBeforEncryption)
{

	for (int i = 0; textBeforEncryption[i]; i++)
	{
		std::string codeOfNextSymbol = getCode(textBeforEncryption[i]);
		if (codeOfNextSymbol == "-1") return false;
		else textAfterEncryption += codeOfNextSymbol;
	}

	return true;
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

std::string HuffmanTree::getCode(const char symbol) const
{
	auto treeIter = m_root;

	while (treeIter->getRightChild())
	{
		if (symbolInSymbols(treeIter->getLeftChild()->getSymbols(), symbol))
			treeIter = treeIter->getLeftChild();
		else if (symbolInSymbols(treeIter->getRightChild()->getSymbols(), symbol))
			treeIter = treeIter->getRightChild();
		else
			return "-1";
	}

	return treeIter->getCode();
}

bool HuffmanTree::createTextAfterDecoding(std::string& textAfterDecoding, std::string textAfterEncryption)
{
	auto treeIter = m_root;

	for (int i = 0; textAfterEncryption[i]; ++i)
	{
		if (textAfterEncryption[i] == '0')
			treeIter = treeIter->getLeftChild();
		else
			treeIter = treeIter->getRightChild();

		if (treeIter->getSymbols().length() == 1)
		{
			textAfterDecoding += treeIter->getSymbols();
			treeIter = m_root;
		}
	}

	if (treeIter == m_root)
		return true;
	else
		return false;
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