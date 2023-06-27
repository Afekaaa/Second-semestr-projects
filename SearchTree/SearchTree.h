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

    Node* addNode(const int key);
    Node* addNode(Node* root, const int key) override;
    bool deleteNode(const int key) override { return false; };

    SearchTree& operator= (const SearchTree& other)/* = default*/;

private:

};

