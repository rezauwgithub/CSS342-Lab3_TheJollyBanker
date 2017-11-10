#pragma once
/*
This Binary Tree implementation is meant to be as generic as possible, which
is why I templated it.  It also includes an Exists() function which
determines if a comparable item already exists within its structure.  The
Insert() function is set to not allow duplicate items in the tree.

Limitations:
-- Display outputs tree objects to the console.  For this function to work,
items stored in the tree must have defined output.
-- This is not a full class.  No copy constructor or assignment operators
exist, so in some cases the program may crash where deep copies are needed.
*/

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <class T>
class BSTree
{
	private:
		struct Node
		{
			T* data;
			Node* right;
			Node* left;
		};

		Node* root;

		bool insertAssistant(Node* currentNode, Node* newNode);
		bool retrieveAssistant(const Node* currentNode, const T &target, T* &result) const;
		void displayAssistant(const Node* currentNode) const;
		void emptyAssistant(Node* node);


	public:
		BSTree();
		~BSTree();

		bool Insert(T* obj);

		// retrieve object, first parameter is the ID of the account
		// second parameter holds pointer to found object, nullptr if not found
		bool Retrieve(const T &target, T* &result) const;

		// displays the contents of a tree to cout
		void Display() const;
		bool Exists(const T &target) const;
		void Empty();
		bool isEmpty() const;
};

template <class T>
bool BSTree<T>::insertAssistant(Node* currentNode, Node* newNode)
{
	if (*currentNode->data == *newNode->data)
	{
		return false; // No duplicates allowed!
	}

	if (*currentNode->data < *newNode->data)
	{
		if (currentNode->right != nullptr)
		{
			insertAssistant(currentNode->right, newNode);
		}
		else
		{
			currentNode->right = newNode;
		}
	}
	else
	{
		if (currentNode->left != nullptr)
		{
			insertAssistant(currentNode->left, newNode);
		}
		else
		{
			currentNode->left = newNode;
		}
	}

	return true;    // Successfully added node to Tree
}

template <class T>
bool BSTree<T>::retrieveAssistant(const Node* currentNode, const T &target, T* &result) const
{
	if (currentNode != nullptr)
	{
		if (*currentNode->data == target)
		{
			result = currentNode->data;
			return true;
		}
		else if (*currentNode->data > target)
		{
			return retrieveAssistant(currentNode->left, target, result);
		}
		else
		{
			return retrieveAssistant(currentNode->right, target, result);
		}

	}

	result = nullptr;
	return false;
}

template <class T>
void BSTree<T>::displayAssistant(const Node* currentNode) const
{
	if (currentNode != NULL)
	{
		displayAssistant(currentNode->left);
		std::cout << *currentNode->data;
		displayAssistant(currentNode->right);
	}

}

template <class T>
void BSTree<T>::emptyAssistant(Node* node)
{
	if (node == nullptr)
	{
		return; // base case, tree is empty
	}

	emptyAssistant(node->left);
	emptyAssistant(node->right);

	delete node->data;
	node->data = nullptr;
	node->left = nullptr;
	node->right = nullptr;

	delete node;
	node = nullptr;
}

template <class T>
void BSTree<T>::Empty()
{
	emptyAssistant(root);
}


template <class T>
BSTree<T>::BSTree()
{
	root = nullptr;
}

template <class T>
BSTree<T>::~BSTree()
{
	Empty();
}

template <class T>
bool BSTree<T>::Insert(T* obj)
{
	if (obj == nullptr)
	{
		return false;
	}

	Node* newNode = new Node();
	newNode->data = obj;

	if (isEmpty())
	{
		root = newNode;

		return true;
	}

	Node* currentNode = root;

	return insertAssistant(currentNode, newNode);
}

template <class T>
bool BSTree<T>::Retrieve(const T &target, T* &result) const
{
	if (&target == nullptr)
	{
		return false;
	}

	return retrieveAssistant(root, target, result);
}

template <class T>
void BSTree<T>::Display() const
{
	displayAssistant(root);
}

template <class T>
bool BSTree<T>::Exists(const T &target) const
{
	if (&target == nullptr)
	{
		return false;
	}

	T* result;

	return retrieveAssistant(root, target, result);
}

template <class T>
bool BSTree<T>::isEmpty() const
{
	return (root == nullptr);
}


#endif // BSTREE_H
