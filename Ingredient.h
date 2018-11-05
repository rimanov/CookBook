#pragma once
#include <iostream>

class Ingredient {
private:
	std::string m_name;
	double m_pro, m_carb, m_fat;
	Ingredient* nextIngredient;
public:
	friend class Food;
	Ingredient(); //default constructor
	Ingredient(std::string);
	Ingredient(std::string, double, double, double);
	~Ingredient(); //destructor
	void addNextIngredient(Ingredient*);
	bool operator==(const Ingredient&);
	void modifyCarb(double);      
	void modifyFat(double);
	void modifyPro(double);
	double totalCalories();
	std::string getName();
	double getPro();
	double getCarb();
	double getFat();
	Ingredient* getNext();
};

Ingredient::~Ingredient() {

}

Ingredient::Ingredient()
	: m_name("untitled"), m_pro(0), m_carb(0), m_fat(0), nextIngredient(nullptr)
{

}

Ingredient::Ingredient(std::string name)
	: m_name(name), m_pro(0), m_carb(0), m_fat(0), nextIngredient(nullptr)
{

}

Ingredient::Ingredient(std::string name, double pro, double carb, double fat)
	: m_name(name), m_pro(pro), m_carb(carb), m_fat(fat), nextIngredient(nullptr)
{

}

bool Ingredient::operator==(const Ingredient& ing) { //overloaded == to compare by name of ingredients
	if (m_name == ing.m_name)
		return true;
	else
		return false;
}
//points to the next ingredient in the list
void Ingredient::addNextIngredient(Ingredient* nextIng) {
	nextIngredient = nextIng;
}


void Ingredient::modifyCarb(double newCarb) {
	m_carb = newCarb;
}

void Ingredient::modifyFat(double newFat) {
	m_fat = newFat;
}

void Ingredient::modifyPro(double newPro) {
	m_pro = newPro;
}


std::string Ingredient::getName() { return m_name; }    //getters because data is private
double Ingredient::getPro() { return m_pro; }
double Ingredient::getCarb() { return m_carb; }
double Ingredient::getFat() { return m_fat; }
Ingredient* Ingredient::getNext() { return nextIngredient; }

//returns total calories of ingredients
double Ingredient::totalCalories() {
	return ((m_carb * 4) + (m_pro * 4) + (m_fat * 9));
}

