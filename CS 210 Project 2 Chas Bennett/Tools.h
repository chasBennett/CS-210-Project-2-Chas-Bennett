#pragma once
#include <sstream> // Included for string validation methods.
#include <iostream> // Included to provide access for input and output methods (cin, cout);
#include <windows.h> // Included so the application can measure the console window and make adjustments to the defaultPadding value;
#include <string> // Included for string manipulation methods.
#include <iomanip> // Included for use of the setprecision() method.

int defaultPadding = 20; // Used to set the padding throughout the application. The value is initialized to 20;

// Method to measure the console window's width. This width is used to determine the proper padding for all of the text elements that will print to the console.
static int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Setter method for setting the defaultPadding value.
static void setDefaultPadding(int padding) {
	defaultPadding = padding;
}

// Method to check a string to see if its a double and return a boolean value. True indicates that the string is a valid double. The method works by iterating through the string and attempting to add characters to a double. 
// If it fails, false is returned.
static bool isDouble(string s) {
	istringstream iss(s);
	double d;
	char remaining_chars;
	iss >> noskipws >> d; // noskipws prevents skipping whitespace.
	return (d > 0) && !(iss >> remaining_chars); // If the string is a double, the remaining characters will be empty. If not, the remaining characters will be something other than whitespace.
}

// Method to check the characters in a string and ensure they are in the allowed characters string. A boolean value of false means an un-allowed character was found and string::npos was produced by the method.
static bool isValidInput(string input, string allowedChars) {
	return input.find_first_not_of(allowedChars) == string::npos;
}

// Method to apply a number of space characters equal to the defaultPadding value to the beginning of a string provided via the "s" parameter and return it.
static string applyInset(string s) {
	return string(defaultPadding, ' ') + s;
}

// Method to apply a number of space characters equal to the "inset" parameter to the beginning of the string provided via the "s" parameter and return it.
static string applyInset(int inset, string s) {
	return string(inset, ' ') + s;
}

// Method to retrieve a double value from the user using a prompt that is provided as a parameter of the method. The method loops until a valid double is entered, using error messages to prompt the user to try again. 
// The valid value is returned once retrieved.
static double getUserDouble(string prompt) {
	while (true) {
		cout << applyInset(prompt); // Prompt is displayed with padding apllied at the beginning.
		string input;
		cin >> input;
		if (isDouble(input)) { // Executes if the method "isDouble" returns true for the user's input string.
			return stod(input); // Converts user inpt to a double type and returns it.
			cin.clear(); // Clears the input buffer.
		}
		else {
			cout << applyInset("Invalid input. Please enter a valid value\n\n"); // Error handling message displayed to user.
		}
	}
}

// This method loops until the user provides valid input. The prompt is printed and then user input is collected via cin and compared to the validInts string to ensure invalid characters are not included. Then the valid int is returned.
static int getUserInt(string prompt, string validInts, int padding) {
	while (true) {
		cout << string(padding, ' ') << prompt; // The prompt is displayed to the user with padding applied at the beginning equal to the method's padding parameter's value.
		string input;
		cin >> input; // User input is collected through cin.
		if (isValidInput(input, validInts)) { // The user input is compared against the string validInts using the isValidInput() method to validate. If any un-allowed characters are found, false is returned.
			return stoi(input); // If the input is valid the user's string is converted to an int and returned.
			cin.clear(); // The input buffer is cleared.
		}
		else {
			if (validInts == "0123456789") { // Error message when all numbers are allowed and a non-number is detected in the user's response.
				cout << "Invalid input. Please enter numbers only\n\n";
			}
			else { // Formatted error handling messages based on which numbers are allowed.
				if (validInts.length() == 2) { // Error message when only 2 numbers are allowed.
					cout << string(padding, ' ') << "Invalid input. Please enter the numbers " << validInts.at(0) << " or " << validInts.at(1) << " only\n\n";
				}
				else { // Error message when multiple numbers are allowed. This iterates through the string validInts and prints its characters in order with commas or the word "or" depending upon their position in the string.
					cout << string(padding, ' ') << "Please enter ";
					for (int i = 0; i < validInts.length(); i++) {
						if (i < validInts.length() - 2) {
							cout << validInts[i] << ", ";
						}
						else if (i == validInts.length() - 2) {
							cout << validInts[i] << ", or ";
						}
						else {
							cout << validInts[i];
						}
					}
					cout << " only\n\n";
				}
			}
		}
	}
}

