#include <iostream>
#include <fstream>
#include <string>

using namespace std;

pair<long long, long long> parseSingleRace(const string& line) {
    string numberStr;
    for (char ch : line) {
        if (isdigit(ch)) numberStr += ch;
    }
    return make_pair(stoll(numberStr), 0); // Returns the parsed number and initializes the second value to 0
}

long long calculateSingleRaceWays(long long time, long long record) {
    long long ways = 0;
    for (long long holdTime = 1; holdTime < time; ++holdTime) {
        if (holdTime * (time - holdTime) > record) {
            ways++;
        }
    }
    return ways;
}

int main() {
    ifstream file("input.txt");
    string timeLine, distanceLine;
    getline(file, timeLine);    // Read Time line
    getline(file, distanceLine); // Read Distance line
    file.close();

    pair<long long, long long> raceTime = parseSingleRace(timeLine);
    pair<long long, long long> raceRecord = parseSingleRace(distanceLine);

    long long totalWays = calculateSingleRaceWays(raceTime.first, raceRecord.first);

    cout << "Total ways to beat the record in the single race: " << totalWays << endl;
    return 0;
}
