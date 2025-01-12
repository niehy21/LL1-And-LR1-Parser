#include "ToyFileIO/ToyFileIO.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main(void) {
    std::string sin = "Lorem ipsum dolor sit amet";
    cout << "Running tests of writing and reading files..." << endl;
    ToyFileIO::writeFile("test.data", sin);
    auto sout = ToyFileIO::readFile("test.data");
    if (sin != sout) {
        cout << "An error occurred while writing or reading files!" << endl;
        exit(EXIT_FAILURE);
    }
    if (remove("test.data") != 0) {
        cout << "Failed to delete test file!" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Success!" << endl;
    return 0;
}