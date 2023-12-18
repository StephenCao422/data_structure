#pragma once

#include "tree.h"

template <class T>
Tree<T>::Iterator::Iterator(Tree::Node *root) : curr_(root) {
	// TODO: your code here
    while(curr_&&curr_->right_){
        s_.push(curr_);
        curr_=curr_->right_;
    }
    if(curr_&&!curr_->data_)
        ++(*this);

}

template <class T>
typename Tree<T>::Iterator & Tree<T>::Iterator::operator++() {
	// TODO: your code here
	//return *this;
    do{
        if(s_.empty()){
            curr_=NULL;
            return *this;
        }
        curr_=s_.top();
        s_.pop();
        Tree::Node* c=curr_;
        if(c->left_){
            c=c->left_;
            while(c){
                s_.push(c);
                c=c->right_;
            }
    }
    }while(!curr_->data_);
    return *this;

}

template <class T>
T Tree<T>::Iterator::operator*() const {
	// TODO: your code here
    if(!curr_)
        return T();
    return curr_->data_; // remove this line
}



/*******************
 ** PROVIDED CODE **
 *******************/
template <class T>
bool Tree<T>::Iterator::operator!=(const Tree<T>::Iterator &other) {
	return !(curr_ == other.curr_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::begin() {
	return Iterator(root_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::end() {
	return Iterator(NULL);
}
