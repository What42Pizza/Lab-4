const double MEMBER_DISCOUNT = 0.1;
const int ITEM_WIDTH = 16;
const int QUANTITY_WIDTH = 12;
const int PRICE_WIDTH = 24;
const int UNIT_PRICE_WIDTH = 12;

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Mock menu:
// Code    Product      Small (s)    Medium (m)    Large (l)
// A       Something    $1.00        $1.00         $1.00
// B       Something    $1.00        $1.00         $1.00
// C       Something    $1.00        $1.00         $1.00

struct Product {
	string name;
	double smallPrice;
	double mediumPrice;
	double largePrice;
};

int main() {
	
	Product products[3] = {};
	products[0] = {"Apple Juice", 2.50, 3.50, 4.50};
	products[1] = {"Coffee"     , 2.50, 3.50, 4.50};
	products[2] = {"Green Tea"  , 2.50, 3.50, 4.50};
	
	cout << "Drink, Small (s), Medium (m), Large (l)" << endl;
	cout << "A Apple Juice 1.0 1.0 1.0" << endl;
	cout << "B Coffee 1.0 1.0 1.0" << endl;
	cout << "C Green Tea 1.0 1.0 1.0" << endl;
	
	
	
	char itemChoice;
	char sizeChoice;
	
	cout << "Select an item: ";
	cin >> itemChoice;
	cout << "Select a size: ";
	cin >> sizeChoice;
	
	Product chosenProduct;
	switch (toupper(itemChoice)) {
		case 'A':
			chosenProduct = products[0];
			break;
		case 'B':
			chosenProduct = products[1];
			break;
		case 'C':
			chosenProduct = products[2];
			break;
		default:
			
			break;
	}
	
	double unitPrice;
	switch (toupper(sizeChoice)) {
		case 'S':
			unitPrice = chosenProduct.smallPrice;
			break;
		case 'M':
			unitPrice = chosenProduct.mediumPrice;
			break;
		case 'L':
			unitPrice = chosenProduct.largePrice;
			break;
		default:
			
			break;
	}
	
	
	
	cout << endl;
	cout << "Item chosen: " << chosenProduct.name << " (" << ((char) toupper(sizeChoice)) << ") for $" << fixed << setprecision(2) << unitPrice << endl;
	
	
	
	cout << "Item Quantity: ";
	int itemQuantity;
	cin >> itemQuantity;
	
	cout << "Is Member (enter yes, no, true, or false): ";
	bool isMember = false;
	string isMemberString;
	cin >> isMemberString;
	if (isMemberString[0] == 't') isMember = true;
	if (isMemberString[0] == 'T') isMember = true;
	if (isMemberString[0] == 'y') isMember = true;
	if (isMemberString[0] == 'Y') isMember = true;
	
	
	
	cout << endl;
	cout << left;
	int firstColumnWidth = max(ITEM_WIDTH, (int) chosenProduct.name.length());
	double price = unitPrice * itemQuantity;
	
	cout << setw(firstColumnWidth) << "Item";
	cout << setw(QUANTITY_WIDTH) << "Quantity";
	cout << right;
	cout << setw(PRICE_WIDTH) << "Price";
	cout << setw(UNIT_PRICE_WIDTH) << "Unit Price";
	cout << left;
	cout << endl;
	
	cout << setw(firstColumnWidth) << chosenProduct.name;
	cout << setw(QUANTITY_WIDTH) << itemQuantity;
	cout << right;
	cout << fixed << setprecision(2) << setw(PRICE_WIDTH) << price;
	cout << fixed << setprecision(2) << setw(UNIT_PRICE_WIDTH) << price;
	cout << left;
	cout << endl;
	
	cout << endl;
	int total_width = firstColumnWidth + QUANTITY_WIDTH + PRICE_WIDTH + UNIT_PRICE_WIDTH;
	for (int i = 0; i < total_width; i++) {
		cout << '-';
	}
	cout << endl;
	
	double subtotal = price;
	
	double discount = 0.0;
	if (isMember) discount = subtotal * MEMBER_DISCOUNT;
	double total = subtotal - discount;
	
	int end_item_width = firstColumnWidth + QUANTITY_WIDTH;
	cout << left << setw(end_item_width) << "Subtotal" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << subtotal << endl;
	cout << left << setw(end_item_width) << "Discount" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << discount << endl;
	cout << left << setw(end_item_width) << "Total" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << total << endl;
	
}
