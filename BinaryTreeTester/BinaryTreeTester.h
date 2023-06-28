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
    virtual void check_addAndCount(const BinaryTree* tree, const int size);
    virtual void check_remove(const BinaryTree* tree, const int size);
    virtual void check_clear(const BinaryTree* tree, const int size);
    //ToDo: virtual check_assign()
    virtual void check_height(const BinaryTree& tree, const int size);

private:
    void deallocateTree(BinaryTree* tree);
    void addAndCount();
    void destructor();
    void remove();
    void clear(); //ToDo: реализовать
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees(); 
    std::vector<const BinaryTree::Node*> treeNodes(const BinaryTree* tree);

private:
    int m_maxSize;
    bool m_useConsoleOutput;
};
