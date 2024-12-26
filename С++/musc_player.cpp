#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <thread>
#include <regex>
#pragma comment(lib, "winmm.lib")

using namespace std;
wstring error = L"|ERROR. Incorrect input|\n";
regex reg_int("[0-9]{0,2}||100");
regex reg_bal("[-]?[0-9]{0,2}||[-]?100");
enum mode { unknown, open, playing, paused, stopped };


int GetVol(wstring what)
{
    string user_data;
    wcout << what;
    getline(cin, user_data);
    while (!regex_match(user_data.c_str(), reg_int))
    {
        wcout << error;
        wcout << what;
        getline(cin, user_data);
    }
    return stoi(user_data) * 10;
}

int GetBal(wstring what)
{
    string user_data;
    wcout << what;
    getline(cin, user_data);
    while (!regex_match(user_data.c_str(), reg_bal))
    {
        wcout << error;
        wcout << what;
        getline(cin, user_data);
    }
    return stoi(user_data) * 10;
}

class MUSC
{
private:
    wstring directory;
    unsigned int length;
    int volume;
    int balance;
    LPWSTR buff = const_cast<LPWSTR>(to_wstring(0).c_str());
public:
    MUSC() : length(0), volume(1000), balance(0)
    {

    };

    void Close()
    {
        wstring temp = L"close " + directory;
        mciSendString(temp.c_str(), NULL, 0, 0);
    }

    void Open(wstring directory)
    {
        Close();
        this->directory = directory;
        wstring temp = L"open \"" + directory + L"\" type mpegvideo alias " + directory;
        mciSendString(temp.c_str(), NULL, 0, 0);
        length = Length(true);
    }

    MUSC(wstring directory) : volume(1000), balance(0)
    {
        Open(directory);
    };

    ~MUSC()
    {
        Close();
    }

    void Play(int pos = 0)
    {
        wstring temp = L"play \"" + directory + L"\" from " + to_wstring(pos);
        mciSendString(temp.c_str(), NULL, 0, 0);
    }

    void Seek(int pos)
    {

        wstring temp = L"seek \"" + directory + L"\" to " + to_wstring(pos);
        mciSendString(temp.c_str(), NULL, 0, 0);

    }

    void Pause()
    {
        wstring temp = L"pause \"" + directory + L"\"";
        mciSendString(temp.c_str(), NULL, 0, 0);
    }

    void Resume()
    {
        wstring temp = L"resume \"" + directory + L"\"";
        mciSendString(temp.c_str(), NULL, 0, 0);
    }

    void Stop()
    {
        wstring temp = L"stop \"" + directory + L"\"";
        mciSendString(temp.c_str(), NULL, 0, 0);
    }

    int Volume()
    {
        return volume;
    }

    void Volume(int vol)
    {
        vol = (vol < 0 ? 0 : (vol > 1000 ? 1000 : vol));

        wstring temp = L"setaudio \"" + directory + L"\" volume to " + to_wstring(vol);
        mciSendString(temp.c_str(), NULL, 0, 0);

    }

    int Balance()
    {
        return balance;
    }

    void Balance(int bal)
    {
        bal = (bal < -1000 ? -1000 : (bal > 1000 ? 1000 : bal));

        wstring temp = L"setaudio " + directory + L"left volume to " + to_wstring(bal < 0 ? 1000 : 1000 - bal);
        mciSendString(temp.c_str(), NULL, 0, 0);
        temp = L"setaudio " + directory + L"right volume to " + to_wstring(bal > 0 ? 1000 : 1000 + bal);
        mciSendString(temp.c_str(), NULL, 0, 0);

    }

    int Length(bool refresh = false)
    {
        if (refresh)
        {
            wstring temp = L"status \"" + directory + L"\" length";
            mciSendString(temp.c_str(), buff, 128, NULL);
            int t = _wtoi(buff);
            return t;
        }
        else
        {
            return length;
        }
    }

    int Position()
    {

        wstring temp = L"status \"" + directory + L"\" position";
        mciSendString(temp.c_str(), buff, 16, 0);
        //wcout << buff << endl;
        long int t = _wtoi(buff);
        return t;
    }

    int Position(int ms)
    {
        if (status() == playing || status() == paused)
            Seek(ms);
        else
            Play(ms);
    }

    mode status()
    {

        wstring temp = L"status \"" + directory + L"\" mode";
        mciSendString(temp.c_str(), buff, 8, 0);
        mode ret;
        if (wcscmp(buff, L"open") == 0) ret = open;
        else if (wcscmp(buff, L"playing") == 0) ret = playing;
        else if (wcscmp(buff, L"paused") == 0) ret = paused;
        else if (wcscmp(buff, L"stopped") == 0) ret = stopped;
        else ret = unknown;

        return ret;
    }
};

bool IsDataDir(wstring data) {
    WIN32_FIND_DATA FFD;
    HANDLE HD = FindFirstFileW((data + L"*").c_str(), &FFD);
    if (HD != INVALID_HANDLE_VALUE)
        return 1;
    return 0;
}

wstring dir;
vector<wstring> names;

