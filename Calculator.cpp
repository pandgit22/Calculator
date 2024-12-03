#include <iostream>
#include <vector>
#include "exprtk.hpp" // External library from https://github.com/ArashPartow/exprtk

using namespace std;

// ANSI Escape Codes to color the console

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Function to perform calculations
// This function asks the user for a mathematical expression, evaluates it using ExprTk, and saves the result in history
void performCalculation(vector<string>& history) {
    string expression; // To store the user's input expression

    // Prompt the user to enter a mathematical expression
    cout << BLUE << "Enter a mathematical expression (for example, " << WHITE << "3+5*(2-8)" << BLUE << "): " << RESET;
    cin.ignore(); // Clear the input buffer to prevent leftover input from interfering
    getline(cin, expression); // Read the full expression from the user

    // Define the ExprTk objects
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_t expr; // Create an expression object
    parser_t parser;   // Create a parser object

    // Try to compile (parse) the user's input expression
    if (parser.compile(expression, expr)) {
        double result = expr.value(); // Evaluate the parsed expression
        cout << YELLOW << "Result: " << GREEN << result << RESET << endl; // Display the result in green
        history.push_back(expression + " = " + to_string(result)); // Save the expression and result to history
    }
    else {
        // If the expression is invalid, display an error message in red
        cout << RED << "Invalid expression! Please try again." << RESET << endl;
    }
}

// Function to display the history of calculations
// This function prints all previously entered calculations stored in the history vector
void displayHistory(const vector<string>& history) {
    if (history.empty()) {
        // If no calculations have been performed yet, notify the user
        cout << RED << "\nNo calculations yet!" << RESET << endl;
        return; // Exit the function early
    }

    // Display the header for the history section
    cout << CYAN << "\nCalculation History:" << RESET << endl;

    int counter = 1; // Counter for numbering the history entries
    for (const string& record : history) {
        // Alternate colors for better readability
        if (counter % 2 == 0) {
            cout << YELLOW << counter << ". " << record << RESET << endl; // Yellow for even entries
        }
        else {
            cout << counter << ". " << record << endl; // Default color for odd entries
        }
        counter++; // Increment the counter
    }
}

// Main function
// This function implements the main menu and handles user interactions
int main() {
    vector<string> history; // Vector to store the history of calculations
    int choice; // Variable to store the user's menu choice

    do {
        // Display the main menu
        cout << CYAN << "\n===================" << endl;
        cout << "  Calculator Menu  " << endl;
        cout << "===================" << RESET << endl;
        cout << GREEN << "1. Perform Calculation\n" << RESET;
        cout << YELLOW << "2. View History\n" << RESET;
        cout << RED << "3. Exit\n" << RESET;
        cout << "Choose an option: ";

        // Validate the user's input
        if (!(cin >> choice)) { // If the input is not a valid number
            cin.clear(); // Clear the input error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << RED << "Invalid input! Please enter a number between 1 and 3." << RESET << endl;
            continue; // Restart the menu loop
        }

        // Process the user's choice
        switch (choice) {
        case 1:
            performCalculation(history); // Call the function to perform a calculation
            break;
        case 2:
            displayHistory(history); // Call the function to display the history
            break;
        case 3:
            // Display a farewell message and exit the loop
            cout << MAGENTA << "============" << endl;
            cout << "  Exiting.  " << endl;
            cout << "============" << RESET << endl;
            break;
        default:
            // Handle invalid menu choices
            cout << RED << "Invalid choice. Please enter a number between 1 and 3." << RESET << endl;
        }
    } while (choice != 3); // Repeat until the user chooses to exit

    return 0;
}