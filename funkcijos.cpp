﻿#include "funkcijos.h"

int InputMark() {
    int value;
    while (true) {
        if (cin >> value && value <= 10 && value > -1) {
            return value;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw L"\007Įveskite tinkamą pažymį nuo 1 iki 10 (0 - pabaigti)";
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
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw L"\007Įveskite tinkamą pažymių skaičių";
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
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw L"\007Įveskite tinkamą pažymį nuo 1 iki 10";
        }
    }
}

bool InputSortType() {
    bool value;
    while (true) {
        if (cin >> value) {
            return value;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw L"\007Įveskite 0 arba 1";
        }
    }
}

int InputTestNum() {
    int value;
    while (true) {
        if (cin >> value && value <= 10000000 && value > 0) {
            return value;
        }
        else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw L"\007Įveskite tinkamą įrašų skaičių";
        }
    }
}

float Mean(Student st) {
    return (std::accumulate(st.marks.begin(), st.marks.end(), 0) * 1.0) / (st.marks.size() * 1.0);
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

template <class T>
void Readfile(std::wifstream& inputFile, T& grupe) { //skaitymas is failo
    wstring temp;
    getline(inputFile, temp);
    wstringstream ss(temp);
    int counter = 0;
    while (ss >> temp) {
        counter++;
    }
    wstringstream buffer;
    buffer << inputFile.rdbuf();
    inputFile.close();
    while (buffer) {
        if (buffer.eof()) {
            break;
        }
        Student student;
        buffer >> student.surname >> student.name;
        int mark = 0;
        for (int i = 0; i < counter - 3; i++) {
            buffer >> mark;
            student.marks.push_back(mark);
        }
        buffer >> mark;
        student.examMark = mark;
        student.vid = Mean(student);
        student.median = Median(student);
        grupe.push_back(student);
    }
}

template <class arr1, class arr2, class arr3>
void SortStudentsInGroups(arr1& kietiakai, arr2& vargsiukai, arr3 group, bool sortType) { //sorting function
    for (int i = 0; i < group.size(); i++) {
        if (sortType == 1) {
            if (group[i].vid < 5.0) {
                vargsiukai.push_back(group[i]);
            }
            else {
                kietiakai.push_back(group[i]);
            }
        }
        else {
            if (group[i].median < 5.0) {
                vargsiukai.push_back(group[i]);
            }
            else {
                kietiakai.push_back(group[i]);
            }
        }
    }
    kietiakai.shrink_to_fit();
	vargsiukai.shrink_to_fit();
}

void FileGen(int n) {
    string name;
    name = "studentai" + std::to_string(n) + ".txt";
	std::ofstream file(name);
    std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 10);
    file << setw(17) << left << "Pavarde" << setw(17) << left << "Vardas" << setw(10) << left << "ND1"
        << setw(10) << left << "ND2" << setw(10) << left << "ND3" << setw(10) << left << "ND4" << setw(10) << left << "ND5" << setw(9) << left << "Egzaminas";
    for (int i = 0; i < n; i++) {
        file << endl;
        file << setw(17) << left << "Pavarde" + std::to_string(i+1) << setw(17) << left << "Vardas" + std::to_string(i+1)
            << setw(10) << left << dist(mt) << setw(10) << left << dist(mt) << setw(10) << left << dist(mt) << setw(10) << left << dist(mt)
            << setw(10) << left << dist(mt) << dist(mt);
    }
	file.close();
}

void PrintIntoFile(vector<Student> group, wstring fileName) {
    wstringstream output;
    output << setw(17) << left << L"Pavardė" << setw(17) << left << L"Vardas" << setw(20) << left << "Galutinis(vid.)" << setw(15) << left << "Galutinis(med.)\n";
    output << "-----------------------------------------------------------------------------------\n";
    for (int i = 0; i < group.size(); i++) {
        output << setw(17) << left << group[i].surname << setw(17) << left 
            << group[i].name << setw(20) << left << setprecision(2) << fixed
            << group[i].vid << setw(15) << left << setprecision(2) << fixed << group[i].median << L"\n";
    }
    std::wofstream outputFile(fileName);
    outputFile.imbue(std::locale(outputFile.getloc(), new std::codecvt_utf8<wchar_t>));
    outputFile << output.str();
    outputFile.close();
}

void TestFunction(vector<Student>& grupe, vector<Student>& vargsiukai, vector<Student>& kietiakai) {
    wcout << L"Iš kiek įrašų testuoti programą?";
    int testNum;
    while (true) {
        try {
            testNum = InputTestNum();
			break;
        }
        catch (const wchar_t* e) {
            std::wcerr << e << endl;
            continue;
        }
        catch (...) {
            std::wcerr << L"\007Nežinoma klaida" << endl;
            continue;
        }
    }

    string inputFileName = "studentai" + std::to_string(testNum) + ".txt";
    wifstream inputFile(inputFileName);
	if (!inputFile) {
		std::wcerr << L"Failas nerastas\n";
        return;
	}
    std::ofstream testFile("tyrimas.txt", std::ios::app);
    wcout << L"Testo pradzia\n";
    testFile << "Programos veikimas: \n";

	std::chrono::time_point<std::chrono::system_clock> programStart = std::chrono::system_clock::now();
	Readfile(inputFile, grupe);
	grupe.shrink_to_fit();
    std::chrono::time_point<std::chrono::system_clock> endReading = std::chrono::system_clock::now();

    std::chrono::time_point<std::chrono::system_clock> startSorting = std::chrono::system_clock::now();
    SortStudentsInGroups(kietiakai, vargsiukai, grupe, 1);
	grupe.clear();
	grupe.shrink_to_fit();
    sort(kietiakai.begin(), kietiakai.end(), CompareByVid);
    sort(vargsiukai.begin(), vargsiukai.end(), CompareByVid);
    std::chrono::time_point<std::chrono::system_clock> endSorting = std::chrono::system_clock::now();

    std::chrono::time_point<std::chrono::system_clock> startOutput = std::chrono::system_clock::now();
	wstring outputFileName = L"vargsiukuRezultatai.txt";
    PrintIntoFile(vargsiukai, outputFileName);
    outputFileName = L"kietiakuRezultatai.txt";
    PrintIntoFile(kietiakai, outputFileName);
    std::chrono::time_point<std::chrono::system_clock> endOutput = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> programEnd = std::chrono::system_clock::now();

    testFile << "Duomenu nuskaitymas is " << testNum << " irasu: " << std::chrono::duration<double>(endReading - programStart).count() << " s\n";
    testFile << "Studentu rusiavimas i 2 grupes is " << testNum << " irasu: " << std::chrono::duration<double>(endSorting - startSorting).count() << " s\n";
    testFile << "Surusiuotu studentu isvedimas is " << testNum << " irasu: " << std::chrono::duration<double>(endOutput - startOutput).count() << " s\n";
    testFile << "Visos programos veikimo laikas is " << testNum << " irasu: " << std::chrono::duration<double>(programEnd - programStart).count() << " s\n\n";
	
    wcout << L"Testas baigtas. Patikrinkite tyrimas.txt\n";
}