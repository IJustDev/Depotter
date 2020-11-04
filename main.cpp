#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "stockUpdater.h"

using namespace std;

struct Position
{
    double amount;
    string name;
    double buyPrice;
    double currentValue;
};
typedef Position Position;

struct Depot
{
    vector<Position> positions;
};
typedef Depot Depot;

auto split(const std::string& value, char separator)
    -> std::vector<std::string>
{
    std::vector<std::string> result;
    std::string::size_type p = 0;
    std::string::size_type q;
    while ((q = value.find(separator, p)) != std::string::npos) {
        result.emplace_back(value, p, q - p);
        p = q + 1;
    }
    result.emplace_back(value, p);
    return result;
}

int longestName(vector<Position> positions)
{
    int minLength = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        Position pos = positions[i];
        int length = pos.name.size();
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

Position newPosition(double amount, string name, double buyPrice, double currentValue)
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

Depot readDepotFromFile(string filename)
{
    Depot d;

    ifstream infile(filename);
    string content ((istreambuf_iterator<char>(infile)),
            (istreambuf_iterator<char>()));

    auto lines = split(content, '\n');
    for (string &line : lines) {
        if (line.rfind("#", 0) == 0) {
            continue;
        }
        vector<string> parts = split(line, ' ');
        if (parts.size() != 4) {
            continue;
        }
        double amount = stod(parts[0]);
        string name = parts[1];
        double buyPrice = stod(parts[2]);
        double currentValue = stod(parts[3]);
        d.positions.push_back(newPosition(amount, name, buyPrice, currentValue));
    }

    return d;
}

int main(int argc, char *argv[])
{
    char* filename = argv[1];
    if (filename == NULL) {
        cout << "Please provide a filename." << endl;
        return 127;
    }
    Depot d = readDepotFromFile(argv[1]);
    printDepot(d);
}
