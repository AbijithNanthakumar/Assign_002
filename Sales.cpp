#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;


bool allitems = true;

void AddItems() {
    string filename = "sales.csv";

    // Check if file exists to avoid rewriting header
    bool fileExists = filesystem::exists(filename);

    fstream file(filename, ios::app | ios::out);

    if (!fileExists) {
        file << "Unit Price Date,Sale ID,Item Name,Item Quantity,Unit Price\n";
    }

    while (true) {
        string date, itemName, isallitems;
        int saleID, quantity, unitPrice;

        cout << "\nEnter Unit Price Date (e.g., ): ";
        getline(cin, date);


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
