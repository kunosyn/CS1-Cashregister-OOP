/*
    Written by: kunostaken
    Written on: 5/20/2022
    
    Project name: Cash Register Program
    Project description: A program to simulate a cash register to practice OOP.
*/


// IMPORTS //
#include <iostream>
#include "cash_register.hpp"

// NAMESPACES //
using namespace std;

// FUNCTIONS //
void startDay(void);

void printMenu(void);

void labelInterface(void);
void mainInterface(void);
void itemInterface(void);

// GLOBAL VARIABLES //
CashRegister cashRegister; // Make cash register global scope so we don't need it as a function parameter.
bool isDayOnGoing = true, isTransactionActive = true;
string input;

// MAIN FUNCTION //
int main()
{
    // Add Coupon codes below
    cashRegister.addCoupon("EASports", 0.2); // 20 Percent discount with coupon code "EASports".
    cashRegister.addCoupon("C++", 0.5); // 50 Percent discount with coupon code "C++".
    cashRegister.addCoupon("Free", 1); // 100 Percent discount with coupon code "Free".
    cashRegister.addCoupon("ThisIsACoupon", 0.1); // 10 Percent discount with coupon code "ThisIsACoupon".
    
    startDay();
    return 0;
}

// DEFINING FUNCTIONS //

void labelInterface(void)
{
    cout << string(30, '-') << endl;
    cout << "\tCash Register Interface" << endl;
    cout << string(30, '-') << endl << endl;
}

void printMenu(void)
{        
    labelInterface();
    
    cout << string(30, '-') << endl; 
    cout << "\t\t\tItems" << endl;
    cout << string(30, '-') << endl << endl;

    cout << setw(45) << left << "[G] Grapes:\t\t\t$ 3.00" << endl << "[C] Celery:\t\t\t$ 5.00" << endl << "[J] Jelly\t\t\t$ 10.15" << endl << "[S] Steak:\t\t\t$ 25.10" << endl;
    cout << string(30, '-') << endl;
}
void startDay(void)
{    
    do {
        cashRegister.clearItems();
        mainInterface();
    } while(isDayOnGoing);
}

void mainInterface(void)
{
    system("cls");
    labelInterface();
        
    cout << endl << "[1] Start New Transaction." << endl << "[2] Display Sales Statistics." << endl << "[3] Clear Sales Statistics." << endl << "[4] Close Register." << endl;
    
    cout << "> ";
    cin >> input;
    
    int choice = stoi(input);
    
    if (choice == 1)
    {
        system("cls");
        itemInterface();
    }
    else if (choice == 2)
    {
        system("cls");
        labelInterface();
    
        cout << string(30, '-') << endl;
        cout << "\t\tSales Today" << endl;
        cout << string (30, '-') << endl;    
        cout << endl << "[*] Sales Today: " << cashRegister.getSalesCount() << endl;
        cout << "[*] Profit Made Today: $" << cashRegister.getSalesTotal() << endl;
    
        cout << endl << string(30, '-') << endl;
        cashRegister.listSales();

        system("pause");
    }
    else if (choice == 3)
    {
        cashregister.resetSales();
    
        system("cls");
        labelInterface();
    
        cout << endl << "[*] Cleared sales statistics." << endl;
        system("pause");
    }
    else if (choice == 4)
    {
        system("cls");
        labelInterface();
    
        cout << string(30, '-') << endl;
        cout << "\t\tSales Today" << endl;
        cout << string (30, '-') << endl;    
        cout << endl << "[*] Sales Today: " << cashRegister.getSalesCount() << endl;
        cout << "[*] Profit Made Today: $" << cashRegister.getSalesTotal() << endl;
    
        cout << endl << string(30, '-') << endl;
        cashRegister.listSales();

        isTransactionActive = false;
        isDayOnGoing = false;
    }
}

void itemInterface(void)
{
    cashregister.clearItems();
    
    do {
        bool isBulk = false;
        string couponCode = "", chosenItem;
            
        int amount;
        double amountDue;
            
        system("cls");
        printMenu();
            
        cout << endl << "[!] Please enter the item you'd like to select." << endl << "> ";
        cin >> input;
    
        input[0] = tolower(input[0]);
            
        if (input == "g")
        {
            amountDue = 3;   
            chosenItem = "Grapes";
        } 
        else if (input == "c")
        {
            amountDue = 5;
            chosenItem = "Celery";
        } 
        else if (input == "j")
        {
            amountDue = 10.15;
            chosenItem = "Jelly";
        }
        else if (input == "s")
        {
            amountDue = 25.10;
            chosenItem = "Steak";
        }
        else
        {
            continue;
        }
    
        system("cls");
        labelInterface();
        
        cout << endl;
            
        cout << "[?] Would you like multiple " << chosenItem << "? (Yes/No)" << endl;
            
        cout << "> ";
        cin >> input;
    
        input[0] = tolower(input[0]);
        if (input == "yes" || input == "y")
        {
            cout << endl << "[?] How much of this item would you like to purchase?" << endl;
    
            cout << "> ";
            cin >> input;
    
            amount = stoi(input);
            isBulk = true;
        }
        else if (input != "no" && input != "n")
        {
            continue;
        }
    
        system("cls");
        labelInterface();
            
        cout << endl;
        cout << "[?] Would you like to apply a Coupon Code to this item? (Yes/No)" << endl;
    
        cout << "> ";
        cin >> input;
    
        input[0] = tolower(input[0]);
    
        if (input == "yes" || input == "y")
        {
            cout << endl << "[!] Please enter your coupon code." << endl;
                
            cout << "> ";
            cin >> input;
    
            if (cashRegister.getCouponDiscount(input) == 0)
             {
                cout << endl <<"[*] Invalid Coupon Code, exiting Coupon Process." << endl;
                system("pause");
            }
            else
            {
                couponCode = input;
            }
        }
    
        system("cls");
        labelInterface();
            
        if (isBulk)
        {
            if (couponCode == "")
            {
                cashRegister.addItems(amountDue, amount);
            }
            else
            {
                cashRegister.addItems(amountDue, amount, couponCode);
                system("pause");
            }
        }
        else
        {
            if (couponCode == "")
            {
                cashRegister.addItem(amountDue);
            }
            else
            {
                cashRegister.addItem(amountDue, couponCode);
                system("pause");
            }
        }

        system("cls");
        labelInterface();
    
        cout << string(30, '-') << endl << "\t\tCurrent Cart" << endl << string (30, '-') << endl;
    
        cout << endl << "[*] Items in Cart: " << cashRegister.getItemCount() << endl;
        cout << "[*] Cost of Cart: " << cashRegister.getCurrentTotal() << endl;
    
        cout << endl << string(30, '-') << endl;
        cashRegister.displayAll();
            
        cout << endl << "[?] Would you like to add another item to your cart? (Yes/No)" << endl;
    
        cout << "> ";
            
        cin >> input;
        input[0] = tolower(input[0]);
    
        if (input == "no" || input == "n")
        {
            system("cls");
            labelInterface();
    
            cout << string(30, '-') << endl << "\t\tCurrent Cart" << endl << string (30, '-') << endl;
    
            cout << endl << "[*] Items in Cart: " << cashRegister.getItemCount() << endl;
            cout << "[*] Cost of Cart: " << cashRegister.getCurrentTotal() << endl;
    
            cout << endl << string(30, '-') << endl;
            cashRegister.displayAll();

            system("pause");
            break;
        }
        
    } while (isTransactionActive);
}
