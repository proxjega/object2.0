﻿#include "funkcijos.h"

int InputMark() {
    int value;
    while (true) {
        if (cin >> value && value <= 10 && value > -1) {
            return value;
        }
        else {
            wcout << L"\007Įveskite tinkamą pažymį nuo 1 iki 10 (0 - pabaigti)" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int InputMarkNum() {
    int value;
    while (true) {
        if (cin >> value && value > 0) {
            return value;
        }
        else {
            wcout << L"\007Įveskite tinkamą pažymių skaičių" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int InputExamMark() {
    int value;
    while (true) {
        if (cin >> value && value <= 10 && value > 0) {
            return value;
        }
        else {
            wcout << L"\007Įveskite tinkamą pažymį nuo 1 iki 10" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

float Mean(Student st) {
    float mean = 0;
    for (int i = 0; i < st.marks.size(); i++) {
        mean = mean + st.marks[i];
    }
    mean = (mean / st.marks.size()) * 0.4 + st.examMark * 0.6;
    return mean;
}

float Median(Student st) {
    float median = 0;
    sort(st.marks.begin(), st.marks.end());
    (st.marks.size() % 2 != 0) ? median = st.marks[st.marks.size() / 2] : median = (st.marks[st.marks.size() / 2] + st.marks[st.marks.size() / 2 - 1]) / 2.0;
    median = median * 0.4 + st.examMark * 0.6;
    return median;
}

bool CompareByName(Student a, Student b) {
    return a.name < b.name;
}

bool CompareBySurname(Student a, Student b) {
    return a.surname < b.surname;
}

bool CompareByVid(Student a, Student b) {
    return a.vid < b.vid;
}

bool CompareByMed(Student a, Student b) {
    return a.median < b.median;
}