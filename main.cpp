const double MEMBER_DISCOUNT = 0.1;
const int ITEM_WIDTH = 16;
const int ITEM_CODE_WDITH = 6;
const int QUANTITY_WIDTH = 12;
const int PRICE_WIDTH = 8;
const int UNIT_PRICE_WIDTH = 10;

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	
	cout << "Food Name: ";
	string foodName;
	getline(cin, foodName);
	
	cout << "Item Code: ";
	char itemCode;
	cin >> itemCode;
	
	cout << "Item Quantity: ";
	int itemQuantity;
	cin >> itemQuantity;
	
	cout << "Unit Price: ";
	double unitPrice;
	cin >> unitPrice;
	
	cout << "Is Member (enter true or false): ";
	bool isMember;
	cin >> isMember;
	
	if (isMember) unitPrice *= 1.0 - MEMBER_DISCOUNT;
	
	cout << "Cashier Notes: ";
	string cashierNotes;
	cin.ignore();
	getline(cin, cashierNotes);
	
	cout << left;
	
	
	
}
