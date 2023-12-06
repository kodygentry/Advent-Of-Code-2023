#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class SeedMapper {
public:
    SeedMapper(const string& inputFile, const string& outputFile) : inputFilePath(inputFile), outputFilePath(outputFile) {}

    void RunConversion() {
        ReadSeeds();
        ProcessConversions();
        FindMinimumSeedLocation();
    }

private:
    string inputFilePath, outputFilePath;
    vector<long long> originalSeeds, convertedSeeds;

    void ReadSeeds() {
        ifstream inFile(inputFilePath);
        string line;
        if (getline(inFile, line)) {
            ParseSeeds(line);
        }
        inFile.close();
        convertedSeeds = originalSeeds;
    }

    void ParseSeeds(const string& line) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) return;
        
        size_t startPos = colonPos + 1;
        while (startPos < line.size()) {
            size_t endPos;
            long long seed = stoll(line.substr(startPos), &endPos);
            originalSeeds.push_back(seed);
            startPos += endPos;
        }
    }

    void ProcessConversions() {
        ifstream inFile(inputFilePath);
        string line;
        while (getline(inFile, line)) {
            if (line.empty() || !isdigit(line[0])) continue;
            ApplyConversion(line);
        }
        inFile.close();
    }

    void ApplyConversion(const string& line) {
        istringstream iss(line);
        long long dest, src, range;
        iss >> dest >> src >> range;

        for (size_t i = 0; i < originalSeeds.size(); ++i) {
            if (originalSeeds[i] >= src && originalSeeds[i] < src + range) {
                convertedSeeds[i] = dest + originalSeeds[i] - src;
            }
        }
    }

    void FindMinimumSeedLocation() {
        ofstream outFile(outputFilePath);
        long long minLocation = *min_element(convertedSeeds.begin(), convertedSeeds.end());
        outFile << "Minimum Seed Location: " << minLocation << endl;
        outFile.close();
    }
};

int main() {
    SeedMapper mapper("input.txt", "output.txt");
    mapper.RunConversion();
    return 0;
}
