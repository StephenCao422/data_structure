#pragma once

#include <iterator>
#include <stack>
#include <queue>

template <class T>
class Tree {
	public:
		class Node {
			public:
				T data_;

				Node *left_;

				Node *right_;

				// Constructors
				Node(T data) : data_(data), left_(NULL), right_(NULL) {};
				Node(T data, Node *left, Node *right) : data_(data), left_(left), right_(right) {};
		};

		class Iterator : std::iterator<std::forward_iterator_tag, T> {
			private:
				Node *curr_;
				std::stack<Node*> s_;
			
			public:
				Iterator(Node *root);

				/**
				Progresses the iterator one step.
				**/
				Iterator & operator++();

				/**
				Accesses the data in the Iterator's current position.
				**/
				T operator*() const;

				/**
				Compares two iterators.
				**/
				bool operator!=(const Iterator &other);
		};

		/**
		Constructs an empty Tree.
		**/
		Tree() : root_(NULL) {};
		
		/**
		Destroys the Tree's associated dynamic memory as necessary.
		**/
		~Tree() {};

		/**
		Returns a begin iterator that can be used to traverse the non-NULL data values in this tree.
		**/
		Iterator begin();

		/**
		Returns an end iterator for this tree.
		**/
		Iterator end();


		Node *getRoot() { return root_; }
		void setRoot(Node *root) { root_ = root; }

	private:
		/**
		The root node of the Tree, or NULL if the Tree is empty.
		**/
		Node *root_;
};

//#include "tree.hpp"
