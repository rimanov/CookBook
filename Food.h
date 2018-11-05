#pragma once
#include <iostream>
#include <string>
#include "Ingredient.h"

class Food : public Ingredient {
public:
	Ingredient* topIngredient; //first item in linked list
	std::string m_title;
	std::string m_serves;
	double calories;
	Food(); //base constructor
	Food(std::string);
	Food(std::string, std::string);
	~Food();
	//LinkedList ofIngredients;
	void addNewIngredient(std::string name, double pro, double carb, double fat);
	bool compareProFat(double, double);
	bool operator<(const Food&);
	bool operator>(const Food&);
	bool operator==(const Food&);
	bool  operator==(const std::string&);
	bool  operator<(const std::string&);
	bool  operator>(const std::string&);
};

Food::~Food() {
	
}
Food::Food()
{
}

Food::Food(std::string title) : m_title(title), m_serves("1"), topIngredient(nullptr), calories(0)
{

}

Food::Food(std::string title, std::string serves) : m_title(title), m_serves(serves), topIngredient(nullptr), calories(0)
{

}

void Food::addNewIngredient(std::string name, double pro, double carb, double fat) {
	//make the new ingredient

	Ingredient* newIng = new Ingredient(name, pro, carb, fat); //create ingredient object
	calories += newIng->totalCalories();   //calculate total calories as ingredients are added
	modifyPro(getPro() + pro);
	modifyCarb(getCarb() + carb);
	modifyFat(getFat() + fat);
	//have new ingredient's next ingredient equal topIngredient
	newIng->addNextIngredient(topIngredient);
	//keep track of ingredients by having topIngredient pointer point to newIng
	topIngredient = newIng;

}

bool Food::compareProFat(double pro, double fat) {
	bool equals = false;
	double ratio, otherRatio;
	if (getFat() == 0) { //if fat is zero, can't divide by zero
		ratio = -1;
	}
	else {
		ratio = (getPro() / getFat());
	}
	if (fat == 0) { //if fat is zero, can't divide by zero
		otherRatio = -1;
	}
	else {
		otherRatio = (pro / fat);
	}

	if (ratio == otherRatio) { //if the ratios are true then return true
		equals = true;
	}

	return equals;
}

bool Food::operator<(const Food& compFood) {
	return (m_title < compFood.m_title);
}

bool Food::operator>(const Food& compFood) {
	return (m_title > compFood.m_title);
}

bool Food::operator==(const Food& compFood) {
	return (m_title == compFood.m_title);
}

bool Food::operator==(const std::string& compName) {
	return (m_title == compName);
}

bool Food::operator<(const std::string& compName) {
	return (m_title < compName);
}

bool Food::operator>(const std::string& compName) {
	return (m_title > compName);
}





