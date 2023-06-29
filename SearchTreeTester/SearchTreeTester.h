#pragma once

#include "..\BinaryTreeTester\BinaryTreeTester.h"
#include "..\SearchTree\SearchTree.h"


class SearchTreeTester : public BinaryTreeTester
{
public:
    SearchTreeTester(const bool useConsoleOutput);
    ~SearchTreeTester() = default;

protected:
    BinaryTree* allocateTree() override;
    void deallocateTree(BinaryTree* tree) override;
    void check_addAndCount(const BinaryTree* tree, const int size) override;
    void check_remove(const BinaryTree* tree, const int size) override;
    void check_clear(const BinaryTree* tree, const int size) override;
    void check_assign(std::vector<BinaryTree::Node*> tree1Nodes, std::vector<BinaryTree::Node*> tree2Nodes) override;

private:
    bool isSearchTree(const BinaryTree* tree);
    void getKeysLnr(std::vector<int>& keys, BinaryTree::Node* node);
};
