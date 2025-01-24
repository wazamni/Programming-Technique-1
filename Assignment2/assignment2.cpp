#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX 50
using namespace std;

void readInput(string householdName[], string utilityType[], double monthlyBill[], char status[], int &num) {
    ifstream inputfile;
    inputfile.open("input.txt");
    if (!inputfile) {
        cout << "Error! File not found." << endl;
        return;
    }
    num = 0;
    while (!inputfile.eof()) {
        getline(inputfile, householdName[num], ',');
        inputfile >> utilityType[num] >> monthlyBill[num] >> status[num];
        inputfile.ignore(10, '\n'); // To ignore the newline character
        num++;
    }
    inputfile.close();
}

double calculateLateFee(string &utilityType, char status) {
    if (status == 'N') return 0.0;
    if (utilityType == "Electricity") return 20.00;
    if (utilityType == "Water") return 10.00;
    if (utilityType == "Internet") return 15.00;
    return 0.0;
}

void calculateTotalPayment(double monthlyBill[], double lateFee[], double totalPayment[], int num) {
    for (int i = 0; i < num; i++) {
        totalPayment[i] = monthlyBill[i] + lateFee[i];
    }
}

void displayOutput(string householdName[], string utilityType[], double monthlyBill[], double lateFee[], double totalPayment[], int num) {
    cout << left << setw(20) << "Household Name"
         << setw(15) << "Utility Type"
         << setw(20) << "Monthly Bill (MYR)"
         << setw(15) << "Late Fee (MYR)"
         << setw(20) << "Total Payment (MYR)" << endl;
    cout << string(90, '-') << endl;

    for (int i = 0; i < num; i++) {
        cout << left << setw(20) << householdName[i]
             << setw(15) << utilityType[i]
             << right << setw(12) << fixed << setprecision(2) << monthlyBill[i]
             << setw(15) << lateFee[i]
             << setw(20) << totalPayment[i] << endl;
    }
}

void displayAnalysis(string householdNames[], string utilityType[], double totalPayment[], char status[], int num) {
    int lateWater = 0, lateInternet = 0, lateElectric = 0;
    double totalWater = 0.0, totalInternet = 0.0, totalElectric = 0.0;
    int countWater = 0, countInternet = 0, countElectric = 0;
    double allTotal = 0.0;
    int totalLateFees = 0;
    int highestPayment = 0, lowestPayment = 0;

    for (int i = 0; i < num; i++) {
        if (status[i] == 'Y') {
            totalLateFees++;
            if (utilityType[i] == "Water") lateWater++;
            else if (utilityType[i] == "Internet") lateInternet++;
            else if (utilityType[i] == "Electricity") lateElectric++;
        }
    }

    for (int i = 0; i < num; i++) {
        if (utilityType[i] == "Water") {
            totalWater += totalPayment[i];
            countWater++;
        } else if (utilityType[i] == "Internet") {
            totalInternet += totalPayment[i];
            countInternet++;
        } else if (utilityType[i] == "Electricity") {
            totalElectric += totalPayment[i];
            countElectric++;
        }
    }
    
    double averageWater = totalWater / countWater;
    double averageInternet = totalInternet / countInternet;
    double averageElectric = totalElectric / countElectric;

    for (int i = 0; i < num; i++) {
        allTotal += totalPayment[i];
        if (totalPayment[i] > totalPayment[highestPayment]) highestPayment = i;
        if (totalPayment[i] < totalPayment[lowestPayment]) lowestPayment = i;
    }

    double percentLateFees = (totalLateFees / (double)num) * 100;

    string mostLateUtility = "Water";
    int mostLateCount = lateWater;

    if (lateInternet > mostLateCount) {
        mostLateUtility = "Internet";
        mostLateCount = lateInternet;
    }

    if (lateElectric > mostLateCount) {
        mostLateUtility = "Electricity";
        mostLateCount = lateElectric;
    }

    cout << "\n\n" << left << setw(15) << "Utility Type"
         << setw(13) << "Households"
         << setw(15) << "Late Payments"
         << setw(22) << "Total Payments (MYR)"
         << setw(25) << "Average Payments (MYR)" << endl;
    cout << string(87, '-') << endl;

    cout << left << setw(15) << "Water"
         << right <<  setw(5) << countWater
         << setw(15) << lateWater
         << setw(20) << fixed << setprecision(2) << totalWater
         << setw(23) << averageWater << endl;

    cout << left << setw(15) << "Internet"
         << right << setw(5) << countInternet
         << setw(15) << lateInternet
         << setw(20) << totalInternet
         << setw(23) << averageInternet << endl;

    cout << left << setw(15) << "Electricity"
         << right << setw(5) << countElectric
         << setw(15) << lateElectric
         << setw(20) << totalElectric
         << setw(23) << averageElectric << endl;

    cout << "\nOverall Total Payments : RM " << allTotal << endl;
    cout << "Overall Average Payment : RM " << allTotal / num << endl;

    cout << "Highest Payment : " << householdNames[highestPayment] << " (MYR "
         << totalPayment[highestPayment] << ") for " << utilityType[highestPayment] << endl;

    cout << "Lowest Payment : " << householdNames[lowestPayment] << " (MYR "
         << totalPayment[lowestPayment] << ") for " << utilityType[lowestPayment] << endl;

    cout << "Percentage of Households with Late Payments: " << fixed << setprecision(1)
         << percentLateFees << "%" << endl;

    cout << "Utility Type with the Most Late Payments: " << mostLateUtility << endl;
}

int main() {
    string householdNames[MAX];
    string utilityType[MAX];
    double monthlyBill[MAX], lateFee[MAX], totalPayment[MAX];
    char status[MAX];
    int num;

    readInput(householdNames, utilityType, monthlyBill, status, num);

    for (int i = 0; i < num; i++) {
        lateFee[i] = calculateLateFee(utilityType[i], status[i]);
    }

    calculateTotalPayment(monthlyBill, lateFee, totalPayment, num);
    displayOutput(householdNames, utilityType, monthlyBill, lateFee, totalPayment, num);
    displayAnalysis(householdNames, utilityType, totalPayment, status, num);
    system("pause");
    return 0;
}
