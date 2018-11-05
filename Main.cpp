#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
#include "Ingredient.h"
#include "Food.h"
#include "HashTable.h"

void inOrderTravel(TreeNode<Food>* curTreeNodePtr);
void compareProtien2Fat(TreeNode<Food>*, double, double);

int main() {
	int choice = -1;

	BST<Food> foodTree; //makes tree of food items
	HashMap<Food> foodHash; //makes hashtable of food items
	char sentinel = ' ';
	std::string tFoodName, tIngredientName, tServes;
	double tProtein, tCarbs, tFat;
	std::fstream foodFile;
	int count = 0;
	foodFile.open("FoodItems.txt"); //opens file
	while (sentinel != '$') {  //$ signifies end of file
		if (count != 0) // makes sure its not the first run of inserting into tree
		{
			foodFile.ignore();
		}
		std::getline(foodFile, tFoodName);
		foodFile >> tServes;
		foodFile >> sentinel;
		std::cout << count << std::endl; //test

		Food tempFoodItem = Food(tFoodName, tServes); //makes a food object to put in hash table and BST
		while (sentinel == '-')  //reads through all ingredients until it hits the end of a food signified by @ in file
		{
			foodFile.ignore();
			std::getline(foodFile, tIngredientName);
			foodFile >> tProtein;
			foodFile >> tCarbs;
			foodFile >> tFat;
			foodFile >> sentinel;
			tempFoodItem.addNewIngredient(tIngredientName, tProtein, tCarbs, tFat);
		}
		foodTree.insert(tempFoodItem, &foodTree.topPtr);  //puts food item in tree
		foodHash.place(tempFoodItem.m_title, tempFoodItem); //puts food item in hash table
		count++;

	}
	foodFile.close();

	while (choice != 9)
	{
		std::cout << "What would you like to do?" << std::endl <<
			"(1). Add new food\n" <<
			"(2). Delete a food\n" <<
			"(3). Find 1 Food using the primary key\n" <<
			"(4). List food in hash table sequence\n" <<
			"(5). List food in sorted key sequence\n" <<
			"(6). Print indented tree\n" <<
			"(7). Efficiency of finding an item\n" <<
			"(8). Team choice menu option?\n" <<
			"(9). Quit" << std::endl;
		std::cin >> choice;
		std::cin.clear(); std::cin.ignore();
		if (choice == 9) {
			break;
		}
		else if (choice == 8) {
			for (;;) {
				double proCent, fatCent;
				char yn;
				std::cout << "\nSearch Foods based on the protein to fat ratios?\nEnter ratios in order of protien then fat.\nPress 'enter' after each entry." << std::endl;
				std::cin >> proCent; std::cin.clear(); std::cin.ignore();
				std::cin >> fatCent; std::cin.clear(); std::cin.ignore();
				std::cout << "You entered " << proCent << ":" << fatCent << " is this correct? y/n" << std::endl;
				std::cin >> yn; std::cin.clear(); std::cin.ignore();
				if (yn == 'n') {
					continue;
				}
				compareProtien2Fat(foodTree.topPtr, proCent, fatCent);
				//std::cout << "\nSimilar Results:\n";
				/*for (int i = 1; i < 5; i++) {
					if (proCent != 0) {
						compareProtien2Fat(foodTree.topPtr, proCent - i, fatCent);
					}
					compareProtien2Fat(foodTree.topPtr, proCent + i, fatCent);
					if (fatCent != 0) {
						compareProtien2Fat(foodTree.topPtr, proCent, fatCent - i);
					}
					compareProtien2Fat(foodTree.topPtr, proCent, fatCent + i);
				}*/
				break;
			}
		}
		else if (choice == 7) {
			//(7). Find 1 Food using the primary key
			std::string input;
			std::cout << "Name a dish to test for/against: ";
			getline(std::cin, input);
			int efficiency;
			Food temp;
			efficiency = foodHash.getWithEfficiency(input, temp);
			if (efficiency > 0) {
				std::cout << "Found " << temp.m_title << " in the hash in " << efficiency << " operations.\nThere were " << (efficiency - temp.m_title.length()*4)-1 << " collisions, and the load factor currently is " << (double)foodHash.getLoad() / (double)TABLE_SIZE << "." << std::endl;
			}
			else {
				std::cout << "Determined that " << temp.m_title << " does not exist in the hash in " << -efficiency << " operations." << std::endl;
			}

			//int BST<Type>::searchWithEfficiency(TreeNode<Type> * root, Type item, int temp = 0)
			efficiency = foodTree.searchWithEfficiency(foodTree.topPtr, input, 0);
			if (efficiency > 0) {
				std::cout << "Found " << temp.m_title << " in the Tree in " << efficiency << " operations." << std::endl;
			}
			else {
				std::cout << "Determined that " << temp.m_title << " does not exist in the tree in " << -efficiency << " operations." << std::endl;
			}
		}
		else if (choice == 6) {
			int spaces = 0;
			foodTree.dispInOrder(foodTree.topPtr, spaces);
		}
		else if (choice == 5) {
			inOrderTravel(foodTree.topPtr); //prints out the food items in alphabetical order
		}
		else if (choice == 4) {
			//(4). List food in hash table sequence
			foodHash.PrintFoodHash();
			//my thought process basically was "lol how do i even", so I elected to be lazy.
		}
		else if (choice == 3) {
			//(3). Find 1 Food using the primary key
			std::string input;
			std::cout << "What is the name of the dish you want to find? ";
			getline(std::cin, input);
			bool tralse;
			Food temp;
			tralse = foodHash.get(input, temp);
			if (tralse) {
				//item found
				std::cout << "Found: " << temp.m_title << std::endl;
				std::cout << "Serves: " << temp.m_serves << ", has, in it:" << std::endl;
				Ingredient* prtIngInfo = temp.topIngredient;
				double t_pro = 0, t_carb = 0, t_fat = 0;
				while (prtIngInfo != nullptr) {
					std::cout << prtIngInfo->getName() << ", with " << prtIngInfo->getPro() << "g protein, " <<
						prtIngInfo->getCarb() << "g carbohydrates, " << prtIngInfo->getFat() << "g fat." << std::endl;
					t_pro += prtIngInfo->getPro(); t_carb += prtIngInfo->getCarb(); t_fat += prtIngInfo->getFat();
					prtIngInfo = prtIngInfo->getNext();
				}
				std::cout << "In total, this food has " << t_pro << "g protein, " << t_carb << "g carbohydrates, and " << t_fat << "g fat." << std::endl;
				/* Ingredient* topIngredient;
				std::string m_title;
				std::string m_serves;
				double calories;
				Food(std::string);
				Food(std::string, std::string); */
			}
			else {
				//not found
				std::cout << "Failed to acquire food item named " << temp.m_title << "." << std::endl;
			}
		}
		else if (choice == 2) { //delets a food item from the food BST and the food Hashtable
			std::string delName;

			std::cout << "Please enter the name of the Food you would like to delete: " << std::endl;
			std::getline(std::cin, delName);
			TreeNode<Food>* tempTreeNodePoint = foodTree.topPtr;
			int  treeFind = foodTree.deleting(tempTreeNodePoint, delName);
			bool hashFind = foodHash.remove(delName);
			if (treeFind = TARGET_UNFOUND) {
				std::cout << delName << " was not found in the tree. ";
			}
			else {
				std::cout << delName << " has been deleted from the tree. ";
			}

			if (hashFind) {
				std::cout << "It has also been deleted from the hash." << std::endl;
			}
			else {
				std::cout << "It was not found in the hash." << std::endl;
			}

		}
		else if (choice == 1) {
			std::string title, serves;
			int numOfIng;
			std::cout << "add new food" << std::endl << "Title: ";
			getline(std::cin, title);
			std::cout << "Serves: ";
			getline(std::cin, serves);
			Food* newFood = new Food(title, serves);
			std::cout << "How many ingredients?";
			std::cin >> numOfIng;
			std::cin.clear(); std::cin.ignore();
			while (numOfIng > 0) {
				std::string name;
				double pro, carb, fat;
				std::cout << "add ingredient" << std::endl << "Name: ";
				getline(std::cin, name);
				std::cout << "Protein: ";
				std::cin >> pro;
				std::cin.clear(); std::cin.ignore();
				std::cout << "Carbohydrates: ";
				std::cin >> carb;
				std::cin.clear(); std::cin.ignore();
				std::cout << "Fat: ";
				std::cin >> fat;
				std::cin.clear(); std::cin.ignore();
				newFood->addNewIngredient(name, pro, carb, fat);
				numOfIng--;
			}
			foodTree.insert(*newFood, &foodTree.topPtr);
			foodHash.place(title, *newFood);
		}
		else {
			std::cout << "not valid choice." << std::endl;
			continue;
		}
	}

	std::ofstream outFile;
	outFile.open("FoodItems.txt");
	TreeNode<Food>* tempTreeNodePtr = foodTree.topPtr;
	foodTree.treeToFile(tempTreeNodePtr, outFile); //writes all the information into a file
	outFile.seekp(-3, std::ios_base::end);
	outFile.write("$\n", 3); // places a $ character that signifies end of file
	outFile.close();
}

