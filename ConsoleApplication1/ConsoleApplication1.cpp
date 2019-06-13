// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// declare type of the discount	
enum discountType { amount, percentage };

/*
This class is used to define category of the products. It has private member textKey and other public members like 
description, name and parent_cat.
*/
class Item {
public:
	virtual double getTotalPrice() = 0;
	virtual string getName() = 0;
};
class Category {
private:
	string textKey; //Unique textKey to differentiate object from others
public:
	string description; // description page
	string name;
	Category* p_cat;
	Category(string nam, string dscrptn, string textK, Category* p_caat=NULL) {
		name = nam;
		description = dscrptn;
		textKey = textK;
		p_cat = p_caat;
	}
	Category() {}; // Default constructor
};

/* Product class has private textKey member because textKey shouldn't be accessed from the other classes.
It also has basic data slots for name of the product, price, discount if possible, etc.
There is  a default Product constructor and Constructor taking all arguments as well. Constructor handles with the
negative inputs throwing error.
The function getEffectivePrice calculates the price after discount. It also checks if the discount is bigger than price,
in which case throws an error, thus ensuring that methods don't return negative result.
*/
class Product: public Item {
private:
	string textKey;
public:
	string name;
	string description;
	double discount;
	double price;
	int quantity;
	discountType s; // what kind of discount? Amount or Percentage?
	Category cat; // Category of the product
	double GetEffectivePrice() { // To get the price of the product after discounts
		if (s == amount) {// if the type of discount is amount, this just deducts it from the price
			if (discount > price) {
				throw "Discount bigger than price!";
			}
			return price - discount;
		}
		else {
			if (price*discount / 100 > price) {
				throw "discount bigger than the price!";
			}
			return price - price*discount / 100;
		}
	}
	double getTotalPrice() {
		return quantity * GetEffectivePrice(); //Get the total price of products
	}
	string getName(){
		return name;
	}
	// Constructor for product class
	Product(string nam, string dscrptn, string textK, double prce, int quant, double dscnt, discountType a, Category c) {
		name = nam;
		description = dscrptn;
		textKey = textK;
		try {
			if (prce < 0) {
				throw "Negative number input. Try again";
			}
			price = prce;

		}
		catch (int a) {
			price = prce;
		}

		try {
			if (quant < 0) {
				throw "Negative number";
			}
			quantity = quant;

		}
		catch (int a) {
			quantity = quant;
		}

		try {
			if (dscnt < 0) {
				throw "Negative number or Discount is larger than Price. Try again";
			}
			discount = dscnt;
		}
		catch (int a) {
			discount = dscnt;
		}
		cat = c;
		s = a;
	}
	Product() {};

};

/* Service class inherits Product class and has protected own members that can't
be accessed from the other classes. It also has basic data slots for name of the product, price, discount if possible, etc.
There is  a default Service constructor and constructor taking all arguments as well. Constructor handles with the
negative inputs throwing error.
The function getEffectiveRate calculates the rate after discount. It also checks if the rateDiscount is bigger than the rate,
in which case throws an error, thus ensuring that methods don't return negative result.
*/
class Service :public Product {
protected:
	double duration;
	double rate;
	double rateDiscount;

	discountType r;
public:
	string name;
	double GetEffectiveRate() {
		if (amount) {
			if (rateDiscount > rate) {
				throw "Discount bigger than rate!";
			}
			return rate - rateDiscount;
		}
		else {
			if (rate*rateDiscount / 100 > rate) {
				throw "discount bigger than the rate!";
			}
			return rate - rate * rateDiscount / 100;
		}
	}
	double getTotalPrice() {
		return Product::getTotalPrice() + GetEffectiveRate()*duration;
	}
	string getName() {
		return name;
	}
	Service(string nam, double dur, double ratee, double rateDscnt, discountType a) {


		name = nam;
		try {
			if (dur < 0) {
				throw "negative input. try again!";
			}
			duration = dur;
		}
		catch (int a) {
			duration = duration;
		}
		try {
			if (ratee < 0) {
				throw "negative input. try again!";
			}
			rate = ratee;
		}
		catch (int a) {
			rate = rate;
		}
		try {
			if (rateDscnt < 0) {
				throw "negative input or Discount is bigger than Rate itself. try again!";
			}
			rateDiscount = rateDscnt;
		}
		catch (int a) {
			rateDiscount = rateDiscount;
		}

		r = a;
	}
	Service() {};
};


