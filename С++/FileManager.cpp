#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;
string error = "|ERROR. Incorrect input|\n";

bool IsFile(wstring dir) {
    wifstream trying(dir, ios_base::in);

    if (trying.is_open()) {
        trying.close();
        return 1;
    }
    return 0;
}

bool IsDataDir(wstring data) {
    WIN32_FIND_DATA FFD;
    HANDLE HD = FindFirstFileW((data+L"*").c_str(), &FFD);
    if (HD != INVALID_HANDLE_VALUE)
        return 1;
    return 0;
}

bool IsDir(wstring dir) {
    WIN32_FIND_DATA FFD;

    HANDLE HD=FindFirstFileW((dir + L"*").c_str(), &FFD);
    DWORD attrib = FFD.dwFileAttributes;

    if (attrib & FILE_ATTRIBUTE_DIRECTORY) {
        return 1;
    }
    else {
        return 0;
    }
}

void Deleater(wstring& dir) {
    wstring temp;
    for (int i = dir.size(); dir[i]!=L'\\'|| dir[i] != L'/'; i--) {

    }
}

wstring FileManagerForTXT()
{
    wcin.imbue(locale(".866"));
    wcout.imbue(locale(".866"));

    WIN32_FIND_DATA FFD;
    HANDLE HD;
    DWORD attrib;

    wstring dir;
    wstring dir_t;
    wstring dir_t1;

    wcout << "Enter path: "<<endl;
    getline(wcin, dir);
    while (!IsDataDir(dir)) {
        cout << error;
        wcout << "Enter path: "<<endl;
        getline(wcin, dir);
    }

    do {

        dir_t = dir + L"*";

        HD = FindFirstFileW(dir_t.c_str(), &FFD);
        if (HD != INVALID_HANDLE_VALUE) {
            do {
                attrib = FFD.dwFileAttributes;
                if(attrib & FILE_ATTRIBUTE_DIRECTORY)
                    wcout << L"|------->" << FFD.cFileName << L"\\\\..." << endl;
                //wcout << dir + FFD.cFileName << endl;//dir + filename;

            } while (FindNextFile(HD, &FFD));

            dir_t = dir + L"*.txt";
            HD = FindFirstFileW(dir_t.c_str(), &FFD);
            if (HD != INVALID_HANDLE_VALUE) {
                do {
                    wcout << L"|------->" << FFD.cFileName << endl;
                    //wcout << dir + FFD.cFileName << endl;//dir + filename;
                } while (FindNextFile(HD, &FFD));
            }

            wcout << "Select file: ";
            getline(wcin, dir_t);
            wstring dir_t2 = dir + dir_t;
            if (IsFile(dir_t2))
                return dir_t2;
            dir_t1 = dir_t2;

            while (!IsDir(dir_t1)) {
                cout << error;
                wcout << "Select file: ";
                getline(wcin, dir_t);
                wstring dir_t3 = dir + dir_t;
                if(IsFile(dir_t3))
                    return dir_t3;
                dir_t1 = dir_t3;
            } 
            wcout << endl;
            if ((wstring)dir_t == L".." || (wstring)dir_t == L".");
            else
                dir = dir_t1 + L"\\\\";
            wcout << dir;
            wcout << endl;
        }
    } while(1);
}

int main() {
    string repeat="Y";
    do { 
       wcout << FileManagerForTXT() << endl;
    } while (repeat == "Y");
}