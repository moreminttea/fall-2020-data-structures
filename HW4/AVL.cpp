// Mindy Mohr
// 917425752
// AVL.cpp

#include <cassert>
#include <iostream>
#include <string>
#include <queue>

#include "AVL.h"
#include "json.hpp"

/*
 * REFERENCED CITED SOURCES
 *
 *   for help on left and right rotations: AVL Tree | Set 1 Insertion. https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 */

AVL::AVL() : root_(nullptr), size_(0) {} //AVL version of BST class function

void AVL::Insert(int key){ //AVL version of BST class function
    if (root_ == nullptr)
    {
        root_ = std::make_shared<BSTNode>(key);
        size_++;
        return;
    }
    std::shared_ptr<BSTNode> currentNode = root_;
    
    currentNode = rebalanceTree(key, currentNode, currentNode->parent_); //call rebalanceTree function on currentNode and its parent to perform rotations, if necessary
    
    size_++;
}

size_t AVL::size() const { //AVL version of BST class function
    return size_;
}

bool AVL::empty() const { //AVL version of BST class function
    return size_ == 0;
}

std::string AVL::JSON() { //AVL version of BST class function
    nlohmann::json result;
    std::queue< std::shared_ptr<BSTNode> > nodes;
    if (root_ != nullptr) {
        result["root"] = root_->key_;
        nodes.push(root_);
        while (!nodes.empty()) {
            auto v = nodes.front();
            nodes.pop();
            std::string key = std::to_string(v->key_);
            if (v->left_ != nullptr) {
                result[key]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key]["right"] = v->right_->key_;
                nodes.push(v->right_);
            }
            if (v->parent_.lock() != nullptr) {
                result[key]["parent"] = v->parent_.lock()->key_;
            } else {
                result[key]["root"] = true;
            }
            int node_height = getHeight(v); //call getHeight function to get height of node
            result[key]["height"] = node_height; //print height of node
            int node_bf = getBalanceFactor(v); //call getBalanceFactor function to get balance factor of node
            result[key]["balance factor"] = node_bf; //print balance factor of node
        }
    }
    result["height"] = std::max(getHeight(root_->left_), getHeight(root_->right_)) + 1; //call getHeight function to get height of root (the max of either its children)
    result["size"] = size_;
    return result.dump(2) + "\n";
}

int AVL::getHeight(std::shared_ptr<BSTNode> currentNode) //to get height of node
{
    if (currentNode == nullptr || (currentNode->left_ == nullptr && currentNode->right_ == nullptr)) //if itself or its children are nullptr, return height of 0
    {
        return 0;
    }
    return std::max(getHeight(currentNode->left_), getHeight(currentNode->right_)) + 1; //otherwise, return height of max of either its children
}

int AVL::getBalanceFactor(std::shared_ptr<BSTNode> currentNode) //to get balance factor of node
{
    if (currentNode == nullptr || (currentNode->left_ == nullptr && currentNode->right_ == nullptr)) //if itself or its children are nullptr, return balance factor of 0
    {
        return 0; //left child & right child heights = -1, so balance factor = -1 - (-1) = 0
    }
    if (currentNode->left_ == nullptr && currentNode->right_ != nullptr) //if only left child is null
    {
        return getHeight(currentNode->right_) + 1; //left child height = -1, so balance factor = height(right) - (-1)
    }
    if (currentNode->right_ == nullptr && currentNode->left_ != nullptr) //if only right child is null
    {
        return (- 1) - (getHeight(currentNode->left_)); //right child height = -1, so balance factor = -1 - height(left)
    }
    else //otherwise, if both children are not null
    {
        return (getHeight(currentNode->right_)) - (getHeight(currentNode->left_)); //balance factor = height(right) - height(left)
    }
}

