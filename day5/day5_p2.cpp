#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class SeedConverter {
public:
    SeedConverter(const string& inputFilePath, const string& outputFilePath) : inputFile(inputFilePath), outputFile(outputFilePath) {}

    void ProcessData() {
        ReadSeeds();
        while (ReadNextConversion()) {
            ApplyConversion();
        }
        FindMinimumSeedLocation();
    }

private:
    ifstream inputFile;
    ofstream outputFile;
    vector<pair<long long, long long>> seeds;
    vector<pair<long long, long long>> convertedSeeds;
    vector<long long> conversionParameters;

    void ReadSeeds() {
        string line;
        getline(inputFile, line);
        stringstream ss(line.substr(line.find(":") + 1));

        long long seed;
        while (ss >> seed) {
            seeds.emplace_back(seed, 1);
        }
        convertedSeeds = seeds;
    }

    bool ReadNextConversion() {
        string line;
        if (!getline(inputFile, line) || line.empty()) return false;

        stringstream ss(line);
        conversionParameters.clear();
        long long param;
        while (ss >> param) {
            conversionParameters.push_back(param);
        }
        return true;
    }

    void ApplyConversion() {
        long long destStart = conversionParameters[0];
        long long srcStart = conversionParameters[1];
        long long length = conversionParameters[2];

        for (auto& seedRange : seeds) {
            // Check if the range overlaps with the conversion range
            if (seedRange.first + seedRange.second <= srcStart || seedRange.first >= srcStart + length) continue;

            long long overlapStart = max(seedRange.first, srcStart);
            long long overlapEnd = min(seedRange.first + seedRange.second, srcStart + length);

            // Adjust the range in the converted seeds
            convertedSeeds.push_back({destStart + (overlapStart - srcStart), overlapEnd - overlapStart});
        }
    }

    void FindMinimumSeedLocation() {
        long long minimumLocation = LLONG_MAX;
        for (const auto& seed : convertedSeeds) {
            minimumLocation = min(minimumLocation, seed.first);
        }
        outputFile << "Minimum Seed Location: " << minimumLocation << endl;
    }
};

int main() {
    string inputFilePath = "input.txt";
    string outputFilePath = "output.txt";

    SeedConverter converter(inputFilePath, outputFilePath);
    converter.ProcessData();

    return 0;
}
