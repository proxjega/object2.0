#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::wcout;

struct Student {
    std::wstring name;
    std::wstring surname;
    std::vector<int>marks;
    int examMark = 0;
    float median = 0;
    float vid = 0;
};