std::shared_ptr<BSTNode> AVL::rebalanceTree(int key, std::shared_ptr<BSTNode> currentNode, std::weak_ptr<BSTNode> parentNode) //for rotations
{
    if (currentNode == nullptr) //if node is null
    {
        currentNode = std::make_shared<BSTNode>(key, parentNode); //create BSTNode w/ key and its parent
        return std::shared_ptr<BSTNode>(currentNode); //return a no longer nullptr node
    }
    if (key < currentNode->key_) //go down on left side of tree
    {
        currentNode->left_ = rebalanceTree(key, currentNode->left_, currentNode); //recursive call to perform rotations if necessary
    }
    if (key > currentNode->key_) //go down on right side of tree
    {
        currentNode->right_ = rebalanceTree(key, currentNode->right_, currentNode); //recursive call to perform rotations if necessary
    }
    
    int balance_factor = getBalanceFactor(currentNode); //initialize and get balance factor
    
    //4 rebalancing cases:
    
    if (currentNode->left_ != nullptr && key < currentNode->left_->key_ && balance_factor < -1) //if left heavy (with the left child being "left-heavier" than current node)
    {
        return rotateRight(currentNode); //call rotateRight function to rebalance left-heaviness
    }
    
    if (currentNode->right_ != nullptr && key > currentNode->right_->key_ && balance_factor > 1) //if right heavy (with the right child being "right-heavier" than current node)
    {
        return rotateLeft(currentNode); //call rotateLeft function to rebalance right-heaviness
    }
        
    if (currentNode->left_ != nullptr && key > currentNode->left_->key_ && balance_factor < -1) //if current node is left heavy (with the left child being "right-heavier" than current node)
    {
        currentNode->left_ = rotateLeft(currentNode->left_); //call rotateLeft function on left child to rebalance right-heaviness
        return rotateRight(currentNode); //then call rotateRight function on current node to rebalance left-heaviness
        //return rotateRightLeft(currentNode);
    }

    if (currentNode->right_ != nullptr && key < currentNode->right_->key_ && balance_factor > 1) //if current node is right heavy (with the right child being "left-heavier" than current node)
    {
        currentNode->right_ = rotateRight(currentNode->right_); //call rotateRight function on right child to rebalance left-heaviness
        return rotateLeft(currentNode); //then call rotateLeft function on current node to rebalance right-heaviness
        //return rotateLeftRight(currentNode);
    }
    return currentNode;
}

std::shared_ptr<BSTNode> AVL::rotateRight(std::shared_ptr<BSTNode> unbalancedNode) //to rebalance left-heaviness (BF < -1)
{
    //assign ptrs for nodes participating in rotation
    std::shared_ptr<BSTNode> grandparent = unbalancedNode; //grandparent is the left heavy node
    std::weak_ptr<BSTNode> parent_p = unbalancedNode->parent_; //temp save grandparent's original parent node (will be parent's new parent node)
    std::shared_ptr<BSTNode> parent = grandparent->left_; //parent is grandparent's left child node

    //perform right-right rotation
    grandparent->left_ = parent->right_; //right child of parent becomes left child of grandparent node
    parent->right_ = grandparent; //grandparent becomes right child of parent
    
    if (parent_p.lock() == nullptr) //if grandparent's parent is null
    {
        root_ = parent; //parent becomes root
    }
    
    grandparent->parent_ = parent; //new parent of grandparent
    parent->parent_ = parent_p; //new parent of parent
    unbalancedNode = parent; //parent is now potential unbalancedNode

    //update new heights after rotation using max of either its children
    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    
    return unbalancedNode; //return parent
}

std::shared_ptr<BSTNode> AVL::rotateLeft(std::shared_ptr<BSTNode> unbalancedNode) //to rebalance right-heaviness (BF > 1)
{
    
    //assign ptrs for nodes participating in rotation
    std::shared_ptr<BSTNode> grandparent = unbalancedNode; //grandparent is the right heavy node
    std::weak_ptr<BSTNode> parent_p = unbalancedNode->parent_; //temp save grandparent's original parent node (will be parent's new parent node)
    std::shared_ptr<BSTNode> parent = unbalancedNode->right_; //parent is grandparent's right child node
    
    //perform left-left rotation
    if (parent->left_ != nullptr) //if parent's left child exists
    {
        std::shared_ptr<BSTNode> parent_rc = parent->left_; //assign parent's left child to new node parent_rightchild
        parent->left_->parent_ = grandparent; //grandparent is new parent of parent's left child
        parent->left_ = grandparent; //grandparent is parent's new left child
        grandparent->right_ = parent_rc; //parent's right child is grandparent's new right child
    }
    
    if (parent->left_ == nullptr) //if parent's left child is null
    {
        parent->left_ = grandparent; //grandparent is parent's new left child
        grandparent->right_ = nullptr; //grandparent's right child is null
    }
    
    if (parent_p.lock() == nullptr) //if grandparent's parent is null
    {
        root_ = parent; //parent becomes root
    }
    
    grandparent->parent_ = parent; //new parent of grandparent
    parent->parent_ = parent_p; //new parent of parent
    unbalancedNode = parent; //parent is now potential unbalancedNode
    
    //update new heights after rotation using max of either its children
    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    
    return unbalancedNode; //return parent
}

