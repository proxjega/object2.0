#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <limits>
#include <fstream>
#include <sstream>
#include <chrono>
#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>
#include <deque>
#include <list>

using std::deque;
using std::list;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::sort;
using std::ifstream;
using std::stringstream;
using std::left;
using std::setw;
using std::setprecision;
using std::fixed;
using std::wcout;
using std::wcin;
using std::wstringstream;
using std::wstring;
using std::wifstream;
using std::wofstream;
using std::wcerr;
using std::cerr;


struct Student {
    std::wstring name;
    std::wstring surname;
    std::vector<int>marks;
    int examMark = 0;
    float median = 0;
    float vid = 0;
};

int InputMark();
int InputMarkNum();
int InputExamMark();
int InputTestNum();
int InputStrategy();
float Mean(Student st);
float Median(Student st);
bool CompareByName(Student a, Student b);
bool CompareBySurname(Student a, Student b);
bool CompareByVid(Student a, Student b);
bool CompareByMed(Student a, Student b);
void FileGen(int n);
bool InputSortType();

