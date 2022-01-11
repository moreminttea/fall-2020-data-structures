// Mindy Mohr
// 917425752
// AVL.h

#include <memory>
#include <string>
#include "BST.h"

class AVL; //AVL version of BST class

class AVL {
 public:
    AVL();
    
    void Insert(int key);
    std::string JSON();
    size_t size() const;
    bool empty() const;
    int getHeight(std::shared_ptr<BSTNode> currentNode); //for getting height of node
    int getBalanceFactor(std::shared_ptr<BSTNode> currentNode); //for getting the balance factor of a node
    std::shared_ptr<BSTNode> rebalanceTree(int key, std::shared_ptr<BSTNode> currentNode, std::weak_ptr<BSTNode> parentNode); //for rebalancing inserted nodes
    std::shared_ptr<BSTNode> rotateRight(std::shared_ptr<BSTNode> unbalancedNode); //for rebalancing left-heavy nodes
    std::shared_ptr<BSTNode> rotateLeft(std::shared_ptr<BSTNode> unbalancedNode); //for rebalancing right-heavy nodes
    std::shared_ptr<BSTNode> rotateLeftRight(std::shared_ptr<BSTNode> unbalancedNode); //for rebalancing right-left-heavy nodes
    std::shared_ptr<BSTNode> rotateRightLeft(std::shared_ptr<BSTNode> unbalancedNode); //for rebalancing left-right-heavy nodes
    
 private:
 	std::shared_ptr<BSTNode> root_;
 	size_t size_;
}; // class AVL
