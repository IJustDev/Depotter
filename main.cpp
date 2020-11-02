#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Position
{
    double amount;
    char *name;
    double buyPrice;
    double currentValue;
};
typedef Position Position;

struct Depot
{
    vector<Position> positions;
};
typedef Depot Depot;

int longestName(vector<Position> positions)
{
    int minLength = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        Position pos = positions[i];
        int length = strlen(pos.name);
        if (minLength <= length)
        {
            minLength = length + 1;
        }
    }
    return minLength;
}

string pad(string input, int length)
{
    int size = input.length();
    int missing = length - size;
    string missingString = "";
    for (int i = 0; i < missing; i++)
    {
        missingString = missingString + " ";
    }
    return input + missingString;
}

double getCurrentValue(Depot depot)
{
    double sum = 0;
    for (int i = 0; i < depot.positions.size(); i++)
    {
        Position pos = depot.positions[i];
        sum += pos.currentValue * pos.amount;
    }
    return sum;
}

double getBuyPrice(Depot depot)
{
    double sum = 0;
    for (int i = 0; i < depot.positions.size(); i++)
    {
        Position pos = depot.positions[i];
        sum += pos.buyPrice * pos.amount;
    }
    return sum;
}

Position newPosition(double amount, char *name, double buyPrice, double currentValue)
{
    Position pos;
    pos.amount = amount;
    pos.name = name;
    pos.buyPrice = buyPrice;
    if (currentValue == -1)
    {
        currentValue = buyPrice;
    }
    pos.currentValue = currentValue;
    return pos;
}

double calculatePerformance(Depot depot)
{
    double buyValue = getBuyPrice(depot);
    double currentValue = getCurrentValue(depot);

    return (currentValue / buyValue) * 100 - 100;
}

void printDepot(Depot depot)
{
    cout << "Your Depot" << endl;
    cout << pad("Amount", 20) << " | " << pad("Name", 20) << " | " << pad("Buy Price", 15) << " | " << pad("Current Value", 15) << " | "
         << "Performance" << endl;
    for (int i = 0; i < depot.positions.size(); i++)
    {
        Position pos = depot.positions[i];
        cout
            << pad(to_string(pos.amount), 20) << " | "
            << pad(pos.name, 20) << " | "
            << pad(to_string(pos.buyPrice), 15) << " | "
            << pad(to_string(pos.currentValue), 15) << " | "
            << ((pos.currentValue / pos.buyPrice) - 1) * 100 << " %"
            << endl;
    }
    cout << endl
         << pad("Buy Price", 20) << " | " << to_string(getBuyPrice(depot)) << endl;
    cout << pad("Current Value", 20) << " | " << to_string(getCurrentValue(depot)) << endl;

    cout << pad("> Plain W/L", 20) << " | " << to_string(getCurrentValue(depot) - getBuyPrice(depot)) << endl;

    cout << endl
         << pad("Avg. Performance", 20) << " | " << calculatePerformance(depot) << " %" << endl;
}

void readDepotFromFile(string filename)
{
    ifstream infile(filename);

    string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b))
        {
            break;
        } // error

        // process pair (a,b)
    }
    double amount, buyPrice, currentValue;
    char *name;
}

int main()
{
    Depot d;
    // readDepotFromFile("depot.txt"); Coming soon
    d.positions.push_back(newPosition(100, "Acme Inc", 1.37, 4.20));
    printDepot(d);
}