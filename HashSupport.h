#pragma once
#include <string>
#include <iostream>
#include "HashTable.h" //this is necessary due to scoping of global constants in visual stupidio :V
//hashing table header
//basic implementation; utilizing a noised modulo

//well, this is complicated because our key is strings;
//but generally we've got this.

//Collisions are supposed to be resolved with a few methods based on Project Option chosen, umm
//1) Linked List
//2) Quadratic Probe
//3) Buckets
//4) Linked List
//5) Linear Probe: +1, -2, +3, -4...
//6) Psuedorandom
//7) Key Offset

//technically speaking buckets and linked lists are the same

//we don't need to template the key because we know it will be a character string
//technically we don't need to template the value either because we know it will
//be a pointer to a Food item.
//BUT WELL I THINK THAT MAKING MY LIFE DIFFICULT IS GOOD IDEA I GUESS
template <typename V>
class HashNode {
private:
	std::string key;
	V value;
	HashNode* next; //collision handler: this is a linked list / bucket approach.
					//I'm rather disgusted by the probe methods because they make deleting very difficult without having an exceedingly padded table, which means you might as well have done it this way anyway because you need to do basically the same thing to end up handling it.
public:
	//constructor
	HashNode(const std::string key, const V &val) :
		key(key), value(val), next(NULL) {}

	//trivial getters
	std::string getKey() { return key; }
	V getValue() { return value; }
	HashNode* getNext() { return next; }

	//trivial setters: note that the KEY can never actually change because it's based on the item itself
	void setNext(HashNode* after) { next = after; }
	void setValue(V val) { value = val; }
	//wait but the key and the value are inherently linked for our purposes aaaaaAAAAAAAAAAAAAAAAAAAAAAAA oh well doesn't really matter
};

//========================================================================
//grab bit from each character and just use that
//what size array, because we only have 25+ elements
//primes sorta close to 25 are 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71
//so idk let's go with 47

//Outside of the hashnode (trivial), we need to create a hash do-er thing
//This thing needs to calculate the hash from the key
//It needs to put the item in the appropriate spot based on that hashed key.

//So the first step is to make key -> hash
int convertKeyToHash(std::string key) {
	//The hashed number is the 3rd and 7th bits of each character
	//so "a c" is 
	//0x61, 0x20, 0x63
	//a: 01100001
	// : 00100000
	//c: 01100011
	//    ^   ^
	//10b + (00b << 2) + (10b << 4)
	//or 00 10 00 10b, which is 0x22
	unsigned int calcHash = 0; //temp, temp2;

	for (unsigned int i = 0; i < key.length(); i++) {

		calcHash = calcHash + (((((unsigned int)key[i] & 0x4) >> 2) + (((unsigned int)key[i] & 0x40) >> 5)) << (i % 15));
		/* Expanded, that becomes:
		temp = (unsigned int)key[i];
		temp = (temp & 0x4); //strip off everything except the 3rd bit (which represents 0x04)
		temp = (temp >> 2); //move the 3rd bit to the 1rst bit
		temp2 = (unsigned int)key[i];
		temp2 = (temp2 & 0x40); //7th bit (0x40)
		temp2 = (temp2 >> 5); //7th -> 2nd bit
		//calcHash += (temp + temp2) << (i * 2);
		//need to make this end up NOT tossing out the characters past the 15th
		//so instead, uhh
		calcHash += (temp + temp2) << (i % 14);
		*/

		//Debug stuff
		//std::cout << temp << "   ";
		//std::cout << temp2 << " ";
		//std::cout << std::setw(6);
		//std::cout << ((temp + temp2) << (i*2)) << " ";
		//std::cout << std::setw(6);
		//std::cout << calcHash << std::endl;
	}

	return (calcHash % TABLE_SIZE);
}

//========================================================================