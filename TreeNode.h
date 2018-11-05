#pragma once
#include <iostream>
#include <string>

template<class Type>
class TreeNode
{
public:
	Type dataItem;
	TreeNode<Type>* leftChild;
	TreeNode<Type>* rightChild;
	TreeNode(); //default constructor
	TreeNode(const Type& anItem); //Contructor takes type and item but no next pointer 
	void setItem(const Type& anItem); // sets data
	void setRightChild(TreeNode<Type>* nextTreeNodePtr); // sets right child TreeNode
	void setLeftChild(TreeNode<Type>* nextTreeNodePtr); //sets left child TreeNode
	Type getItem() const; //gets dataItem
	TreeNode<Type>* getLeft() const; //returns left child
	TreeNode<Type>* getRight() const; //returns right child
	~TreeNode(); //destructor
};

template<class Type>
TreeNode < Type> ::TreeNode() : leftChild(nullptr), rightChild(nullptr)
{
}

template<class Type>
TreeNode <Type> ::TreeNode(const Type& anItem) : dataItem(anItem), leftChild(nullptr), rightChild(nullptr)
{
}

template<class Type>
void TreeNode<Type> ::setItem(const Type& anItem)
{
	dataItem = anItem;
}

template<class Type>
void TreeNode<Type> ::setRightChild(TreeNode<Type>* nextTreeNodePtr)
{
	rightChild = nextTreeNodePtr;
}

template<class Type>
void TreeNode<Type> ::setLeftChild(TreeNode<Type>* nextTreeNodePtr)
{
	leftChild = nextTreeNodePtr;
}

template<class Type>
Type TreeNode<Type> ::getItem() const
{
	return dataItem;
}

template<class Type>
TreeNode<Type>* TreeNode<Type> ::getLeft() const
{
	return leftChild;
}

template<class Type>
TreeNode<Type>* TreeNode<Type> ::getRight() const
{
	return rightChild;
}

template<class Type>
TreeNode <Type> :: ~TreeNode()
{
}


