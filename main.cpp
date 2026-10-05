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
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void toLower(string &str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

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

	bool moreCustomers = true;
	while( moreCustomers){
		
		Product products[3] = {};
		products[0] = {"Apple Juice", 2.50, 3.50, 4.50};
		products[1] = {"Coffee"     , 2.50, 3.50, 4.50};
		products[2] = {"Green Tea"  , 2.50, 3.50, 4.50};
		
		cout << "Customer name: ";
		string customerName;
		cin >> customerName;
		
		ostringstream itemsOutput;
		bool addMoreItems = true;
		double itemsTotal = 0.0;
		while (addMoreItems) {
			
			cout << "Drink           Small (s)   Medium (m)   Large (l)" << endl;
			cout << "A Apple Juice   $2.50       $3.50        $4.50" << endl;
			cout << "B Coffee        $2.50       $3.50        $4.50" << endl;
			cout << "C Green Tea     $2.50       $3.50        $4.50" << endl;
			
			
			
			Product chosenProduct;
			
			bool inputIsValid = false;
			while (!inputIsValid) {
				char itemChoice;
				cout << "Select an item: ";
				cin >> itemChoice;
				switch (toupper(itemChoice)) {
					case 'A':
						chosenProduct = products[0];
						inputIsValid = true;
						break;
					case 'B':
						chosenProduct = products[1];
						inputIsValid = true;
						break;
					case 'C':
						chosenProduct = products[2];
						inputIsValid = true;
						break;
					default:
						inputIsValid = false;
						cout << "Input is not valid" << endl;
						break;
				}
			}
			
			inputIsValid = false;
			char sizeChoice;
			double unitPrice;
			while (!inputIsValid) {
				cout << "Select a size: ";
				cin >> sizeChoice;
				switch (toupper(sizeChoice)) {
					case 'S':
						unitPrice = chosenProduct.smallPrice;
						inputIsValid = true;
						break;
					case 'M':
						unitPrice = chosenProduct.mediumPrice;
						inputIsValid = true;
						break;
					case 'L':
						unitPrice = chosenProduct.largePrice;
						inputIsValid = true;
						break;
					default:
						inputIsValid = false;
						cout << "Input is not valid" << endl;
						break;
				}
			}
			
			
			
			cout << endl;
			cout << "Item chosen: " << chosenProduct.name << " (" << ((char) toupper(sizeChoice)) << ") for $" << fixed << setprecision(2) << unitPrice << endl;
			
			cout << "Item Quantity: ";
			int itemQuantity;
			cin >> itemQuantity;
		
			itemsOutput << left;
			itemsOutput << setw(ITEM_WIDTH) << chosenProduct.name;
			itemsOutput << setw(QUANTITY_WIDTH) << itemQuantity;
			itemsOutput << right;
			itemsOutput << fixed << setprecision(2) << setw(PRICE_WIDTH) << (unitPrice * itemQuantity);
			itemsOutput << fixed << setprecision(2) << setw(UNIT_PRICE_WIDTH) << unitPrice;
			itemsOutput << left;
			itemsOutput << endl;
			
			itemsTotal += unitPrice * itemQuantity;
			
			
			
			inputIsValid = false;
			cin.ignore();
			while (!inputIsValid) {
				
				cout << "Add another item? (enter Yes or No:) ";
				string addAnotherItemString;
				getline(cin, addAnotherItemString);
				toLower(addAnotherItemString);
				
				if (addAnotherItemString == "yes") {
					addMoreItems = true;
					inputIsValid = true;
				} else if (addAnotherItemString == "no") {
					addMoreItems = false;
					inputIsValid = true;
				} else {
					cout << "Input is not valid" << endl;
					inputIsValid = false;
				}
				
			}
			
		}
		
		
		
		bool inputIsValid = false;
		bool isMember = false;
		while (!inputIsValid) {
			
			cout << "Is Member? (enter Yes or No:) ";
			string isMemberString;
			getline(cin, isMemberString);
			toLower(isMemberString);
			
			if (isMemberString == "yes") {
				isMember = true;
				inputIsValid = true;
			} else if (isMemberString == "no") {
				isMember = false;
				inputIsValid = true;
			} else {
				cout << "Input is not valid" << endl;
				inputIsValid = false;
			}
			
		}


		double subtotal = itemsTotal;
		
		double discount = 0.0;
		if (isMember) discount = subtotal * MEMBER_DISCOUNT;
		double afterMembership = subtotal - discount;
		
		double arkansasStateTax = subtotal * (ARKANSAS_STATE_TAX / 100.0);
		double faulknerCountyTax = subtotal * (FAULKNER_COUNTY_TAX / 100.0);
		double conwayMunicipalTax = subtotal * (CONWAY_MUNICIPAL_TAX / 100.0);
		double afterTax = afterMembership + arkansasStateTax + faulknerCountyTax + conwayMunicipalTax;
		
		cout << endl;
		cout << "Tip Selection		Amount" << endl;
		cout << "A. 15%             $"<< fixed << setprecision(2) << afterTax * 0.15 << endl;
		cout << "B. 20%             $"<< fixed << setprecision(2) << afterTax * 0.20 << endl;
		cout << "C. 25%             $"<< fixed << setprecision(2) << afterTax * 0.25 << endl;
		cout << "D. Custom Tip" << endl;
		double tipAmount;
		
		inputIsValid = false;
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

		
		
		cout << endl;
		cout << left;
		
		cout << "Receipt:" << endl;
		int total_width = ITEM_WIDTH + QUANTITY_WIDTH + PRICE_WIDTH + UNIT_PRICE_WIDTH;
			for (int i = 0; i < total_width; i++) {
			cout << '-';
		}
		cout << endl;
		cout << "Customer: " << customerName << endl;
		cout << endl;
		
		cout << setw(ITEM_WIDTH) << "Item";
		cout << setw(QUANTITY_WIDTH) << "Quantity";
		cout << right;
		cout << setw(PRICE_WIDTH) << "Price";
		cout << setw(UNIT_PRICE_WIDTH) << "Unit Price";
		cout << left;
		cout << endl;
		
		cout << itemsOutput.str();
		
		cout << endl;
		for (int i = 0; i < total_width; i++) {
			cout << '-';
		}
		cout << endl;

		int end_item_width = ITEM_WIDTH + QUANTITY_WIDTH;
		cout << left << setw(end_item_width) << "Arkansas State Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << arkansasStateTax << endl;
		cout << left << setw(end_item_width) << "Faulkner County Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << faulknerCountyTax << endl;
		cout << left << setw(end_item_width) << "Conway Municipal Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << conwayMunicipalTax << endl;

		double totalAmount = afterTax + tipAmount;
		
		int loyaltyPoints = totalAmount / 3; 
		string loyaltyPointsString = "";
		for (int i = 0; i < loyaltyPoints; i++) {
			loyaltyPointsString += "*";
		} 
		
		cout << left << setw(end_item_width) << "Subtotal" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << subtotal << endl;
		cout << left << setw(end_item_width) << "After Membership" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << afterMembership << endl;
		cout << left << setw(end_item_width) << "After Tax" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << afterTax << endl;
		cout << left << setw(end_item_width) << "Tip" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << tipAmount << endl;
		cout << left << setw(end_item_width) << "Total" << right << setw(PRICE_WIDTH) << fixed << setprecision(2) << totalAmount << endl;
		cout << left << setw(end_item_width) << "Loyalty Points" << right << setw(PRICE_WIDTH) << loyaltyPointsString << endl;
		
		inputIsValid = false;
		cin.ignore();
		while (!inputIsValid) {
			
			cout << "Do another customer? (enter Yes or No:) ";
			string doAnotherCustomer;
			getline(cin, doAnotherCustomer);
			toLower(doAnotherCustomer);
			
			if (doAnotherCustomer == "yes") {
				moreCustomers = true;
				inputIsValid = true;
			} else if (doAnotherCustomer == "no") {
				moreCustomers = false;
				inputIsValid = true;
			} else {
				cout << "Input is not valid" << endl;
				inputIsValid = false;
			}
			
		}

	}
}

/*

subtotal = all items to pay for
after_membership = subtotal * (1.0 - discount)
after_tax = after_membership * (1.0 + tax)
total = after_tax + tip

*/
