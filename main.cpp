const double MEMBER_DISCOUNT = 0.1;
const int ITEM_WIDTH = 24;
const int QUANTITY_WIDTH = 12;
const int PRICE_WIDTH = 24;
const int UNIT_PRICE_WIDTH = 12;
const double ARKANSAS_STATE_TAX = 6.5;
const double FAULKNER_COUNTY_TAX = 0.5;
const double CONWAY_MUNICIPAL_TAX = 2.125;

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;



// custom types

struct Product {
	// the name of the product
	string name;
	// the price of the small variant
	double smallPrice;
	// the price of the medium variant
	double mediumPrice;
	// the price of the large variant
	double largePrice;
	// the quantity of this product in inventory
	int inventoryCount;
	// the amount of this product that has been taken from inventory by this program 
	int amountTaken;
};



// processes a customer, asks for customer items, prints and writes receipt, etc
void serveCustomer(vector<Product> &products, ofstream &receiptFile);

// generates and outputs the receipt to the given output stream
void printReceipt(ostream &output, string customerName, string itemsOutput, double afterTax, double tipAmount, double subtotal, double afterMembership, double arkansasStateTax, double faulknerCountyTax, double conwayMunicipalTax);

// Gets the character width needed to print a column of product names 
int getProductNamesWidth(vector<Product> &products);

// prompts the user for a yes/no input with the given prompt
bool getYesNoInput(string prompt);

// converts a string to lowercase
// note: this edits the input string instead of returning a new string
void toLower(string &str);



int main() {
	
	
	
	// open file objects
	
	ofstream receiptFile;
	receiptFile.open("Receipt.txt");
	if (!receiptFile.is_open()) {
		cout << "Error: could not open file \"Receipt.txt\"";
		return 1;
	}
	
	ifstream itemDatas;
	itemDatas.open("Item Datas.txt");
	if (!itemDatas.is_open()) {
		cout << "Error: could not open file \"Item Datas.txt\"";
		return 1;
	}
	
	ifstream inventory;
	inventory.open("Inventory.txt");
	if (!inventory.is_open()) {
		cout << "Error: could not open file \"Inventory.txt\"";
		return 1;
	}
	
	
	
	// parse item datas file
	
	vector<Product> products;
	
	int i = 0;
	while (true) {
		string productName;
		if (getline(itemDatas, productName)) {
			products.push_back({});
			products[i].name = productName;
			itemDatas >> products[i].smallPrice;
			itemDatas >> products[i].mediumPrice;
			itemDatas >> products[i].largePrice;
			itemDatas.ignore();
		} else {
			break;
		}
		i ++;
	}
	itemDatas.close();
	
	
	
	// parse inventory file
	
	i = 0;
	while (true) {
		string productName;
		if (getline(inventory, productName)) {
			if (productName != products[i].name) {
				cout << "Warning: item " << (i + 1) << " of Item Datas.txt does not match item " << (i + 1) << " of Inventory.txt" << endl;
			}
			inventory >> products[i].inventoryCount;
			inventory.ignore();
		} else {
			break;
		}
		i ++;
	}
	inventory.close();
	
	
	
	// main loop
	
	bool moreCustomers = true;
	while (moreCustomers) {
		
		serveCustomer(products, receiptFile);
		
		cin.ignore();
		cout << endl;
		cout << endl;
		moreCustomers = getYesNoInput("Do another customer? (enter Yes or No:) ");
		
	}
	
	// close receipt file, not needed after main loop
	receiptFile.close();
	
	
	
	// save inventory
	
	ofstream inventoryOut;
	inventoryOut.open("Inventory.txt");
	for (int i = 0; i < (int) products.size(); i++) {
		inventoryOut << products[i].name << endl;
		inventoryOut << products[i].inventoryCount << endl;
	}
	inventoryOut.close();
	
	
	
	// print daily inventory and what has changed
	
	cout << endl;
	cout << "Daily Inventory:" << endl;
	
	int producNamesWidth = getProductNamesWidth(products);
	cout << left << setw(producNamesWidth + 2) << "Drink" << "Start    Change    End" << endl << setprecision(2) << fixed;
	for (int i = 0; i < (int) products.size(); i ++) {
		int change = -products[i].amountTaken;
		int end = products[i].inventoryCount;
		int start = end - change;
		cout << left << setw(producNamesWidth) << products[i].name << setw(9) << start << setw(9) << change << end << endl;
	}
	
}



