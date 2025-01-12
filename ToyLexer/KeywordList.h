#pragma once

#include <vector>
#include <string>

using Keyword = std::string;

struct KeywordList : std::vector<Keyword> {
    KeywordList() : std::vector<Keyword>({
        "var",
        "input",
        "print",
        "if",
        "while"
    }) {
    }
};
