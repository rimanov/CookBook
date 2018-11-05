#pragma once
#include <iostream>
#include "TreeNode.h"


const int DELETE_SUCCESS = 0;
const int TARGET_UNFOUND = 1;
const int NO_CHILD = 2;
const int ONLY_LEFT_CHILD = 3;
const int ONLY_RIGHT_CHILD = 4;
const int LEFT_RIGHT_CHILDREN = 5;

template<class Type>
class BST : public TreeNode<Type> {
public:
	TreeNode<Type>* topPtr; //= new TreeNode<Type>();
	int rightWeight, leftWeight;
	BST();
	BST(TreeNode<Type>*);
	void balanceTree();
	bool insert(Type, TreeNode<Type>**);
	int deleting(TreeNode<Type>*, Type);
	bool search(TreeNode<Type>*, Type);
	void treeToFile(TreeNode<Type>*, std::ofstream&);
	void dispInOrder(TreeNode<Type> *, int);
	//void deleteByName(TreeNode<Type>*, std::string);
	int searchWithEfficiency(TreeNode<Type>*, Type, int temp = 0);
};

template<class Type>
BST<Type>::BST() : topPtr(nullptr), rightWeight(0), leftWeight(0)
{ }

template<class Type>
BST<Type>::BST(TreeNode<Type>* newPtr) : topPtr(newPtr), rightWeight(0), leftWeight(0)
{ }

//Type A; Pointer to Pointer
template<class Type>
bool BST<Type>::insert(Type newItem, TreeNode<Type>** root) { // * * TreeNode
															  //special casing top / the first TreeNode is probably easier to grok
															  //if root is null, then insert new TreeNode at root
	if (*root == nullptr) { //NOT **root e.g. the TreeNode itself, but the thing that the pointer points at is "not a TreeNode" / otherwise not assigned
		TreeNode<Type>* newRoot = new TreeNode<Type>(newItem);
		*root = newRoot;
		return true;
	}

	//Moves to next child depending on whether greater than or less than root item
	if (newItem < (*root)->dataItem) {
		//indirect through root because root is pointer to pointer, not pointer to item
		//THEN we do -> so as to get the item that is cared about.
		if (insert(newItem, &((*root)->leftChild))) {
			leftWeight++;
		}
	}
	else {
		if (insert(newItem, &((*root)->rightChild))) {
			rightWeight++;
		}
	}
	balanceTree();

}

//Type B; reference to pointer
/*
template<class Type>
void BST<Type>::insert(Type newItem, TreeNode<Type>*& root) {
//special casing top / the first TreeNode is probably easier to grok
//if root is null, then insert new TreeNode at root
if (root == nullptr) { //NOT **root e.g. the TreeNode itself, but the thing that the pointer points at is "not a TreeNode" / otherwise not assigned
TreeNode<Type>* newRoot = new TreeNode(newItem);
root = newRoot;
return;
}

//Moves to next child depending on whether greater than or less than root item
if (newItem < root->dataItem) {
//indirect through root because root is pointer to pointer, not pointer to item
//THEN we do -> so as to get the item that is cared about.
insert(newItem, root->leftChild));
} else {
insert(newItem, root->rightChild));
}

}
*/

template<class Type>
void BST<Type>::balanceTree() {
	////if ((LHSitem-2) >= (RHSitem) && (LHSitem+2) <= (RHSitem)
	////then LHS-2 <= RHS <= LHS+2
	//TreeNode<Type>* temp;
	//if ((rightWeight - 2) <= leftWeight) { //left weighs at least more
	//	temp = topPtr;
	//	TreeNode<Type> * tempTreeNode;
	//	TreeNode<Type> * prevTreeNode = nullptr;
	//	if (temp->leftChild == nullptr) {
	//		tempTreeNode = temp->leftChild;
	//		while (tempTreeNode->rightChild != nullptr) {
	//			prevTreeNode = tempTreeNode;
	//			tempTreeNode = tempTreeNode->rightChild;
	//		}
	//		tempTreeNode->setLeftChild(topPtr->leftChild);
	//		tempTreeNode->setRightChild(topPtr->rightChild);
	//		prevTreeNode->setRightChild(nullptr);
	//		topPtr = tempTreeNode;
	//		insert(temp->dataItem, &topPtr);
	//	}
	//	else {
	//		temp->setLeftChild(topPtr);

	//	}
	//	//need to find largest child from left subtree
	//
	//}
	//else if ((rightWeight + 2) >= leftWeight) {//right weighs at least 2 more
	//	temp = topPtr;
	//	TreeNode<Type> * tempTreeNode;
	//	TreeNode<Type> * prevTreeNode = nullptr;
	//	if (temp->rightChild == nullptr) {
	//		tempTreeNode = temp->rightChild;
	//	}
	//	else {
	//		tempTreeNode = temp;
	//	}
	//	//need to find smallest child from right subtree
	//	while (tempTreeNode->leftChild != nullptr) {
	//		prevTreeNode = tempTreeNode;
	//		tempTreeNode = tempTreeNode->leftChild;
	//	}
	//	tempTreeNode->setLeftChild(topPtr->leftChild);
	//	tempTreeNode->setRightChild(topPtr->rightChild);
	//	prevTreeNode->setLeftChild(nullptr);
	//	topPtr = tempTreeNode;
	//	insert(temp->dataItem, &topPtr);
	//}
}

