#include "BinaryTreeTester.h"


BinaryTreeTester::BinaryTreeTester(const bool useConsoleOutput)
    : m_useConsoleOutput(useConsoleOutput)
{}

void BinaryTreeTester::test(const int size)
{
    if (size == 0)
        return;
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

BinaryTree* BinaryTreeTester::allocateTree()
{
    return new BinaryTree;
}

void BinaryTreeTester::deallocateTree(BinaryTree* tree)
{
    delete tree;
}

void BinaryTreeTester::addAndCount()
{
    BinaryTree* tree = allocateTree();
    check_addAndCount(tree, 0);

    for (int i = 0; i < m_maxSize; ++i) {
        tree->addNode(i);
        check_addAndCount(tree, i + 1);
    }

    deallocateTree(tree);
}

void BinaryTreeTester::check_addAndCount(const BinaryTree* tree, const int size)
{
    assert(tree->getAmountNode() == size);
}

void BinaryTreeTester::destructor()
{
    const int runsCount = 200;
    for (int i = 0; i < runsCount; i++)
    {
        BinaryTree* tree = allocateTree();
        for (int i = 0; i < m_maxSize; ++i) {
            tree->addNode(i);
        }
        deallocateTree(tree);
    }
    std::cout << "BinaryTreeTester::destructor ended. Press any key to continue..." << std::endl;
    getchar();

}

void BinaryTreeTester::remove()
{
    int invalidKey = -1;
    std::vector<int> nodeKeys;

    BinaryTree* tree = allocateTree();
    tree->remove(invalidKey);
    check_remove(tree, nodeKeys.size());

    for (int i = 0; i < m_maxSize; ++i) {
        nodeKeys.push_back(i);
        tree->addNode(i);
    }

    if (m_useConsoleOutput)
    {
        tree->printTree();
        std::cout << "______________________________________________________________________" << std::endl;
    }

    while (!nodeKeys.empty()) {
        int removedNodeIndex = rand() % nodeKeys.size(); //3

        tree->remove(invalidKey);
        check_remove(tree, nodeKeys.size());

        tree->remove(nodeKeys[removedNodeIndex]);
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);
        check_remove(tree, nodeKeys.size());
        if (m_useConsoleOutput)
        {
            tree->printTree();
            std::cout << "______________________________________________________________________" << std::endl;
        }
    }
    if (m_useConsoleOutput)
    {
        tree->printTree();
        std::cout << "______________________________________________________________________" << std::endl;
    }
    tree->remove(invalidKey);
    check_remove(tree, nodeKeys.size());
    deallocateTree(tree);
}

void BinaryTreeTester::check_remove(const BinaryTree* tree, const int size)
{
    assert(tree->getAmountNode() == size);
}

void BinaryTreeTester::clear()
{
    BinaryTree* tree = allocateTree();

    for (int i = 0; i < 200; i++)
    {
        for (int i = 0; i < m_maxSize; ++i) 
        {
            tree->addNode(i);
        }
        tree->clear();
        check_clear(tree, 0);
    }

    deallocateTree(tree);
    std::cout << "BinaryTreeTester::destructor ended. Press any key to continue..." << std::endl;
    getchar();
}

void BinaryTreeTester::check_clear(const BinaryTree* tree, const int size)
{
    assert(tree->getAmountNode() == size);
}

void BinaryTreeTester::check_assign(std::vector<BinaryTree::Node*> tree1Nodes, std::vector<BinaryTree::Node*> tree2Nodes)
{
    auto treeIter1 = tree1Nodes.begin();
    auto treeIter2 = tree2Nodes.begin();

    for (; treeIter1 != tree1Nodes.end() and treeIter2 != tree2Nodes.end(); ++treeIter1, ++treeIter2)
    {
        if ((*treeIter1) or (*treeIter2))
        {
            assert(!((*treeIter1) == nullptr and (*treeIter2) != nullptr) or ((*treeIter1) != nullptr and (*treeIter2) == nullptr));
            assert((*treeIter1) != (*treeIter2));
            assert((*treeIter1)->getKey() == (*treeIter2)->getKey());
        }
    }
}

void BinaryTreeTester::assign()
{
    BinaryTree tree1;
    int size = m_maxSize;

    for (int i = 0; i < size; ++i) {
        tree1.addNode(i);
    }

    BinaryTree tree2 = tree1; //Конструктор копирования

    std::vector<BinaryTree::Node*> tree1Nodes = treeNodes(&tree1);
    std::vector<BinaryTree::Node*> tree2Nodes = treeNodes(&tree2);

    check_assign(tree1Nodes, tree2Nodes);

    tree1 = tree2; //Присваивание

    tree1Nodes = treeNodes(&tree1);
    tree2Nodes = treeNodes(&tree2);

    check_assign(tree1Nodes, tree2Nodes);
}

std::vector<BinaryTree::Node*> BinaryTreeTester::treeNodes(const BinaryTree* tree)
{
    std::vector<BinaryTree::Node*> nodes;

    std::queue<BinaryTree::Node*> nodesToProcess;
    nodesToProcess.push(tree->getRoot());
    while (!nodesToProcess.empty()) {
        BinaryTree::Node* node = nodesToProcess.front();
        if (node != nullptr) {
            nodesToProcess.push(node->getLeftChild());
            nodes.push_back(node);
            nodesToProcess.push(node->getRightChild());
        }
        nodesToProcess.pop();
    }

    return nodes;
}

void BinaryTreeTester::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree& tree, const int height)
{
    assert(tree.getHeight() == height);
}

void BinaryTreeTester::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
}

void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node* runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setLeftChild(new BinaryTree::Node(i));
        runner = runner->getLeftChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyRightSubtree()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node* runner = longTree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setRightChild(new BinaryTree::Node(i));
        runner = runner->getRightChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node* leftRunner = longTree.getRoot();
    BinaryTree::Node* rightRunner = longTree.getRoot();
    for (int i = 1; i < m_maxSize / 2; ++i) {
        leftRunner->setLeftChild(new BinaryTree::Node(i));
        leftRunner = leftRunner->getLeftChild();
        check_height(longTree, i + 1);


        rightRunner->setRightChild(new BinaryTree::Node(i));
        rightRunner = rightRunner->getLeftChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    BinaryTree longTree;
    longTree.addNode(0);
    BinaryTree::Node* leftRunner = longTree.getRoot();
    BinaryTree::Node* rightRunner = longTree.getRoot();

    leftRunner->setLeftChild(new BinaryTree::Node(1));
    leftRunner = leftRunner->getLeftChild();
    rightRunner->setRightChild(new BinaryTree::Node(1));
    rightRunner = rightRunner->getRightChild();

    for (int i = 2; i < m_maxSize / 2; ++i) {
        if (rand() % 2 == 0)
        {
            leftRunner->setLeftChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getLeftChild();
        }
        else
        {
            leftRunner->setRightChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getRightChild();
        }
        check_height(longTree, i + 1);

        if (rand() % 2 == 0)
        {
            rightRunner->setLeftChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftChild();
        }
        else
        {
            rightRunner->setRightChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getRightChild();
        }
        check_height(longTree, i + 1);
    }
}

//int main()
//{
//    const int maxSize = 1;
//    BinaryTreeTester BTTester = BinaryTreeTester(true);
//    BTTester.test(maxSize);
//    return 0;
//}