#pragma once

#include "..\BinaryTree\BinaryTree.h"


class SearchTree : public BinaryTree
{
public:
    SearchTree() = default;
    ~SearchTree() override = default;

    using BinaryTree::Node;

    int getMaxKey() const override;
    int getMinKey() const override;

    int getMaxKey(const Node* root) const override;
    int getMinKey(const Node* root) const override;

    Node* addNode(const int key) override;
    Node* addNode(Node* root, const int key) override;

    bool remove(const int key) override;

    Node* findNode(Node* root, const int key) const;

    //SearchTree& operator= (const SearchTree& other)/* = default*/;

private:
    Node* getParent(Node* root) const; 
    Node* getReplacementRoot(Node* root) const;
};

