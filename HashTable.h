#pragma once
//Then we have a mapping to manage/insert these
//const int TABLE_SIZE = 7; [smaller table for other testing]
const int TABLE_SIZE = 47;
#include "HashSupport.h"
						   //#include "Food.h"

template<typename V>
class HashMap {
private:
	HashNode<V>** table; //table is a pointer.
						 //it points to a pointer table,
						 //and each index points at a hashnode.
	int loadFactor;
public:
	HashMap() {
		table = new HashNode<V>*[TABLE_SIZE](); //sets table size
		loadFactor = 0;
	}
	~HashMap();
	int  getLoad();
	bool get(std::string key, V &item);
	int  getWithEfficiency(std::string key, V &item);
	void place(std::string key, V &value);
	void PrintFoodHash();
	bool remove(std::string);
};

template<typename V>
int HashMap<V>::getLoad() {
	return loadFactor;
}

template<typename V>
void HashMap<V>::PrintFoodHash() {
	int count = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		HashNode<V>* current = table[i];
		while (current != nullptr) {
			std::cout << (current->getValue()).m_title << ", serves " << (current->getValue()).m_serves << std::endl;
			std::cout << "DEBUG:: " << convertKeyToHash((current->getValue()).m_title) << std::endl;
			//std::cout << (current->getValue()).m_title << std::endl;
			//std::cout << (current->getValue()).m_serves << std::endl;
			Ingredient* ingptr = (current->getValue()).topIngredient;

			count = (ingptr->getName()).length() + 1;
			std::cout << ingptr->getName();
			ingptr = ingptr->getNext();
			while (ingptr != nullptr) {
				std::cout << ",";
				if (count == 80) {
					count = 0;
				}
				count += (ingptr->getName()).length();
				if (count >= 79) {
					std::cout << std::endl;
					count = (ingptr->getName()).length();
				}
				else {
					std::cout << " ";
				}
				std::cout << ingptr->getName();
				//and now we append the comma and space.
				count += 2;
				//The commented lines print the total details about the ingredient.
				//std::cout << "\t" << ingptr->getName() << std::endl << "\t" << ingptr->getCarb() << "g Carbs, " << 
				//	ingptr->getFat() << "g Fat, " << ingptr->getPro() << "g Protein" << std::endl;
				ingptr = ingptr->getNext();
			} //while, ingptr
			std::cout << "." << std::endl << std::endl;
			current = current->getNext();
		} //while, current
	} // for, i
}

template<typename V>
bool HashMap<V>::get(std::string key, V &item) {
	int hashdex = convertKeyToHash(key);
	HashNode<V>* entry = table[hashdex];
	while (entry != nullptr) {
		if (entry->getKey() == key) {
			item = entry->getValue(); //set the item that was found
			return true; //'found it!'
		}
		entry = entry->getNext();
	}
	return false; //not found
}

template<typename V>
int HashMap<V>::getWithEfficiency(std::string key, V &item) {
	int hashdex = convertKeyToHash(key);
	int temp = key.length()*4;
	//very technically speaking, it takes 4 meaningful operations per character in the string
	//1: incrementing the FOR loop
	//2, 3: getting the i-th character from the string, which is done twice (to get the 3rd and 7th bits).
	//I say this counts because referencing and dereferencing counts.
	//Everything else is just computational. (ANDing with constants 0x4 and 0x40, modulo-ing i by 14, 
	//bitshifting by 2, bitshifting by 5, adding, and bitshifting by the modulo result.)
	//It was stated in discussion topics that
	//"x + y * 3 - z", "x += 12 * 3", "x = x + 12 * 3" all count as one operation.
	//Thusly I have counted my computation all together as one operation.
	HashNode<V>* entry = table[hashdex]; temp++;
	while (entry != nullptr) {
		if (entry->getKey() == key) {
			item = entry->getValue(); temp++; //set the item that was found
			return temp; //'found it!'
		}
		entry = entry->getNext(); temp++;
	}
	return -temp; //not found
}

template<typename V>
void HashMap<V>::place(std::string key, V &value) {
	int hashdex = convertKeyToHash(key);
	HashNode<V>* previous = nullptr;
	HashNode<V>* current = table[hashdex];

	//find a spot that is free
	//make sure that if we have duplicate entries that we don't crash or leak
	while (current != nullptr && current->getKey() != key) {
		previous = current;
		current = current->getNext();
	}

	//if this entry is null
	if (current == nullptr) {
		//make a new thing
		current = new HashNode<V>(key, value);

		//if there is no previous, then we have a first arrival
		if (previous == nullptr) {
			table[hashdex] = current;
			loadFactor++;
		}
		//if the previous item exists we gotta set its next to this new item.
		else {
			previous->setNext(current);
			loadFactor++;
		}
	}

	//entry is not null but we're >overwriting< it anyway
	else {
		current->setValue(value);
	}
}

template<typename V>
bool HashMap<V>::remove(std::string key) {
	int hashdex = convertKeyToHash(key);
	HashNode<V>* previous = nullptr;
	HashNode<V>* current = table[hashdex];

	//now, due to collisions, we need to verify that this item is the right one
	//thus we need to check the key against the key of current
	//we also need to make sure while advancing forward that the key when not found
	//does not cause access violation or infinite loop.
	if (current != nullptr) {
		while (key != current->getKey() && current != nullptr) {
			previous = current;
			current = current->getNext();
		}
	}

	if (current == nullptr) {
		//unfound
		return false;
	}
	else {
		if (previous == nullptr) {
			//the item we need to delete is the direct location,
			//thus we need to set the item to our child
			//(if our child is null, convienently, it works normally!)
			table[hashdex] = current->getNext();
		}
		else {
			//the item we need to delete is in the middle of the collision resolution
			previous->setNext(current->getNext());
		}
		delete current;
		loadFactor--;
		return true;
	}
}

template<typename V>
HashMap<V>::~HashMap() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		HashNode<V>* current = table[i];
		while (current != nullptr) {
			HashNode<V>* destroy;
			destroy = current;
			current = current->getNext();
			delete destroy;
		}
		table[i] = nullptr;
	}
	delete[] table;
}