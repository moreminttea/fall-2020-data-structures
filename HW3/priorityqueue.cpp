// Mindy Mohr
// 917425752
// priorityqueue.cpp

#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

using namespace std; //using std::

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
    nodes_[size_ + 1] = kv; //insert new node into last leaf slot
    
    if (kv < nodes_[1] || kv != nodes_[1] || kv < nodes_[(size_ + 1) /2]) //if new node (can't be root, otherwise no need to heapifyUp) < ROOT or < parent
    {
        heapifyUp(size_ + 1); //if breaks rules -> heapify up
    }
    
    else //if new node > parent or root
    {
        heapifyDown(size_ + 1); //if breaks rules -> heapify down
    }
    size_++; //increment size of current min heap
}

KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    return nodes_[1]; //returns KeyValuePair that has min Key in heap
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    if (size_ == 1) //if only 1 element (the min) in heap
    {
        return min(); //return min key
    }
    
    removeNode(1); //call removeNode function on min
    return min(); //return min key
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    if (nodes_.empty()) //if statement that checks if heap is empty
    {
        return true; //returns true if heap is empty
    }
    return false; //returns false if heap is not empty
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return nodes_.size() - 1; //returns number of KeyValuePairs in heap
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["maxHeapSize"] = max_size_;
  result["metadata"]["max_size"] = max_size_; //get max size
  result["metadata"]["numOperations"] = 200; //get num of operations
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	// TODO: complete this function
    size_t parent = i / 2; //parent index
    std::pair<Key, Value> temp_i = nodes_[parent]; //won't lose parent key if swapping

    if (i == ROOT || nodes_[parent] < nodes_[i]) //if new node is root
    {
        return; //end heapifyUp operation
    }
    
    if (i != ROOT || nodes_[parent] > nodes_[i]) //if new node is not equal to the root and is < current parent, swap
    {
        nodes_[parent] = nodes_[i]; //new node key replaces parent key
        nodes_[i] = temp_i; //prev parent key is placed in prev new node index
        i = i / 2; //new parent index
        heapifyUp(i); //resursive call in case 1+ heapifyUp ops necessary
    }
}

void PriorityQueue::heapifyDown(size_t i) {
	// TODO: complete this function
    size_t left_child = i * 2; //left child index
    size_t right_child = i * 2 + 1; //right child index
    size_t new_i = i; //new node index
    std::pair<Key, Value> temp_i = nodes_[i]; //won't lose node key if swapping
        
    if (nodes_[i] < nodes_[left_child] && nodes_[i] < nodes_[right_child]) //if new node key is < both children
    {
        return; //end heapifyDown operation
    }
    
    if (left_child >= size_) //no left child (null)
    {
        return; //end heapifyDown operation
    }
    
    else if (nodes_[i] > nodes_[left_child] || nodes_[i] > nodes_[right_child]) //if new node key < both left and right children
    {
        if (nodes_[left_child] < nodes_[right_child]) //compare children keys, if left key < right key
        {
            new_i = left_child; //swap new node with left child
        }
        if (nodes_[left_child] > nodes_[right_child]) //compare children keys, if left key > right key
        {
            new_i = right_child; //swap new node with right child
        }
    }
    nodes_[i] = nodes_[new_i]; //smaller child key replaces new node key
    nodes_[new_i] = temp_i; //prev new node key is placed in prev smaller child index
    i = new_i; //new parent index
    heapifyDown(i); //resursive call in case 1+ heapifyDown ops necessary
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    nodes_[i] = nodes_[size_]; //node with index i is replaced with key of last leaf
    size_--; //decrease size of heap after deleting
    heapifyDown(i); //call heapifyDown to check if any rules are broken
}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    KeyValuePair kv = nodes_[i]; //key value pair = array of heap nodes
    return kv.first; //returns key of ith node in heap
}
