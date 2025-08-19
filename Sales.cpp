#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;


bool allitems = true;


#include <string>
using namespace std;

bool isValidDateFormat(const string& date) {
    // Must be exactly 10 characters: YYYY/MM/DD
    if (date.length() != 10) return false;

    // Check slashes at correct positions
    if (date[4] != '/' || date[7] != '/') return false;

    // Check digits in YYYY, MM, DD
    for (int i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    return true;
}


void AddItems() {
    string filename = "sales.csv";

    bool fileExists = filesystem::exists(filename);

    fstream file(filename, ios::app | ios::out);

    if (!fileExists) {
        file << "Unit Price Date,Sale ID,Item Name,Item Quantity,Unit Price\n";
    }

    while (true) {
        string date, itemName, isallitems;
        int saleID, quantity, unitPrice;

        cout << "\nEnter Unit Price Date YYYY/MM/DD: ";
        getline(cin, date);
        if(!isValidDateFormat(date))
        {
            cout << "Invalid Format";
            return;
        }
        
        cout << "Enter Sale ID: ";
        cin >> saleID;
        cin.ignore();

        cout << "Enter Item Name: ";
        getline(cin, itemName);

        cout << "Enter Item Quantity: ";
        cin >> quantity;
        cin.ignore();

        cout << "Enter Unit Price: ";
        cin >> unitPrice;
        cin.ignore();

        // Write to CSV
        file << date << "," << saleID << "," << itemName << "," << quantity << "," << unitPrice << "\n";

        cout << "Is all items entered? (yes/y to stop): ";
        getline(cin, isallitems);

        if (isallitems == "yes" || isallitems == "y") {
            break;
        }
    }

    file.close();
    cout << "\n✅ Data successfully written to sales.csv\n";
}

int main() {
    
    AddItems();
    return 0;
}
