#pragma once
#include <string>

class ToyFileIO {
public:
    static std::string readFile(const std::string &path);
    static void writeFile(const std::string &path, const std::string &content);
    static int compareFiles(const std::string &path1, const std::string &path2);
};