std::shared_ptr<BSTNode> AVL::rotateLeftRight(std::shared_ptr<BSTNode> unbalancedNode) //to rebalance right-left-heaviness
{
    //if unbalancedNode is right heavy and right child is left heavy
    std::shared_ptr<BSTNode> grandparent = unbalancedNode; //grandparent is the right heavy node
    std::weak_ptr<BSTNode> parent_p = unbalancedNode->parent_; //temp save grandparent's original parent node (will be parent's new parent node)
    std::shared_ptr<BSTNode> parent = grandparent->right_; //parent is grandparent's right child node
    std::shared_ptr<BSTNode> parent_child = parent->left_; //parent's left child

    //perform left-right rotation
    if (parent_child->left_ == nullptr) //if parent's left child is null
    {
        grandparent->right_ = nullptr; //grandparent's right child is null
    }
    
    grandparent->right_ = parent_child->left_; //original parent's left child's original left child is grandparent's new right child
    parent->left_ = parent_child->right_; //original parent's left child's original right child is parent's new left child
    parent_child->right_ = parent; //new right child of original parent's left child
    parent_child->left_ = grandparent; //new left child of original parent's left child
    grandparent->parent_ = parent; //new parent of grandparent
    parent->parent_ = parent_p; //new parent of parent
    
    //update new heights after rotation using max of either its children
    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    parent_child->height_ = std::max(getHeight(parent_child->left_), getHeight(parent_child->right_)) + 1;
    
    return parent_child; //return "root" node of rotation
}

std::shared_ptr<BSTNode> AVL::rotateRightLeft(std::shared_ptr<BSTNode> unbalancedNode) //to rebalance left-right-heaviness
{
    //if unbalancedNode is left heavy and left child is right heavy
    std::shared_ptr<BSTNode> grandparent = unbalancedNode; //grandparent is the left heavy node
    std::weak_ptr<BSTNode> parent_child_p = unbalancedNode->parent_; //temp save grandparent's original parent node (will be original parent's right child's new parent node)
    std::shared_ptr<BSTNode> parent = grandparent->left_; //parent is grandparent's left child node
    std::shared_ptr<BSTNode> parent_child = parent->right_; //parent's right child
    
    //perform right-left rotation
    if (parent_child->right_ == nullptr) //if parent's right child is null
    {
        grandparent->left_ = nullptr; //grandparent's left child is null
    }
    
    grandparent->left_ = parent_child->right_; //original parent's right child's original right child is grandparent's new left child
    parent->right_ = parent_child->left_; //original parent's right child's original right child is parent's new right child
    parent_child->left_ = parent; //parent is original parent's right child's new left child
    parent_child->right_ = grandparent; //grandparent is original parent's right child's new right child
    grandparent->parent_ = parent_child; //new parent of grandparent
    parent->parent_ = parent_child; //new parent of parent
    parent_child->parent_ = parent_child_p; //new parent of original parent's right child
    
    //update new heights after rotation using max of either its children
    grandparent->height_ = std::max(getHeight(grandparent->left_), getHeight(grandparent->right_)) + 1;
    parent->height_ = std::max(getHeight(parent->left_), getHeight(parent->right_)) + 1;
    parent_child->height_ = std::max(getHeight(parent_child->left_), getHeight(parent_child->right_)) + 1;
    
    return parent_child; //return "root" node of rotation
}