// Method to append commas after every third digit to the left of the decimal in a string of numbers "s".
string formatWithCommas(string s) { // Iteration starts at the end of the string and works backwards.
	bool periodFound = false; // Once the period is found, this bool's value becomes true;
	int counter = 0; // This is used to determine every third character after a period or comma.
	if (s.find(".") == string::npos) { // This appends a period and 2 zeroes at the end of the string if no period is found using string.find.
		s.insert(s.length() - 1, ".00");
	}
	for (size_t i = s.length() - 1; i > 0; --i) {
		if (periodFound) { // This ensures that the counter only increments after iteration has proceeded beyond the period.
			++counter;
		}
		if (s.at(i) == '.') { // Sets periodFound to true if periodFound is false and a period is found in the string. Otherwise, it replaces additional periods with empty characters.
			if (!periodFound) {
				periodFound = true;
			}
			else {
				s.replace(s.at(i), s.at(i + 1), "");
			}
		}
		if (counter == 3) { // Inserts a comma whenever the counter reaches 3 and resets the counter.
			counter = 0;
			s.insert(i, ",");
		}
	}
	return s;
}

// Method to convert a double to string and give it "precision" number of decimal places, and commas after every third digit left of the decimal.
string formatDouble(double value, int precision) {
	value = round(value * 100.0) / 100.0;
	stringstream stream;
	stream << fixed << setprecision(precision) << value;
	return formatWithCommas(stream.str());
}

// Method to create string of (width) length and to apply (fill) characters to the remaining spaces at the beginning and end of the string. Then (inset) characters of padding are appended to the beginning of the string.
static string paddedTextWithFill(int inset, string text, char fill, int width) {

	size_t padding = (width - text.length()) / 2;
	string value = string(padding, fill) + text + string(padding, fill);
	while (value.length() < width) {
		value = value + string(1, fill);
	}
	return applyInset(inset, value);
}

// Method to apply padding between n number of strings, which are passed via the (vector <string> strings) parameter. The total number of characters in all strings are added and then the reamining spaces in (width) 
// are divided up into (strings.size() + 1) spaces. Then a string is created that alternates between appending the divided spaces and the elements within strings to create an evenly spaced layout.
string tableRow(int padding, vector <string> strings, int width) {
	size_t availableSpace = width;
	for (int i = 0; i < strings.size(); ++i) {
		availableSpace -= strings.at(i).length();
	}
	size_t spaces = availableSpace / (strings.size() + 1);
	string result = applyInset(padding, "");
	for (int i = 0; i < strings.size(); ++i) {
		result += string(spaces, ' ') + strings.at(i);
	}
	return result;
}

// Method to print a string that starts with the defaultPadding (via applyInset()) and then an asterisk character, then 10 spaces and a string s, followed by 38 - s.length() - 10 spaces, and lastly another asterisk character.
// This provides the format that I desired for the menu. Alterations to the width of the rows can be made by changing the 38 and the 10.
string centerMenuItem(string s) {
	size_t remainder = 38 - s.length() - 10;
	return "\n" + applyInset("*" + string(10, ' ') + s + string(remainder, ' ') + "*");
}

// Method for spacing the values for each table row in the console's output. This method attempts to space the elements evenly.
static string splitValues(vector <string> values) {
	for (int i = 0; i < values.size(); i++) {
		values[i].erase(remove_if(values[i].begin(), values[i].end(), ::isspace), values[i].end());
	}
	return string(8, ' ') + values[0] + string(26 - values[0].length() - 12, ' ') + values[1] + string(44 - 8 - values[0].length() - (26 - values[0].length() - 12) - values[1].length(), ' ') + values[2];
}

// Method to print a heading for the data input view. The output depends on the (confirm) parameter which is representative of whether the user has already submitted values in the session. 
static void printDataInputHeader(bool confirm) {
	cout << endl << applyInset(string(40, '*')) << endl;
	if (!confirm) {
		cout << paddedTextWithFill(defaultPadding, "Data Input", '*', 40) << endl << endl;
	}
	else {
		cout << paddedTextWithFill(defaultPadding, "Verify Data", '*', 40) << endl << endl;
	}
}

// Method to gather values for a new investmentData object from the user, with error handling and input validation built in. Once all valid values have been collected, the new InvestmentData object is returned.
InvestmentData gatherUserInfo() {
	InvestmentData investmentData;
	while (true) {
		printDataInputHeader(false);
		investmentData.setStartingInvestment(getUserDouble("Initial Investment Amount: $"));
		investmentData.setMonthlyContribution(getUserDouble("Monthly Contribution: $"));
		investmentData.setYearlyInterestRate(getUserDouble("Yearly Interest Rate: "));
		investmentData.setTerm(getUserInt("Number of Years: ", "0123456789", defaultPadding));
		break;
	}
	return investmentData;
}

