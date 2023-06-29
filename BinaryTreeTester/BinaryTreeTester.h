#pragma once

#include <vector>
#include <queue>
#include <assert.h>
#include "..\BinaryTree\BinaryTree.h"

class BinaryTreeTester
{
public:
    BinaryTreeTester(const bool useConsoleOutput);
    ~BinaryTreeTester() = default;

    void test(const int size);

protected:
    virtual BinaryTree* allocateTree();
    virtual void deallocateTree(BinaryTree* tree);
    virtual void check_addAndCount(const BinaryTree* tree, const int size);
    virtual void check_remove(const BinaryTree* tree, const int size);
    virtual void check_clear(const BinaryTree* tree, const int size);
    virtual void check_assign(std::vector<BinaryTree::Node*> tree1Nodes, std::vector<BinaryTree::Node*> tree2Nodes);
    void check_height(const BinaryTree& tree, const int size);

private:

    void addAndCount();
    void destructor();
    void remove();
    void clear(); 
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees(); 
    std::vector<BinaryTree::Node*> treeNodes(const BinaryTree* tree);

private:
    int m_maxSize;
    bool m_useConsoleOutput;
};
