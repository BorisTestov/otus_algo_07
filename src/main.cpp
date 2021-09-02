#include "tester.h"
#include <sstream>
#include <chrono>
#include <cassert>

void generateTest()
{

        const unsigned long N = 1e9;
        const unsigned short MAX_NUMBER = 65535;
        std::string testNumber = "0";
    {
        char delimiter = '\n';

        unsigned long counters[MAX_NUMBER + 1] = {0};

        auto start = std::chrono::high_resolution_clock::now();
        std::ofstream inputFile("../tests/test" + testNumber + ".in");
        unsigned short number = rand() % (MAX_NUMBER + 1);
        inputFile << number;
        counters[number]++;
        for (unsigned long i = 1; i < N; ++i) {
            number = rand() % (MAX_NUMBER + 1);
            counters[number]++;
            inputFile << delimiter << number;
        }
        inputFile.close();
        auto stop = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Input file written: " << elapsed << " ms\n";
        start = std::chrono::high_resolution_clock::now();
        std::ofstream outputFile("../tests/test" + testNumber + ".out");

        unsigned short maxInArray = 0;
        for (auto i = 0; i < MAX_NUMBER + 1; ++i)
        {
            if (counters[i] == 0) continue;
            maxInArray = i;
        }
        for (auto i = 0; i < MAX_NUMBER + 1; ++i) {
            std::stringstream data;
            if (counters[i] == 0) continue;
            data << i;
            for (unsigned long j = 1; j < counters[i]; ++j) {
                data << delimiter << i;
            }
            if (i != maxInArray) data << "\n";
            outputFile << data.str();
        }
        outputFile.close();
        stop = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Output file written: " << elapsed << " ms\n";
    }
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::ifstream inputFile("../tests/test" + testNumber + ".in");
        unsigned long linesInInputFile = std::count(std::istreambuf_iterator<char>(inputFile),
                                                    std::istreambuf_iterator<char>(), '\n');
        inputFile.close();
        std::ifstream outputFile("../tests/test" + testNumber + ".out");
        unsigned long linesInOutputFile = std::count(std::istreambuf_iterator<char>(outputFile),
                                                    std::istreambuf_iterator<char>(), '\n');
        outputFile.close();
        assert(linesInInputFile == (N - 1)); // -1 -> No new line at the end of file
        assert(linesInOutputFile == (N - 1));
        auto stop = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "File lengths correct: " << elapsed << " ms\n";
    }
}

int main() {
    generateTest();
    return 0;
}