// Method to collect a user's selection from a menu of 4 options. Any selections not equal to 1, 2, 3, or 4 result in an error message and a prompt to try again.
int userSelection(InvestmentData investmentData) {
	return getUserInt("\n\n" + paddedTextWithFill(defaultPadding, "", '*', 40) + "\n" + paddedTextWithFill(defaultPadding, " Select an option: ", '*', 40) + "\n" + applyInset("*" + string(38, ' ') + "*") + centerMenuItem("(1)Monthly Report") +
		centerMenuItem("(2)Yearly Report") + centerMenuItem("(3)Edit Info") + centerMenuItem("(4)Exit Program ") + "\n" + string(defaultPadding, ' ') + "*" + string(38, ' ') + "*\n" + paddedTextWithFill(defaultPadding, "", '*', 40) + "\n", "1234", defaultPadding);
}

// Method to print the investment values of the user's data for both monthly and yearly increments, with contributions and without contributions.
void printReport(InvestmentData data, bool hasContributions, bool isMonthly) {
	string choice = "Without Contributions"; // Default value.
	string frequency = "Year"; // Default value.
	if (hasContributions) {
		choice = "With Contributions"; // Default value changed based on the (hasContributions) parameter.
	}
	if (isMonthly) {
		frequency = "Month"; // Default value changed based on the (isMonthly) parameter.
	}
	// The header and specifiers are printed out to start the table.
	cout << endl << endl << paddedTextWithFill(defaultPadding - 10, frequency + "ly Balance and Interest " + choice, ' ', 62) << endl;
	cout << paddedTextWithFill(defaultPadding - 10, "", '=', 62) << endl;
	cout << tableRow(defaultPadding - 10, { frequency, frequency + " End Balance", "Earned Interest" }, 62) << endl;
	cout << paddedTextWithFill(defaultPadding - 10, "", '-', 62) << endl;
	int elements = data.getTerm(); // The default elements value is set to the number of years assigned to the getTerm() varaiable within "data".
	if (isMonthly) {
		elements *= 12; // If (isMonthly), the number of elements is multiplied by 12 to represent the number of months instead.
	}
	double value = data.getStartingInvestment(); // Value is incremented after each loop and is used to represent the value of the investment. The starting value is assigned as the getStartingInvestment() value from "data". 
	int counter = 0; // An int variable called counter is used to count each element, and represents the number of months or years elapsed for each row in the table.
	while (elements > 0) { // Iterates until the number of years or months has been exhausted.
		++counter; // Increments to count the total years or months iterated through.
		if (isMonthly) { // Executes if the isMonthly parameter is true.
			double interest = value * ((data.getYearlyInterestRate() / 100) / 12); // Interest is calculated by dividing the yearly rate by 100, then by 12 months and then multiplied by the account's (value).
			if (hasContributions) { // The calculation is made with the monthly contributions included if the (hasContributions) parameter is equal to true.
				// Values are output for month, month end balance, and interest earned this period.
				cout << applyInset(defaultPadding - 10, splitValues({ to_string(counter), "$" + formatDouble(value + interest + data.getMonthlyContribution(), 2), "$" + formatDouble(interest, 2) })) << endl;
				value = value + interest + data.getMonthlyContribution(); // The value of the (value) variable is updated in each iteration to prepare for subsequent calculations.
			}
			else { // The calculation is made without the monthly contribution included.
				// Values are output for month, month end balance, and interest earned this period.
				cout << applyInset(defaultPadding - 10, splitValues({ to_string(counter), "$" + formatDouble(value + interest, 2), "$" + formatDouble(interest, 2) })) << endl;
				value = value + interest; // The value of the (value) variable is updated in each iteration to prepare for subsequent calculations.
			}
		}
		else { // Executes if the isMonthly parameter is false.
			double interest = value * ((data.getYearlyInterestRate() / 100)); // Interest is calculated by dividing the yearly rate by 100, then by 12 months and then multiplied by the account's (value).
			if (hasContributions) { // The calculation is made with the monthly contributions included if the (hasContributions) parameter is equal to true. These contributions are multiplied by 12 to represent their yearly value.
				// Values are output for year, year end balance, and interest earned this period.
				cout << applyInset(defaultPadding - 10, splitValues({ to_string(counter), "$" + formatDouble(value + interest + data.getMonthlyContribution() * 12, 2), "$" + formatDouble(interest, 2) })) << endl;
				value = value + interest + data.getMonthlyContribution() * 12; // The value of the (value) variable is updated in each iteration to prepare for subsequent calculations.
			}
			else { // The calculation is made without the monthly contribution included.
				// Values are output for year, year end balance, and interest earned this period.
				cout << applyInset(defaultPadding - 10, splitValues({ to_string(counter), "$" + formatDouble(value + interest, 2), "$" + formatDouble(interest, 2) })) << endl;
				value = value + interest; // The value of the (value) variable is updated in each iteration to prepare for subsequent calculations.
			}
		}
		--elements; // elements is decremented so that the loop will end when the elements have all been iterated over.
	}
}