void Explorer(vector<wstring>& directory) {
    wcin.imbue(locale(".866"));
    wcout.imbue(locale(".866"));

    WIN32_FIND_DATA FFD;
    HANDLE HD;
    DWORD attrib;
    wstring cur_dir;

    wcout << "Enter path: " << endl;
    getline(wcin, dir);
    while (!IsDataDir(dir)) {
        wcout << error;
        wcout << "Enter path: " << endl;
        getline(wcin, dir);
    }

    cur_dir = dir + L"\\*.mp3";
    HD = FindFirstFileW(cur_dir.c_str(), &FFD);
    int i = 1;
    if (HD != INVALID_HANDLE_VALUE) {
        do {

            //СПОСОБ ОБОЙТИ ПРОБЕЛЫ ДЛЯ mciSendString()
            //ИНИЦИАЛИЗИРУЕМ LPWSTR ЛЕВЫМ WSTRING
            wstring directory1 = dir + L"\\" + FFD.cFileName;
            LPWSTR directory2 = const_cast<LPWSTR>((directory1).c_str());
            GetShortPathNameW(directory1.c_str(), directory2, 2048);
            directory1 = directory2;
            wcout << directory1 << endl;
            directory.push_back(directory2);
            wcout << i << L") " << FFD.cFileName << endl;//dir + filename;
            names.push_back(to_wstring(i) + L") " + FFD.cFileName);
            ++i;
        } while (FindNextFile(HD, &FFD));

    }
}

void ClearWindow(MUSC& record, int& rec_num, int& vol, int& bal, int& mode, bool& repeat) {

    int rn = rec_num, v = vol, b = bal, m = -1;
    bool r = repeat;

    map <int, wstring> mods;
    mods[0] = L"UNKNOWN";
    mods[1] = L"OPEN";
    mods[2] = L"PLAYING";
    mods[3] = L"PAUSED";
    mods[4] = L"STOPPED";
    map <bool, wstring> rep;
    rep[0] = L"REPEAT: OFF";
    rep[1] = L"REPEAT: ON";

    while (1) {

        Sleep(100);
        if (rn != rec_num || v != vol || b != bal || m != mode || r != repeat) {
            rn = rec_num;
            v = vol;
            b = bal;
            m = mode;
            r = repeat;

            //system("cls");
            wcout << dir << endl;
            for (int i = 0; i < names.size(); i++) {
                wcout << names[i] << endl;
            }
            wcout << "_________________________________________________________________________________" << endl;
            wcout << mods[mode] + L": " + names[rec_num] << endl;
            wcout << L"VOLUME: " << vol / 10 << L"|" + rep[repeat] << endl;
            wcout << "_________________________________________________________________________________" << endl;
            wcout << L"MACHINE >> WAITING COMMANDS,ENTER \"!HELP\" TO GET LIST\n";
        }
    }
}

void Player(vector<wstring> directories, int& rec_num, int& vol, int& bal, int& mode, bool& repeat) {
    for (; rec_num < directories.size();) {
        int rn = rec_num, v = vol, b = bal, m = mode;
        MUSC record(directories[rec_num]);
        wcout << rec_num << endl;
        thread t2(ClearWindow, ref(record), ref(rec_num), ref(vol), ref(bal), ref(mode), ref(repeat));
        t2.detach();
        record.Play();
        while ((record.status() == 2 || record.status() == 3) && rn == rec_num) {
            Sleep(100);
            if (b != bal) {
                record.Balance(bal);
                b = bal;
            }
            if (v != vol) {
                record.Volume(vol);
                v = vol;
            }
            if (m != mode) {
                if (mode == 3) record.Pause();
                if (mode == 2) record.Resume();
                m = mode;
            }
        }
        if (repeat == 0 && rn == rec_num) rec_num++;
        if (rec_num == directories.size()) rec_num = 0;
        /*wcout << record.status();*/
    }
}

int main() {
    wcin.imbue(locale(".866"));
    wcout.imbue(locale(".866"));

    vector<wstring> directories;
    Explorer(directories);

    map <int, wstring> mods;
    mods[0] = L"unknown";
    mods[1] = L"open";
    mods[2] = L"playing";
    mods[3] = L"paused";
    mods[4] = L"stopped";

    int rec_num = 0, vol = 1000, bal = 0, mode = 2;
    bool repeat = false;

    thread t_1(Player, ref(directories), ref(rec_num), ref(vol), ref(bal), ref(mode), ref(repeat));
    t_1.detach();

    wstring temp;
    wstring HELP = L"MACHINE >>\n!PAUSE\n!RESUME\n!PREVIOUS\n!NEXT\n!SET_VOLUME\n!REPEAT_ON\n!REPEAT_OFF\n!STOP\n";
    wcout << L"MACHINE >> WAITING COMMANDS,ENTER \"!HELP\" TO GET LIST\n";
    do {
        getline(wcin, temp);
        if (temp == L"!HELP") wcout << HELP;
        else if (temp == L"!PAUSE") mode = 3;
        else if (temp == L"!RESUME") mode = 2;
        else if (temp == L"!PREVIOUS")
            if (rec_num > 0) rec_num -= 1;
            else rec_num = directories.size() - 1;
        else if (temp == L"!NEXT")
            if (rec_num < directories.size() - 1) rec_num += 1;
            else rec_num = 0;
        else if (temp == L"!SET_VOLUME") vol = GetVol(L"MACHINE >> ENTER COUNT: ");
        else if (temp == L"!REPEAT_ON")
            if (repeat == false) repeat = true;
            else wcout << error;
        else if (temp == L"!REPEAT_OFF")
            if (repeat == true) repeat = false;
            else wcout << error;
        //else if (temp == "!SET_BALANCE") bal = GetBal("MACHINE >> ENTER COUNT: ");
        else if (temp == L"!STOP");
        else wcout << error;

    } while (temp != L"!STOP");
    return 0;
    //Powered by Berestov Ivan
}