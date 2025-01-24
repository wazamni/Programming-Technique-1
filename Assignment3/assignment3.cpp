// NAME 1: SALWA NAJIHA BINTI ALI BADRON A24CS0183
// NAME 2: WAN AMNI ZAHIRAH BINTI WAN AHMAD NAZARUDDIN A24CS0208
// DATE OF COMPLETION: 18 JANUARY 2025

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Task 1: Define a Structured Data Type
struct ReliefCenter {
    string code;
    string name;
    string state;

    int evac[12];
    int res[12];
    double exp[12];

    int totalevac = 0;
    int totalres = 0;

    double totalexp = 0.0;
    double averageresperevac = 0.0;
    double expperevac = 0.0; 
};

// Task 2: Read and Validate Input Files
int validatefiles(const string file[], int filecount) {
    for (int i = 0; i < filecount; i++) {
        ifstream inputFile (file[i]);
        if (!inputFile) {
            cout << "Error: File " << file[i] << " not found. \n";
            return 0;
        }
    }
    return 1;
}

void readdata(ReliefCenter center[], int& centercount, const string& centerfile, const string& evacfile, const string& resfile, const string& expfile) {
    ifstream centerstream(centerfile), evacstream(evacfile), resstream(resfile), expstream(expfile);
    string line;
    centercount = 0;

    while (getline(centerstream, line)) {
        center[centercount].code = line;
        centercount++;
    }

    for (int i = 0; i < centercount; i++) {
        for (int j = 0; j < 12; j++) {
            evacstream >> center[i].evac[j];
            resstream >> center[i].res[j];
            expstream >> center[i].exp[j];
        }
    }
} 

// Task 3: Determine Relief Center Details
void centerdetails(ReliefCenter center[], int centercount) {
    for (int i = 0; i < centercount; i++) {
        if (center[i].code == "TGR101") {
            center[i].name = "Tanjung Relief Center";
            center[i].state = "Selangor";
        }
        else if (center[i].code == "JHR202") {
            center[i].name = "Johor Relief Center";
            center[i].state = "Johor";
        }
        else if (center[i].code == "KLT303") {
            center[i].name = "Kelantan Relief Center";
            center[i].state = "Kelantan";
        } 
        else if (center[i].code == "TRG404") {
            center[i].name = "Terengganu Relief Center";
            center[i].state = "Terengganu";
        } 
        else if (center[i].code == "SGR505") {
            center[i].name = "Sungai Relief Center";
            center[i].state = "Perak";
        } 
        else if (center[i].code == "KDU606") {
            center[i].name = "Kudat Relief Center";
            center[i].state = "Sabah";
        } 
        else if (center[i].code == "KCH707") {
            center[i].name = "Kuching Relief Center";
            center[i].state = "Sarawak";
        } 
    }
}

// Task 4: Perform Data Analysis
void calculatetotal(ReliefCenter center [], int centercount) {
    for (int i = 0; i < centercount; i++) {
        for (int j = 0; j < 12; j++) {
            center[i].totalevac += center[i].evac[j];
            center[i].totalres += center[i].res[j];
            center[i].totalexp += center[i].exp[j];
        }

        if (center[i].totalevac > 0) {
            center[i].averageresperevac = static_cast<double>(center[i].totalres) / center[i].totalevac;
            center[i].expperevac = center[i].totalexp / center[i].totalevac;
        }
    }
}

// Task 5: Generate a Flood Relief Report
void generatereport(const ReliefCenter center[], int centercount) {
    cout << fixed << setprecision(2);
    cout << left << setw(12)<< "CENTER CODE"
                 << setw(25) << "CENTER NAME"
                 << setw(10) << "STATE" 
                 << setw(13) << "ANNUAL EVAC"
                 << setw(13) << "ANNUAL RES"
                 << setw(18) << "ANNUAL EXP (RM)"
                 << setw(15) << "AVG RES/EVAC" 
                 << setw(14) << "EXP/EVAC (RM)" << endl;
    cout << string(119, '-') << endl;

    double totalexp = 0;
    string highestevaccenter, lowestexpcenter;
    int highestevaccount = 0;
    double lowestexp = 1e9; // Large value
    int monthlytotal[12] = {0};

    for (int i = 0; i < centercount; i++) {
        cout << left << setw(12) << center[i].code 
             << setw(25) << center[i].name 
             << setw(13) << center[i].state 
             << setw(12) << center[i].totalevac
             << setw(14) << center[i].totalres 
             << setw(18) << center[i].totalexp 
             << setw(15) << center[i].averageresperevac 
             << setw(10) << center[i].expperevac << endl;

        totalexp += center[i].totalexp;

        if (center[i].totalevac > highestevaccount) {
            highestevaccount = center[i].totalevac;
            highestevaccenter = center[i].name + " (" + center[i].state + ")";
        }

        if (center[i].totalexp < lowestexp) {
            lowestexp = center[i].totalexp;
            lowestexpcenter = center[i].name + " (" + center[i].state + ")";
        }

        for (int j = 0; j < 12; ++j) {
            monthlytotal[j] += center[i].evac[j];
        }
    }

    cout << string(119, '-') << endl;
    cout << "\n\nSUMMARY: "  << endl;
    cout << "Total Expenditures: RM" << totalexp << endl;
    cout << "Center with Highest Evacuees: " << highestevaccenter << endl;
    cout << "Center with Lowest Expenditures: " << lowestexpcenter << endl;

    int maxmonth = 0, minmonth = 0;
    for (int i = 1; i < 12; ++i) {
        if (monthlytotal[i] > monthlytotal[maxmonth]) maxmonth = i;
        if (monthlytotal[i] < monthlytotal[minmonth]) minmonth = i;
    }

    cout << "Month with Highest Evacuees: Month " << (maxmonth + 1) << " (" << monthlytotal[maxmonth] << " evacuees)" << endl;
    cout << "Month with Lowest Evacuees: Month " << (minmonth + 1) << " (" << monthlytotal[minmonth] << " evacuees)" << endl;
}

// Main Function
int main() {
    const string file[] = {"centers.txt", "evacuees.txt", "resources.txt", "expenditures.txt"};
    const int filecount = 4;

    if (!validatefiles(file, filecount)) {
        return 1;
    }

    ReliefCenter center[100];
    int centercount = 0;
    readdata(center, centercount, file[0], file[1], file[2], file[3]);

    centerdetails(center, centercount);
    calculatetotal(center, centercount);
    generatereport(center, centercount);

    system ("Pause");
    return 0;
}