template <class Type>
int BST<Type>::deleting(TreeNode<Type> * root, Type deletion)
//int which returns varying values when it finds the TreeNode *to* delete,
//so that we have access to the parent of that child and know which TreeNode it is and which case set to use
{
	int TreeNodeFound;
	TreeNode<Type> *temp;
	if (root == nullptr) {
		//failed to find the item to delete
		//therefore we can't delete it
		TreeNodeFound = TARGET_UNFOUND;
	}

	else if (root->dataItem == deletion) //was root
	{
		if (root->leftChild == root->rightChild) {
			//*should* only be equal when nullptr
			//this TreeNode should be a leaf
			return NO_CHILD;
		}
		else if (root->leftChild == nullptr && root->rightChild != nullptr) {
			//this TreeNode is leaf-like, has only a right
			return ONLY_RIGHT_CHILD;
			//move the child to be the child of this child's parent and then delete this child
			//child gets pointed to by a tempPtr
			//delete that child's parent [this TreeNode]
			//make this TreeNode's parent point to tempPtr instead of this parent TreeNode
		}
		else if (root->rightChild == nullptr && root->leftChild != nullptr) {
			//this TreeNode is leaf-like, has only a left
			return ONLY_LEFT_CHILD;
			//move the child to be the child of this child's parent and then delete this child
		}
		else {
			return LEFT_RIGHT_CHILDREN;
			//this TreeNode has two children.
		}
	}

	//did not fail to find,
	//did not yet find it
	//so call down deeper into the tree
	bool wentRight;
	if (root != nullptr) {
		//failed to find the item to delete
		//therefore we can't delete it
		//TreeNodeFound = TARGET_UNFOUND;

		if (root->dataItem > deletion) {
			TreeNodeFound = deleting(root->leftChild, deletion);
			wentRight = false;
		}
		else {
			TreeNodeFound = deleting(root->rightChild, deletion);
			wentRight = true;
		}
	}

	//found or not?
	//temp declaration
	if (TreeNodeFound == DELETE_SUCCESS) {
		return DELETE_SUCCESS;
	}
	else if (TreeNodeFound == TARGET_UNFOUND) {
		return TARGET_UNFOUND;
	}
	else if (TreeNodeFound == NO_CHILD) {
		if (wentRight) {
			delete root->rightChild;
			root->setRightChild(nullptr);
			rightWeight--;
			return DELETE_SUCCESS;
		}
		else {
			delete root->leftChild;
			root->setLeftChild(nullptr);
			leftWeight--;
			return DELETE_SUCCESS;
		}
	}
	else if (TreeNodeFound == ONLY_LEFT_CHILD) {
		if (wentRight) {
			temp = root->rightChild;
			root->setRightChild(temp->leftChild);
			delete temp;
			rightWeight--;
			return DELETE_SUCCESS;
		}
		else {
			temp = root->leftChild;
			root->setLeftChild(temp->leftChild);
			delete temp;
			leftWeight--;
			return DELETE_SUCCESS;
		}

	}
	else if (TreeNodeFound == ONLY_RIGHT_CHILD) {
		if (wentRight) {
			temp = root->rightChild;
			root->setRightChild(temp->rightChild);
			delete temp;
			rightWeight--;
			return DELETE_SUCCESS;
		}
		else {
			temp = root->leftChild;
			root->setLeftChild(temp->rightChild);
			delete temp;
			leftWeight--;
			return DELETE_SUCCESS;
		}
	}
	else if (TreeNodeFound == LEFT_RIGHT_CHILDREN) {
		if (wentRight) {
			temp = root->rightChild;
			TreeNode<Type> * tempTreeNode;
			tempTreeNode = temp->leftChild;
			//need to find largest child from left subtree
			while (tempTreeNode->rightChild != nullptr) {
				tempTreeNode = tempTreeNode->rightChild;
			}
			root->setRightChild(tempTreeNode);
			//have it point to the left and right children of the deleted nodw
			delete temp;
			rightWeight--;
			return DELETE_SUCCESS;
		}
		else {
			temp = root->leftChild;
			TreeNode<Type> * tempTreeNode;
			tempTreeNode = temp->leftChild;
			//need to find largest child from left subtree
			while (tempTreeNode->rightChild != nullptr) {
				tempTreeNode = tempTreeNode->rightChild;
			}
			root->setLeftChild(tempTreeNode);
			//have it point to the left and right children of the deleted nodw
			delete temp;
			leftWeight--;
			return DELETE_SUCCESS;
		}
	}
	balanceTree();
}

