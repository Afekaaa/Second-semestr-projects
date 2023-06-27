#pragma once

#include "..\BinaryTree\BinaryTree.h"


class SearchTree :
    public BinaryTree
{
public:
    SearchTree() = default;
    ~SearchTree() = default;

    int getMaxKey() const override;
    int getMaxKey(const Node* root) const override;
    int getMinKey() const override;
    int getMinKey(const Node* root) const override;

    Node* findNode(Node* root, const int key) const;

    Node* addNode(const int key) override;
    Node* addNode(Node* root, const int key) override;
    bool remove(const int key) override;

    //SearchTree& operator= (const SearchTree& other)/* = default*/;

private:
    Node* getParent(Node* root) const;
};