void serveCustomer(vector<Product> &products, ofstream &receiptFile) {
	
	cout << "Customer name: ";
	string customerName;
	getline(cin, customerName);
	
	ostringstream itemsOutput;
	bool addMoreItems = true;
	double itemsTotal = 0.0;
	while (addMoreItems) {
		
		
		
		// print available products
		
		int producNamesWidth = getProductNamesWidth(products);
		cout << endl;
		cout << left << setw(producNamesWidth + 2) << "Drink" << "Small (s)   Medium (m)   Large (l)" << endl << setprecision(2) << fixed;
		for (int i = 0; i < (int) products.size(); i ++) {
			cout << (char) ('A' + i) << " " << left << setw(producNamesWidth) << products[i].name << "$" << products[i].smallPrice << "       " << "$" << products[i].mediumPrice << "        " << "$" << products[i].largePrice << endl;
		}
		
		
		
		// choose a product
		
		Product* chosenProduct = &products[0];
		bool inputIsValid = false;
		while (!inputIsValid) {
			char itemChoice;
			cout << "Select an item: ";
			cin >> itemChoice;
			switch (toupper(itemChoice)) {
				case 'A':
					chosenProduct = &products[0];
					inputIsValid = true;
					break;
				case 'B':
					chosenProduct = &products[1];
					inputIsValid = true;
					break;
				case 'C':
					chosenProduct = &products[2];
					inputIsValid = true;
					break;
				default:
					inputIsValid = false;
					cout << "Input is not valid" << endl;
					break;
			}
		}
		
		// choose a size
		
		inputIsValid = false;
		char sizeChoice;
		double unitPrice;
		while (!inputIsValid) {
			cout << "Select a size: ";
			cin >> sizeChoice;
			switch (toupper(sizeChoice)) {
				case 'S':
					unitPrice = chosenProduct->smallPrice;
					inputIsValid = true;
					break;
				case 'M':
					unitPrice = chosenProduct->mediumPrice;
					inputIsValid = true;
					break;
				case 'L':
					unitPrice = chosenProduct->largePrice;
					inputIsValid = true;
					break;
				default:
					inputIsValid = false;
					cout << "Input is not valid" << endl;
					break;
			}
		}
		
		cout << endl;
		cout << "Item chosen: " << chosenProduct->name << " (" << ((char) toupper(sizeChoice)) << ") for $" << fixed << setprecision(2) << unitPrice << endl;
		
		// choose an amount
		
		cout << endl;
		cout << "Item Quantity: ";
		int itemQuantity;
		cin >> itemQuantity;
		chosenProduct->inventoryCount -= itemQuantity;
		chosenProduct->amountTaken += itemQuantity;
		
		itemsOutput << left;
		itemsOutput << setw(ITEM_WIDTH) << chosenProduct->name;
		itemsOutput << setw(QUANTITY_WIDTH) << itemQuantity;
		itemsOutput << right;
		itemsOutput << fixed << setprecision(2) << setw(PRICE_WIDTH) << (unitPrice * itemQuantity);
		itemsOutput << fixed << setprecision(2) << setw(UNIT_PRICE_WIDTH) << unitPrice;
		itemsOutput << left;
		itemsOutput << endl;
		
		itemsTotal += unitPrice * itemQuantity;
		
		
		
		// ask if more items should be added
		
		cin.ignore();
		cout << endl;
		addMoreItems = getYesNoInput("Add another item? (enter Yes or No:) ");
		
	}
	
	
	
	// ask final questions
	cout << endl;
	bool isMember = getYesNoInput("Is Member? (enter Yes or No:) ");
	
	// calculate maount owed
	
	double subtotal = itemsTotal;
	
	double discount = 0.0;
	if (isMember) discount = subtotal * MEMBER_DISCOUNT;
	double afterMembership = subtotal - discount;
	
	double arkansasStateTax = subtotal * (ARKANSAS_STATE_TAX / 100.0);
	double faulknerCountyTax = subtotal * (FAULKNER_COUNTY_TAX / 100.0);
	double conwayMunicipalTax = subtotal * (CONWAY_MUNICIPAL_TAX / 100.0);
	double afterTax = afterMembership + arkansasStateTax + faulknerCountyTax + conwayMunicipalTax;
	
	
	
	// ask for tip
	
	cout << endl;
	cout << "Tip Selection		Amount" << endl;
	cout << "A. 15%             $"<< fixed << setprecision(2) << afterTax * 0.15 << endl;
	cout << "B. 20%             $"<< fixed << setprecision(2) << afterTax * 0.20 << endl;
	cout << "C. 25%             $"<< fixed << setprecision(2) << afterTax * 0.25 << endl;
	cout << "D. Custom Tip" << endl;
	double tipAmount;
	
	bool inputIsValid = false;
	while (!inputIsValid) {
		char tipChoice;
		cin >> tipChoice;
		switch (toupper(tipChoice)) {
			case 'A':
				tipAmount = afterTax * 0.15;
				inputIsValid = true;
				break;
			case 'B':
				tipAmount = afterTax * 0.20;
				inputIsValid = true;
				break;
			case 'C':
				tipAmount = afterTax * 0.25;
				inputIsValid = true;
				break;
			case 'D': 
				cout << "Enter custom tip amount: $";
				inputIsValid = true;
				cin >> tipAmount;
				break;
			default:
				cout << "Input is not valid" << endl;
				inputIsValid = false;
				break;
		}
	}
	
	
	
	// create receipt
	
	cout << endl;
	cout << left;
	
	cout << "Receipt:" << endl;
	printReceipt(cout, customerName, itemsOutput.str(), afterTax, tipAmount, subtotal, afterMembership, arkansasStateTax, faulknerCountyTax, conwayMunicipalTax);
	printReceipt(receiptFile, customerName, itemsOutput.str(), afterTax, tipAmount, subtotal, afterMembership, arkansasStateTax, faulknerCountyTax, conwayMunicipalTax);
	
}



