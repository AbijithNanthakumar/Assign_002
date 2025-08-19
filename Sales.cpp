#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <filesystem>
#include <random>
using namespace std;
vector<int> use_id;

bool allitems = true;

// Function to split CSV line into tokens
vector<string> split(const string &line, char delimiter = ',')
{
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to join vector into CSV line
string join(const vector<string> &tokens, char delimiter = ',')
{
    string result;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        result += tokens[i];
        if (i < tokens.size() - 1)
            result += delimiter;
    }
    return result;
}

void Report(const string& filename) {
    ifstream report(filename);
    if (!report.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string header;
    getline(report, header); // Skip header

    map<string, vector<vector<string>>> groupedData;
    string line;

    while (getline(report, line)) {
        vector<string> row = split(line);
        if (row.size() >= 5) {
            groupedData[row[0]].push_back(row); // Group by date
        }
    }
    report.close();

    ofstream reportFile("report.txt");
    if (!reportFile.is_open()) {
        cerr << "Error creating report file!" << endl;
        return;
    }

    double grandTotal = 0.0;

    for (const auto& [date, entries] : groupedData) {
        reportFile << "Date          SaleID   ItemName   Quantity   Price   SalesAmount\n";
        reportFile << "-------------------------------------------------------------\n";

        double subtotal = 0.0;

        for (const auto& row : entries) {
            string saleID = row[1];
            string itemName = row[2];
            int quantity = stoi(row[3]);
            double price = stod(row[4]);
            double salesAmount = quantity * price;
            subtotal += salesAmount;

            reportFile << setw(13) << left << date << "| "
                       << setw(6) << right << saleID << " | "
                       << setw(8) << left << itemName << " | "
                       << setw(8) << right << quantity << " | "
                       << setw(5) << right << price << " | "
                       << setw(11) << right << salesAmount << "\n";
        }

        reportFile << "\nSubtotal for " << date << " is: " << subtotal << ".\n\n";
        grandTotal += subtotal;
    }

    reportFile << "=============================\n";
    reportFile << "Grand Total: " << grandTotal << "\n";
    reportFile << "=============================\n";

    reportFile.close();
    cout << "Report generated successfully in report.txt\n";
}



int generateUniqueID()
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1000, 9999);
 
    int id;
    do {
        id = dist(gen);
    } while (find(use_id.begin(), use_id.end(), id) != use_id.end());
 
    use_id.push_back(id);
    return id;
}




// Sorting the data by dates
void SortByDate(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string header;
    getline(inFile, header); // Read and preserve header

    vector<vector<string>> rows;
    string line;

    while (getline(inFile, line)) {
        vector<string> row = split(line);
        if (!row.empty()) {
            rows.push_back(row);
        }
    }
    inFile.close();

    // Sort rows by date (first column)
    sort(rows.begin(), rows.end(), [](const vector<string>& a, const vector<string>& b) {
        return b[0] > a[0]; // Lexicographical comparison of YYYY/MM/DD
    });

    ofstream outFile("temp.csv");
    outFile << header << "\n"; // Write header back
    for (const auto& row : rows) {
        outFile << join(row) << "\n";
    }
    outFile.close();

    cout << "CSV data sorted by date successfully!\n";
}

void Deleted(const string& filename,string salesIdToUpdate){
     ifstream inFile(filename);
    vector<string> lines;
    string line;
    bool deleted = false;
    while (getline(inFile, line))
        {

            vector<string> row = split(line);

            if (!row.empty() && row[1] == salesIdToUpdate)
            {
                cout << "Current record: " << line << endl;
                deleted=true;
            }
            else
            {
                lines.push_back(line);
            }
        }
        if (deleted)
        {
            ofstream outFile("sales.csv");
            for (const auto &l : lines)
            {
                outFile << l << "\n";
            }
            outFile.close();
            cout << "Record deleted successfully!" << endl;
        }
        else
        {
            cout << "Sales ID not found." << endl;
        }
       
}


void Update(const string& filename,string salesIdToUpdate){
    ifstream inFile(filename);
    vector<string> lines;
    string line;
    bool updated = false;

        while (getline(inFile, line))
        {

            vector<string> row = split(line);

            if (!row.empty() && row[1] == salesIdToUpdate)
            {
                cout << "Current record: " << line << endl;


                cout << "Enter the Unit price Date. \n";
                string unitpriceDate;
                cin >> unitpriceDate;
                cout << "Enter the Description \n";
                string Description;
                cin >> Description;
                cout << "Enter the item quantity.\n";
                string itemquantity;
                cin >> itemquantity;
                cout << "Enter the unitprice.\n";
                string unitprice;
                cin >> unitprice;
                row[0] = unitpriceDate;
                row[2] = Description;
                row[3] = itemquantity;
                row[4] = unitprice;

                line = join(row);

                updated = true;
            }
            lines.push_back(line);
            // inFile.close();
        }
        if (updated)
        {
            ofstream outFile("sales.csv");
            for (const auto &l : lines)
            {
                outFile << l << "\n";
            }
            outFile.close();
            cout << "Record updated successfully!" << endl;
        }
}



void UpdateOrDelete(const string &file)
{

     string salesIdToUpdate;
    cout << "Enter Sales ID to update: ";
    cin >> salesIdToUpdate;

    cout << "Do you want to Update or Delete (u or d).\n";
    char upordel;
    cin >> upordel;

    ifstream inFile(file);
    if (!inFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    if(upordel=='u'){
        Update("sales.csv",salesIdToUpdate);
    }

    if(upordel=='d'){
        Deleted("sales.csv",salesIdToUpdate);
    }
    
   
}

// date nomal validation:::::
bool isValidDateFormat(const string &date)
{
    if (date.length() > 10)
        return false;

    // Check digits in YYYY, MM, DD
    for (int i = 0; i < date.length(); ++i)
    {
        if (date[i]=='/' && date[i]=='/'){
            continue;
        }
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    return true;
}

// View.......
void View(const string &filename)
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
            View("sales.csv");
        }

        saleID = generateUniqueID();

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
}

int main()
{

    AddItems();
    char updateOrdelete;
    cout << "Do you want to update or delete? y or n";
    cin >> updateOrdelete;

    if (updateOrdelete == 'y')
    {
        UpdateOrDelete("sales.csv");
    }

    SortByDate("sales.csv");
    
    Report("sales.csv");

    return 0;
}
