// Fancy Interest Calculator

#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

double iniAmount;
double interestRate;
int timePeriod;
vector<vector<long double>> interestTable;

union Interest {
    double rate;
    int percentage;
};

enum class InterestType {
    Rate,
    Percentage
};

long double iCalc(double amount, double rate, int noYear, InterestType type, char interestTypeChar) {
    if (InterestType::Rate == type) {
        if (interestTypeChar == 'C' || interestTypeChar == 'c') {
            double baseAm = amount;
            for(int i = 1; i < noYear; ++i) {
                baseAm *= (1 + rate);
            }
            return baseAm * rate;
        } else {
            return amount * rate;
        }
    } else {
        return 1;
    }
}

long double iCalc(double amount, int percentage, int noYear, InterestType type, char interestTypeChar) {
    if (InterestType::Percentage == type) {
        if (interestTypeChar == 'C' || interestTypeChar == 'c') {
            double baseAm = amount;
            for(int i = 1; i < noYear; ++i) {
                baseAm *= (1 + (percentage / 100.0));
            }
            return baseAm * (percentage / 100.0);
        } else {
            return amount * (percentage / 100.0);
        }
    } else {
        return 1;
    }
}

int main() {
    unique_ptr<Interest> interest = make_unique<Interest>();
    unique_ptr<InterestType> interestType = make_unique<InterestType>(InterestType::Percentage);

    cout << "Welcome to the Fancy Interest Calculator!" << endl;
    cout << "This program will help you calculate the annual interest over certain years on your insurance." << endl;
    cout << "=========================================================" << endl;
    cout << "Please enter the initial amount of insurance: $";
    cin >> iniAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Please enter the anuual interest rate (Decimal for rate, integer for pencentage): ";
    string iBuffer;
    getline(cin, iBuffer);
    if(iBuffer.empty()) {
        cout << "No input provided. Exiting..." << endl;
        return 1;
    }

    cout << "Please enter the time period in years: ";
    cin >> timePeriod;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Is your product Compound Interest or Simple Interest? (C/S): ";
    char interestTypeChar;
    cin >> interestTypeChar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Processing... please wait." << flush;
    this_thread::sleep_for(1s);
    cout << "\r                           \r";
    cout << "=========================================================\n" << endl;

    for(char c : iBuffer) {
        if(c == '.') {
            *interestType = InterestType::Rate;
        }
    }
    if(*interestType == InterestType::Rate) {
        interest->rate = stod(iBuffer);
    } else {
        interest->percentage = stoi(iBuffer);
    }

    unique_ptr<vector<vector<long double>>> interestData = make_unique<vector<vector<long double>>>(timePeriod, vector<long double>(1));
    if(*interestType == InterestType::Rate) {
        for(int i = 0; i < timePeriod; i++) {
            (*interestData)[i][0] = iCalc(iniAmount, interest->rate, i + 1, InterestType::Rate, interestTypeChar);
            cout << "Year " << i + 1 << ": $" << (*interestData)[i][0] << endl;
        }
    } else {
        for(int i = 0; i < timePeriod; i++) {
            (*interestData)[i][0] = iCalc(iniAmount, interest->percentage, i + 1, InterestType::Percentage, interestTypeChar);
            cout << "Year " << i + 1 << ": $" << (*interestData)[i][0] << endl;
        }
    }

    unique_ptr<long double> totalInterest = make_unique<long double>(0);
    for(const auto& row : *interestData) {
        for(const auto& value : row) {
            *totalInterest += value;
        }
    }

    cout << "You total interest is" << " $" << *totalInterest << "." " Net asset is $" << iniAmount + *totalInterest << ".\n" << endl;
    cout << "=========================================================" << endl;
    cout << "Thank you for using the Fancy Interest Calculator!\nPress Enter to exit...";

    cin.get();
    return 0;
    }