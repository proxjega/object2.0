﻿#include "mylibrary.h"

int main()
{
    FileGen(10);
	system("notepad \"studentai10.txt\"");
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);
    srand(time(NULL));

    vector<Student> vargsiukai, kietiakai;
    wstring names[5] = { L"name1", L"name2", L"name3", L"name4", L"name5" };
    wstring surnames[5] = { L"surname1", L"surname2", L"surname3", L"surname4", L"surname5" };
    float galutinisVid = 0;
    float mediana = 0;
    char menu;
    int markNum;
    int randExMark;
    int randMark;
    bool check = true;
    bool sortType = 0;
	wstring fileName;
	wifstream inputFile;
    wofstream outputFileK(L"kietiakuRezultatai.txt");
    outputFileK.imbue(std::locale(outputFileK.getloc(), new std::codecvt_utf8<wchar_t>));
    outputFileK.close();
    wofstream outputFileV(L"vargsiukuRezultatai.txt");
    outputFileV.imbue(std::locale(outputFileV.getloc(), new std::codecvt_utf8<wchar_t>));
    outputFileV.close();

    wcout << L"Pagal ką rušiuoti studentus? 1 - vidurkis, 0 - mediana\n";
    while (true) {
        try {
            sortType = InputSortType();
			break;
        }
        catch (const wchar_t* e) {
            wcerr << e << endl;
            continue;
        }
        catch (...) {
            wcerr << L"\007Nežinoma klaida" << endl;
			continue;
        }
    }


    while (check == true) {
        Student student;
        wcout << "---------------------------------\nMENU\n";
        wcout << L"1 - ranka įvesti duomenis\n2 - generuoti pažymius\n3 - generuoti ir pažymius ir studentų vardus, pavardės\n4 - įvesti duomenis iš failo\n5 - baigti darbą\n---------------------------------\n";
        cin >> menu;
        switch (menu)
        {
        case('1'):
			system("cls");
            wcout << L"Įveskite studento vardą:\n";
            wcin >> student.name;
            wcout << L"Įveskite studento pavardę:\n";
            wcin >> student.surname;
            wcout << L"Įveskite pažymius (0 - pabaigti)\n";
            while (true) {
                try {
                    int mark = InputMark();
                    if (mark == 0) {
                        if (student.marks.size() != 0) {
                            break;
                        }
                        else throw L"\007Įveskite bent vieną pažymį";
                        continue;
                    }
                    student.marks.push_back(mark);
                }
                catch (const wchar_t* e) {
					wcerr << e << endl;
                    continue;
                }
				catch (...) {
					wcerr << L"\007Nežinoma klaida" << endl;
					continue;
				}
            }
            wcout << L"Įveskite egzamino pažymį:\n";
            while (true) {
                try {
                    student.examMark = InputExamMark();
                    break;
                }
                catch (const wchar_t* e) {
                    wcerr << e << endl;
                    continue;
                }
                catch (...) {
                    wcerr << L"\007Nežinoma klaida" << endl;
                    continue;
                }
            }
            student.vid = Mean(student);
            student.median = Median(student);
			PushStudent(kietiakai, vargsiukai, student, sortType);
            break;
        case('2'):
            system("cls");
            wcout << L"Įveskite studento vardą:\n";
            wcin >> student.name;
            wcout << L"Įveskite studento pavardę:\n";
            wcin >> student.surname;
            wcout << L"Kiek pažymių generuoti?\n";
            while (true) {
				try {
					markNum = InputMarkNum();
					break;
				}
				catch (const wchar_t* e) {
					wcerr << e << endl;
					continue;
				}
				catch (...) {
					wcerr << L"\007Nežinoma klaida" << endl;
					continue;
				}
            }
            for (int i = 0; i < markNum; i++) {
                randMark = rand() % 10 + 1;
                wcout << L"Generuotas pažymys: " << randMark << "\n";
                student.marks.push_back(randMark);
            }
            randExMark = rand() % 10 + 1;
            wcout << L"Generuotas egzamino pažymys: " << randExMark << "\n";
            student.examMark = randExMark;
            student.vid = Mean(student);
            student.median = Median(student);
            PushStudent(kietiakai, vargsiukai, student, sortType);
            break;
        case('3'):
            system("cls");
            student.name = names[rand() % 5];
            wcout << L"Generuotas vardas: " << student.name << endl;
            student.surname = surnames[rand() % 5];
            wcout << L"Generuota pavardė: " << student.surname << endl;
            wcout << L"Kiek pažymiu generuoti?\n";
            while (true) {
                try {
                    markNum = InputMarkNum();
                    break;
                }
				catch (const wchar_t* e) {
					wcerr << e << endl;
					continue;
				}
				catch (...) {
					wcerr << L"\007Nežinoma klaida" << endl;
					continue;
				}
            }
            for (int i = 0; i < markNum; i++) {
                randMark = rand() % 10 + 1;
                wcout << L"Generuotas pažymys: " << randMark << "\n";
                student.marks.push_back(randMark);
            }
            randExMark = rand() % 10 + 1;
            wcout << L"Generuotas egzamino pažymys: " << randExMark << "\n";
            student.examMark = randExMark;
            student.vid = Mean(student);
            student.median = Median(student);
            PushStudent(kietiakai, vargsiukai, student, sortType);
            break;
        case('4'):
            system("cls");
            wcout << L"Iš kokio failo nuskaityti duomenis?\n\n";
			system("dir /b *.txt");
            wcin >> fileName;
            try {
                inputFile.open(fileName);
				if (!inputFile) {
					throw L"\007Failas nerastas";
				}
                Readfile(inputFile, kietiakai, vargsiukai, sortType);
				wcout << L"\nDuomenys nuskaityti.\n";
            }
			catch (const wchar_t* e) {
				wcerr << e << endl;
				break;
			}
			catch (...) {
				wcerr << L"\007Nežinoma klaida" << endl;
                break;
			}
            break;
        case('5'):
            system("cls");
            check = false;
            break;
        default:
            system("cls");
            wcout << L"\007Įveskite tinkamą skaičių nuo 1 iki 5\n";
            continue;
        }
    }
	wcout << L"Pagal ką rušiuoti studentus? (1 - pagal vardą, 2 - pagal pavardę, 3 - pagal galutinį balą (vid.), 4 - pagal galutinį balą (med.))\n";
    while (true) {
        cin >> menu;
        switch (menu)
        {
        case('1'):
            sort(kietiakai.begin(), kietiakai.end(), CompareByName);
            sort(vargsiukai.begin(), vargsiukai.end(), CompareByName);
            break;
        case('2'):
            sort(kietiakai.begin(), kietiakai.end(), CompareBySurname);
            sort(vargsiukai.begin(), vargsiukai.end(), CompareBySurname);
            break;
        case('3'):
            sort(kietiakai.begin(), kietiakai.end(), CompareByVid);
            sort(vargsiukai.begin(), vargsiukai.end(), CompareByVid);
            break;
        case('4'):
            sort(kietiakai.begin(), kietiakai.end(), CompareByMed);
            sort(vargsiukai.begin(), vargsiukai.end(), CompareByMed);
            break;
        default:
            wcout << L"\007Įveskite tinkama skaičių nuo 1 iki 4\n";
            continue;
        }
        break;
    }

    wstringstream output;
    output << setw(17) << left << L"Pavardė" << setw(17) << left << L"Vardas" << setw(20) << left << "Galutinis(vid.)" << setw(15) << left << "Galutinis(med.)\n";
    output << "-----------------------------------------------------------------------------------\n";
    for (int i = 0; i < kietiakai.size(); i++) {
        output << setw(17) << left << kietiakai[i].surname << setw(17) << left << kietiakai[i].name << setw(20) << left << setprecision(2) << fixed << kietiakai[i].vid << setw(15) << left << setprecision(2) << fixed << kietiakai[i].median << L"\n";
    }
    outputFileK.open("kietiakurezultatai.txt");
	outputFileK << output.str();
    outputFileK.close();
    system("notepad \"kietiakurezultatai.txt\"");

    wstringstream output1;
    output1 << setw(17) << left << L"Pavardė" << setw(17) << left << L"Vardas" << setw(20) << left << "Galutinis(vid.)" << setw(15) << left << "Galutinis(med.)\n";
    output1 << "-----------------------------------------------------------------------------------\n";
    for (int i = 0; i < vargsiukai.size(); i++) {
        output1 << setw(17) << left << vargsiukai[i].surname << setw(17) << left << vargsiukai[i].name << setw(20) << left << setprecision(2) << fixed << vargsiukai[i].vid << setw(15) << left << setprecision(2) << fixed << vargsiukai[i].median << L"\n";
    }
    outputFileV.open("vargsiukurezultatai.txt");
    outputFileV << output1.str();
    outputFileV.close();
    system("notepad \"vargsiukurezultatai.txt\"");
	return 0;
}
