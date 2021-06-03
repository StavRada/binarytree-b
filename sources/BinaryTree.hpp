#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

namespace ariel {
template<typename T> class BinaryTree {

class Node {
public:
        T val;
        Node* l;
        Node* r;
        Node(T k) : val(k), r(nullptr), l(nullptr){
        }
};

class iterator {
void add_preorder(Node* node){
        if(node==nullptr) { return; }
        fill_vec.push_back(node);
        add_preorder(node->l);
        add_preorder(node->r);
}

void add_inorder(Node* node){
        if(node==nullptr) { return; }
        add_inorder(node->l);
        fill_vec.push_back(node);
        add_inorder(node->r);
}

void add_postorder(Node* node){
        if(node==nullptr) { return; }
        add_postorder(node->l);
        add_postorder(node->r);
        fill_vec.push_back(node);
}

std::vector<Node*> fill_vec;
Node * cur;

public:

iterator() : cur(nullptr){}
iterator(Node* n) : cur(n){}
iterator(const std::string& type, Node* n) {
        if(n!=nullptr){
          if(type == "inorder") {
                  add_inorder(n);
          }else if(type == "postorder") {
                  add_postorder(n);
          }else if(type == "preorder") {
                  add_preorder(n);
          }
            cur = fill_vec[0];
      }else{
        cur=nullptr;
      }
}
iterator& operator++() {
        if(fill_vec.size()>1) {
                fill_vec.erase(fill_vec.begin());
                cur=fill_vec[0];
        } else{
                cur = nullptr;
        }
        return *this;
}
iterator operator++(int) {
        iterator tmp (fill_vec[0]);
        ++*this;
        return tmp;
}
T& operator*() const {
        return cur->val;
}
T* operator->() const {
        return &(cur->val);
}
bool operator==(iterator const &o) const {
        return cur == o.cur;
}
bool operator!=(iterator const &o) const {
        return !(*this == o);
}
};

Node* search(Node * n, T val_){
        if(n == nullptr ) {return nullptr;}

        if(n->val == val_) {return n;}
        Node * result =   search(n->l, val_);
        if(result!= nullptr) {return result;}
        return search(n->r, val_);
}

static void print(Node * n){
        if(n != nullptr ) {
                std::cout << n->val << " ";
                print(n->l);
                print(n->r);
        }
}

void copy_tree(const Node& from_tree, Node& to_other_tree){
        if(from_tree.l!=nullptr) {
                to_other_tree.l = new Node(from_tree.l->val);
                copy_tree(*from_tree.l,*to_other_tree.l);
        }
        if(from_tree.r!=nullptr) {
                to_other_tree.r = new Node(from_tree.r->val);
                copy_tree(*from_tree.r,*to_other_tree.r);
        }
}

//member
Node* root;

public:
BinaryTree() : root(nullptr) {}

//deep
BinaryTree(const BinaryTree<T> & other){
        if(other.root!=nullptr) {
                root = new Node(other.root->val);
                copy_tree(*other.root,*root);
        }
}

BinaryTree& operator=(BinaryTree other){
        if(this == &other) {
                return *this;
        }
        if(root != nullptr) {
                delete this->root;
        }
        root = new Node(other.root->val);
        copy_tree(*other.root,*this->root);
        return *this;
}

//Shallow
BinaryTree(BinaryTree<T> && other) noexcept {
        root = other.root;
        other.root = nullptr;
}

BinaryTree& operator=(BinaryTree&& other) noexcept{
        *this->root = other.root;
        return *this;
}

~BinaryTree() = default;

BinaryTree& add_root(T k);
BinaryTree& add_right(T parent, T child);
BinaryTree& add_left(T parent, T child);

iterator begin_inorder(){
        return iterator("inorder",this->root);
}
iterator end_inorder(){
        return iterator();
}
iterator begin_preorder(){
        return iterator("preorder",this->root);
}
iterator end_preorder(){
        return iterator();
}
iterator begin_postorder(){
        return iterator("postorder",this->root);
}
iterator end_postorder(){
        return iterator();
}
iterator begin(){
        return iterator("inorder",this->root);
}
iterator end(){
        return iterator();
}
friend std::ostream& operator<<(std::ostream& os,const BinaryTree<T>& binaryTree){
        print(binaryTree.root);
        return os;
}

};// close class bt

template<typename T> BinaryTree<T>& BinaryTree<T>::add_root(T k){
        if(root == nullptr) {
                root = new Node(k);
        }else{
                root->val = k;
        }

        return *this;
}

template<typename T> BinaryTree<T>& BinaryTree<T>::add_left(T parent, T child){

        Node * find = search(this->root, parent);
        if(find==nullptr) { throw std::invalid_argument{"parent isn't exist"};}

        if(find->l ==nullptr) {
                find->l  =  new Node(child);

        }else{
                find->l->val = child;
        }
        return *this;
}

template<typename T> BinaryTree<T>& BinaryTree<T>::add_right(T parent, T child){
        Node * find = search(this->root, parent);
        if(find==nullptr) { throw std::invalid_argument{"parent isn't exist"};}

        if(find->r ==nullptr) {
                find->r  =  new Node(child);

        }else{
                find->r->val = child;
        }
        return *this;
}

} // close name space