void compareProtien2Fat(TreeNode<Food>* curTreeNodePtr, double pro, double fat) {
	if (curTreeNodePtr == nullptr) {
		return;
	}
	else {
		compareProtien2Fat(curTreeNodePtr->getLeft(), pro, fat);
		if (curTreeNodePtr->dataItem.compareProFat(pro, fat)) {
			std::cout << (curTreeNodePtr->dataItem).m_title
				<< "\n   Calories: " << (curTreeNodePtr->dataItem).calories
				<< "\n   Protien: " << (curTreeNodePtr->dataItem).getPro()
				<< "\n   Carbohydrates: " << (curTreeNodePtr->dataItem).getCarb()
				<< "\n   Fat: " << (curTreeNodePtr->dataItem).getFat();
		}
		compareProtien2Fat(curTreeNodePtr->getRight(), pro, fat);
		return;
	}
}


void inOrderTravel(TreeNode<Food>* curTreeNodePtr) { //prints data inorder
	if (curTreeNodePtr == nullptr) {
		return;
	}
	else {
		inOrderTravel(curTreeNodePtr->getLeft());

		std::cout << "Title: " << (curTreeNodePtr->dataItem).m_title << std::endl;
		std::cout << "Serves: "  << (curTreeNodePtr->dataItem).m_serves << std::endl;
		std::cout << "Calories: " << (curTreeNodePtr->dataItem).calories << std::endl << std::endl;


		inOrderTravel(curTreeNodePtr->getRight());
		return;
	}
}
