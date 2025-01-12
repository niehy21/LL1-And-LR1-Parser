#include "ToyFileIO.h"
#include <fstream>
#include <iostream>
#include <cstring>
std::string ToyFileIO::readFile(const std::string &path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Failed to open file \"path\"!" << std::endl;
        exit(EXIT_FAILURE);
    }

    using BufIter = std::istreambuf_iterator<char>;
    return std::string(BufIter(fin), BufIter());
}

void ToyFileIO::writeFile(const std::string &path, const std::string &content) {
    std::ofstream fout(path);
    if (!fout.is_open()) {
        std::cout << "Failed to open or create file \"path\"!" << std::endl;
        exit(EXIT_FAILURE);
    }

    fout << content;
    fout.close();
}

int ToyFileIO::compareFiles(const std::string &path1, const std::string &path2) {
    std::string file1 = readFile(path1),
                file2 = readFile(path2);
    return strcmp(file1.c_str(), file2.c_str());
}
