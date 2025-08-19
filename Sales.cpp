#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool allitems = true;

#include <string>
#include <filesystem>
using namespace std;



// date nomal validation:::::
bool isValidDateFormat(const string &date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '/' || date[7] != '/')
        return false;

    // Check digits in YYYY, MM, DD
    for (int i = 0; i < date.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    return true;
}

// View.......
void View(const string& filename)
{
    fstream file(filename);
    string line;
    if (!file)
    {
        cout << "Error Opening the file.\n";
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ','))
        {
            cout << cell << "\t";
        }
        cout << "\n";
    }

    file.close();
    return;
}

// Addd items:::::
void AddItems()
{
    string filename = "sales.csv";

    bool fileExists = filesystem::exists(filename);

    fstream file(filename, ios::in | ios::app | ios::out);

    if (!fileExists)
    {
        file << "Unit Price Date,Sale ID,Item Name,Item Quantity,Unit Price\n";
    }

    while (true)
    {
        string date, itemName, isallitems;
        int saleID, quantity, unitPrice;

        cout << "\nEnter Unit Price Date YYYY/MM/DD: ";
        getline(cin, date);
        if (!isValidDateFormat(date))
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

        if (isallitems == "yes" || isallitems == "y")
        {
            break;
        }
    }

    cout << "\n Data successfully written to sales.csv\n";
    View("sales.csv");
    cout <<"return st";
}

int main()
{

    AddItems();
    string updateOrdelete;
    cout << "Do you want to update or delete?";
    cin >> updateOrdelete;
    return 0;
}
