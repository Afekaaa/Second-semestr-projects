#include "SearchTreeTester.h"

SearchTreeTester::SearchTreeTester(const bool useConsoleOutput)
    : BinaryTreeTester(useConsoleOutput)
{}

BinaryTree* SearchTreeTester::allocateTree()
{
    return new SearchTree;
}

void SearchTreeTester::deallocateTree(BinaryTree* tree)
{
    delete tree;
}

void SearchTreeTester::check_addAndCount(const BinaryTree* tree, const int size)
{
    BinaryTreeTester::check_addAndCount(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_remove(const BinaryTree* tree, const int size)
{
    BinaryTreeTester::check_remove(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_clear(const BinaryTree* tree, const int size)
{
    BinaryTreeTester::check_clear(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_assign(std::vector<BinaryTree::Node*> tree1Nodes, std::vector<BinaryTree::Node*> tree2Nodes)
{
    BinaryTreeTester::check_assign(tree1Nodes, tree2Nodes);

    auto firstTreeIter = ++tree1Nodes.begin();
    auto secondTreeIter = tree1Nodes.begin();

    for (; firstTreeIter != tree1Nodes.end(); ++firstTreeIter, ++secondTreeIter)
    {
        assert((*secondTreeIter)->getKey() < (*firstTreeIter)->getKey());
    }

}

int main()
{
    const int maxSize = 5;
    SearchTreeTester STTester = SearchTreeTester(true);

    STTester.test(5);
}

bool SearchTreeTester::isSearchTree(const BinaryTree* tree)
{
    std::vector<int> keys;

    getKeysLnr(keys, tree->getRoot());

    for (int i = 1; i < keys.size(); i++)
    {
        if (keys[i] <= keys[i - 1])
        {
            return false;
        }
    }

    return true;
}

void SearchTreeTester::getKeysLnr(std::vector<int>& keys, BinaryTree::Node* node)
{
    if (!node)
        return;
    if (node->getLeftChild())
        getKeysLnr(keys, node->getLeftChild());
    keys.push_back(node->getKey());
    if (node->getRightChild())
        getKeysLnr(keys, node->getRightChild());
}