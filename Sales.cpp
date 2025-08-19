#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
using namespace std;

bool allitems = true;

// Function to split CSV line into tokens
vector<string> split(const string& line, char delimiter = ',') {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to join vector into CSV line
string join(const vector<string>& tokens, char delimiter = ',') {
    string result;
    for (size_t i = 0; i < tokens.size(); i++) {
        result += tokens[i];
        if (i < tokens.size() - 1) result += delimiter;
    }
    return result;
}

void UpdateOrDelete(const string& file){
 
    string salesIdToUpdate;
    cout << "Enter Sales ID to update: ";
    cin >> salesIdToUpdate;

    
    cout << "Do you want to Update or Delete (u or d).\n";
    char upordel;
    cin >> upordel;

    if(upordel=='y'){
        
    }

    
 
    ifstream inFile(file);
    if (!inFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return ;
    }
 
    vector<string> lines;
    string line;
    bool updated = false;
 
    // Read file line by line
    while (getline(inFile, line)) {

        vector<string> row = split(line);
 
        // Assuming SalesID is the first column
        if (!row.empty() && row[0] == salesIdToUpdate) {
            cout << "Current record: " << line << endl;
            // Example: Update amount (3rd column)
            cout << "Enter new amount: ";
            string newAmount;
            string name;
            cin >> newAmount;
            cout << "Enter new amount: ";
            cin >> name;
            row[2] = newAmount;  
            row[1] = name;
 
            line = join(row);
           
            updated = true;
        }
    lines.push_back(line);
        
       
    }
    inFile.close();
 
    if (updated) {
        ofstream outFile("C:\\Users\\vishvalingam.kumaran\\Documents\\sample\\sample.csv");
        for (const auto& l : lines) {
            outFile << l << "\n";
        }
        outFile.close();
        cout << "Record updated successfully!" << endl;
    } else {
        cout << "Sales ID not found." << endl;
    }
 
    return ;

}


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
    char updateOrdelete;
    cout << "Do you want to update or delete? y or n";
    cin >> updateOrdelete;
    
    if(updateOrdelete){
        UpdateOrDelete("sales.csv");
    }

    // sort();
    
    return 0;
}
