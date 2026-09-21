const double MEMBER_DISCOUNT = 0.1;
const int ITEM_WIDTH = 16;
const int ITEM_CODE_WDITH = 6;
const int QUANTITY_WIDTH = 12;
const int PRICE_WIDTH = 8;
const int UNIT_PRICE_WIDTH = 12;

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
	
	cout << "Is Member (enter yes, no, true, or false): ";
	bool isMember = false;
	string isMemberString;
	cin >> isMemberString;
	if (isMemberString[0] == 't') isMember = true;
	if (isMemberString[0] == 'T') isMember = true;
	if (isMemberString[0] == 'y') isMember = true;
	if (isMemberString[0] == 'Y') isMember = true;
	
	cout << "Cashier Notes: ";
	string cashierNotes;
	cin.ignore();
	getline(cin, cashierNotes);
	
	cout << "'" << cashierNotes << "'" << endl;
	
	cout << endl;
	
	cout << left;
	int firstColumnWidth = max(ITEM_WIDTH, (int) foodName.length());
	double price = unitPrice * itemQuantity;
	
	cout << setw(firstColumnWidth) << "Item";
	cout << setw(ITEM_CODE_WDITH) << "Code";
	cout << setw(QUANTITY_WIDTH) << "Quantity";
	cout << right;
	cout << setw(PRICE_WIDTH) << "Price";
	cout << setw(UNIT_PRICE_WIDTH) << "Unit Price";
	cout << left;
	cout << endl;
	
	cout << setw(firstColumnWidth) << foodName;
	cout << setw(ITEM_CODE_WDITH) << itemCode;
	cout << setw(QUANTITY_WIDTH) << itemQuantity;
	cout << right;
	cout << fixed << setprecision(2) << setw(PRICE_WIDTH) << price;
	cout << fixed << setprecision(2) << setw(UNIT_PRICE_WIDTH) << unitPrice;
	cout << left;
	cout << endl;
	
	cout << endl;
	int total_width = firstColumnWidth + ITEM_CODE_WDITH + QUANTITY_WIDTH + PRICE_WIDTH + UNIT_PRICE_WIDTH;
	for (int i = 0; i < total_width; i++) {
		cout << '-';
	}
	cout << endl;
	
	double subtotal = price;
	
	double discount = 0.0;
	if (isMember) discount = subtotal * MEMBER_DISCOUNT;
	double total = subtotal - discount;
	
	int end_item_width = firstColumnWidth + ITEM_CODE_WDITH + QUANTITY_WIDTH;
	cout << left << setw(end_item_width) << "Subtotal" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << subtotal << endl;
	cout << left << setw(end_item_width) << "Discount" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << discount << endl;
	cout << left << setw(end_item_width) << "Total" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << total << endl;
	
	cout << endl;
	cout << "Cashier Notes:" << endl;
	cout << cashierNotes;
	
}