void merge(int arr[], int l, int m, int n) {
	int n1 = 1 + m - l;
	int n2 = n - m;

	double* arr_n1 = new double[n1];
	double* arr_n2 = new double[n2];

	int i;
	int j;
	int k;
	for (i = 0; i < n1; i++) {
		arr_n1[i] = arr[l + i];
		// N1 = {1, 2, 3}
	}
	for (j = 0; j < n2; j++) {
		arr_n2[j] = arr[m + j + 1];
		// n2 = {4, 5, 6}
	}
	i = 0; j = 0; // n2
	k = l; // middle point

	while (i < n1 && j < n2) {
		if (arr_n1[i] <= arr_n2[j]) {
			arr[k] = arr_n1[i];
			i++;
		}
		else {
			arr[k] = arr_n2[j];
			j++;
		}
		k++;

	}
	while (i < n1) {
		arr[k] = arr_n1[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = arr_n2[j];
		j++;
		k++;
	}
	delete arr_n1;
	delete arr_n2;
}

void mergeSort(int arr[], int l, int n) {
	int m = l + (n - l) / 2;
	if (l < n) {
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, n);

		merge(arr, l, m, n);
	}
}

void printArray(int arr[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		printf("%d \n", arr[i]);
	}
	printf("\n");
}

int main()
{
	// Implementing vectors to store pointers for class instances
	vector<Category*> categories;
	vector<Item*> items;
	
	// Load up the vector with Category objects
	Category* c = NULL;
	Category elec("Electronics", "everythin electronic", "text1");
	c = &elec;
	categories.push_back(c);
	Category drinks("drinks", "everythin drinks", "text2");
	c = &drinks;
	categories.push_back(c);
	Category food("food", "everythin food", "text3");
	c = &food;
	categories.push_back(c);
	Category cellphones("phones", "wide range of phones", "text4", &elec); //elec is parent category

	// Load up the vector with Product objects
	Item* p = NULL;
	Product g5("lga", "phone", "lg", 25.0, 10, 10, amount, elec);
	p = &g5;
	items.push_back(p);
	Product jack("daniels", "whiskey", "jd", 50.0, 120, 20, percentage, drinks);
	p = &jack;
	items.push_back(p);
	Product lays("chips", "chips paprika", "ls", 4.9, 500, 10, percentage, food);
	p = &lays;
	items.push_back(p);
	Product coke("coke", "famous Coke", "cc", 10, 20, 0.5, amount, drinks);
	p = &coke;
	items.push_back(p);


	// Load up the vector with Service objects
	Item* s = NULL;
	Service delivery("delivery", 15.0, 12.0, 10, percentage);
	s = &delivery;
	items.push_back(s);
	Service refund("refund", 10.2, 5, 2, amount);
	s = &refund;
	items.push_back(s);
	Service repair("repair" ,10, 8, 100, percentage);
	s = &repair;
	items.push_back(s);



	cout << "===Items===" << endl;
	int* arr = new int[items.size()];
	string * names = new string[items.size()];
	int k = 0;
	for (Item* i : items) {
		cout << i->getName() << " - ";
		names[k] = i->getName();
		arr[k] = (i->getTotalPrice());
		k++;
		cout << i->getTotalPrice() << endl;
	}
	mergeSort(arr, 0, 6);
	cout << "---------------"<<endl<<"sorted list of items's prices: "<< endl;
	printArray(arr, items.size());
	delete arr;
    return 0;
}