template <class Type>
bool BST<Type>::search(TreeNode<Type> * root, Type item)
{
	if (root->dataItem == item) {
		return true;
	}

	if (root->dataItem < item)
	{
		search(root->getRight(), item);
	}
	else
	{
		search(root->getLeft(), item);
	}
}

template <class Type>
void BST<Type>::treeToFile(TreeNode<Type>* curTreeNodePtr, std::ofstream& outFile) { //goes through tree in inorder and puts it in file
	if (curTreeNodePtr == nullptr) {
		return;
	}
	else {
		treeToFile(curTreeNodePtr->getLeft(), outFile);
		Ingredient *traversalPtr = curTreeNodePtr->dataItem.topIngredient;
		outFile << (curTreeNodePtr->dataItem).m_title << "\n" << (curTreeNodePtr->dataItem).m_serves << "\n";//prints food name and how many it serves to file
		while (traversalPtr != nullptr) //goes through the linked list until it finds null pointer
		{
			outFile << "-" << "\n" << traversalPtr->getName()/*->m_name*/ << "\n" << traversalPtr->getPro() << " "
				<< traversalPtr->getCarb() << " " << traversalPtr->getFat() << "\n";
			traversalPtr = (traversalPtr->getNext());
			if (traversalPtr == nullptr)
			{
				outFile << "@" << "\n"; //signifies end of a food item
			}
		}
		treeToFile(curTreeNodePtr->getRight(), outFile);
		return;
	}
}

//template <class Type>
//void BST<Type>::deleteByName(TreeNode<Type>* nodePtr, std::string name)
//{
//	Food tempFood;
//	//double tempCal;
//	if (nodePtr != nullptr)
//	{
//		deleteByName(nodePtr->leftChild, name);
//		deleteByName(nodePtr->rightChild, name);
//		if (nodePtr->dataItem.m_title == name)
//		{
//			tempFood = nodePtr->dataItem;
//			//tempCal = nodePtr->dataItem.calories;
//			deleting(nodePtr, tempFood);
//		}
//
//	}
//}
template<class Type>
void BST<Type>::dispInOrder(TreeNode<Type> *root, int spaces)
{
	if (root == nullptr)
		return;

	int setSpaces = root->dataItem.m_title.length() + 1;
	spaces += setSpaces;
	dispInOrder(root->rightChild, spaces);

	std::cout << std::endl;
	for (int i = setSpaces; i < spaces; i++)
		std::cout << " ";
	std::cout << root->dataItem.m_title << std::endl;

	dispInOrder(root->leftChild, spaces);
}

template <class Type>
int BST<Type>::searchWithEfficiency(TreeNode<Type> * root, Type item, int efficiency = 0) {
	efficiency+=6;
	//we have to compare three times
	//we have to indirect through root three times

	if (root == nullptr) {
		return -efficiency;
	}
	else if (root->dataItem == item) {
		return efficiency;
	}

	if (root->dataItem < item) {
		return searchWithEfficiency(root->getRight(), item, efficiency);
	}
	else {
		return searchWithEfficiency(root->getLeft(), item, efficiency);
	}
}
