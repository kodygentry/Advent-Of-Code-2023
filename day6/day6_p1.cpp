#include <iostream>
#include <fstream>
#include <sstream>  // Include this for stringstream
#include <vector>
#include <string>

using namespace std;

void readInput(const string& filename, vector<int>& times, vector<int>& distances) {
    ifstream infile(filename);
    string line;

    // Read times
    getline(infile, line);
    stringstream ss(line.substr(6)); // Skip "Time: "
    int time;
    while (ss >> time) {
        times.push_back(time);
    }

    // Read distances
    getline(infile, line);
    ss.clear();
    ss.str(line.substr(11)); // Skip "Distance: "
    int distance;
    while (ss >> distance) {
        distances.push_back(distance);
    }
}

int calculateWays(int time, int recordDistance) {
    int ways = 0;
    for (int holdTime = 1; holdTime < time; holdTime++) {
        int travelTime = time - holdTime;
        int distance = holdTime * travelTime;
        if (distance > recordDistance) {
            ways++;
        }
    }
    return ways;
}

int main() {
    vector<int> times, distances;
    readInput("input.txt", times, distances);

    long long totalWays = 1; // Use long long to avoid integer overflow
    for (size_t i = 0; i < times.size(); i++) {
        int ways = calculateWays(times[i], distances[i]);
        totalWays *= ways;
    }

    cout << "Total number of ways to beat the records: " << totalWays << endl;
    return 0;
}