void printReceipt(ostream &output, string customerName, string itemsOutput, double afterTax, double tipAmount, double subtotal, double afterMembership, double arkansasStateTax, double faulknerCountyTax, double conwayMunicipalTax) {
	
	int total_width = ITEM_WIDTH + QUANTITY_WIDTH + PRICE_WIDTH + UNIT_PRICE_WIDTH;
	string separator;
	for (int i = 0; i < total_width; i++) {
		separator += '-';
	}
	
	// print header
	output << separator << endl;
	output << "Customer: " << customerName << endl;
	output << endl;
	
	// print items
	output << setw(ITEM_WIDTH) << "Item";
	output << setw(QUANTITY_WIDTH) << "Quantity";
	output << right;
	output << setw(PRICE_WIDTH) << "Price";
	output << setw(UNIT_PRICE_WIDTH) << "Unit Price";
	output << left;
	output << endl;
	
	output << itemsOutput;
	
	output << endl;
	output << separator << endl;
	
	// print tax amounts
	int end_item_width = ITEM_WIDTH + QUANTITY_WIDTH;
	output << left << setw(end_item_width) << "Arkansas State Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << arkansasStateTax << endl;
	output << left << setw(end_item_width) << "Faulkner County Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << faulknerCountyTax << endl;
	output << left << setw(end_item_width) << "Conway Municipal Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << conwayMunicipalTax << endl;
	
	// get loyalty points amount
	double totalAmount = afterTax + tipAmount;
	int loyaltyPoints = totalAmount / 3; 
	string loyaltyPointsString = "";
	for (int i = 0; i < loyaltyPoints; i++) {
		loyaltyPointsString += "*";
	} 
	
	// print totals and subtotals
	output << left << setw(end_item_width) << "Subtotal" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << subtotal << endl;
	output << left << setw(end_item_width) << "After Membership" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << afterMembership << endl;
	output << left << setw(end_item_width) << "After Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << afterTax << endl;
	output << left << setw(end_item_width) << "Tip" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << tipAmount << endl;
	output << left << setw(end_item_width) << "Total" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << totalAmount << endl;
	output << left << setw(end_item_width) << "Loyalty Points" << right << setw(PRICE_WIDTH) << loyaltyPointsString << endl;
	
	output << separator << endl;
	
}



int getProductNamesWidth(vector<Product> &products) {
	int max_width = 5;
	for (int i = 0; i < (int) products.size(); i ++) {
		max_width = max(max_width, (int) products[i].name.length());
	}
	return max_width + 3;
}



bool getYesNoInput(string prompt) {
	while (true) {
		
		// get input
		cout << prompt;
		string input;
		getline(cin, input);
		toLower(input);
		
		// check input
		if (input == "yes" || input == "y" || input == "true" || input == "t" || input == "1") {
			return true;
		} else if (input == "no" || input == "n" || input == "false" || input == "f" || input == "0") {
			return false;
		} else {
			cout << "Input is not valid" << endl;
		}
		
	}
}



void toLower(string &str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}
