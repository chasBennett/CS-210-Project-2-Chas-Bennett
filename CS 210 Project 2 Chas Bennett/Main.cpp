/*
Project Two: Airgead Banking
Author: Chas Bennett
Date: 03/30/2025
Class: CS-210
Professor Parsons
 */

#include <iostream> // Included the iostream so that cout can be used.
#include "InvestmentData.h" // Included InvestmentData.h so that it's methods can be called from main().
#include "Tools.h" // Included Tools.h so that it's methods can be called from main().

 // Main Function  
int main() {

	// This utilizes the getConsoleWidth() method from Tools.h and sets the defaultPadding value based on the width of the console. The goal here is to center the text within the console window.
	if (getConsoleWidth() >= 40) { // The standard width of most elements in this program is 40 characters. If the console is larger than that, padding is equal to half of the remaining spaces.
		setDefaultPadding((getConsoleWidth() - 40) / 2);
	}
	else {
		setDefaultPadding(0); // If the console window isn't wide enough to fit all 40 characters of each line of text, then set the padding to zero.
	}

	cout << endl << endl << applyInset("Welcome to the Airgead Banking App!") << endl; // Welcome message for the user.
	InvestmentData data = gatherUserInfo(); // A new instantiation of InvestmentData is initialized and given the alias of "data".
	while (true) { // Loops until a value is returned.
		// This utilizes the userSelection(InvestmentData data) method from Tools.h to assign an int value to the choice variable. Error handling is built into this method to ensure only an int can be returned.
		int choice = userSelection(data);
		// The printReport method is called two times using the data object as input and with the bool monthly parameter set to true. First it's called to run without monthly contributions. Then, it's called with monthly contributions.
		if (choice == 1) {
			printReport(data, false, true);
			printReport(data, true, true);
		}
		// The printReport method is called two times using the data object as input and with the bool monthly parameter set to false (yearly instead). First it's called to run without monthly contributions. Then, it's called with monthly contributions.
		else if (choice == 2) {
			printReport(data, false, false);
			printReport(data, true, false);
		}
		// The user is prompted to enter data for the InvestmentData object again so that they can see a new set of values and compare them.
		else if (choice == 3) {
			data = gatherUserInfo();
		}
		else { // This displays a thank you message and ends the program.
			cout << endl << applyInset("Thank you for using the Airgead Banking App!") << endl;
			return 0;
		}
	}
}

// end code