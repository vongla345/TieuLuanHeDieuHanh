#pragma once
#include "Process.h"
#include "GiaoDien.h"

int main() 
{ 
    /*
    Process pArr[100], p;
    int n, x, cpu, arrival, io = -1, ioStart = -1;
    bool IO = false;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "\nDo the processes have IO? (note: 1 mean 'yes', 0 mean 'no') ";
    cin >> x;
    if (x == 1)
        IO = true;

    for (int i = 0; i < n; i++) {
        cout << "\nProcess: " << i + 1 << '\n';
        cout << "===> Burst time: ";
        cin >> cpu;
        cout << "===> Arrival time: ";
        cin >> arrival;
        if (IO) {
            cout << "===> IO burst time: ";
            cin >> io;
            cout << "===> IO start time: ";
            cin >> ioStart;
        }
        Process process(i + 1, cpu, arrival, io, ioStart, IO);
        pArr[i] = process;
    }

    p.printGantt(pArr, n, IO);
    */

    int focus = 0;
    string menu[] = {
        "Bat Dau",
        "Thoat"
    };
    int len = sizeof(menu) / sizeof(menu[0]);
    MenuChinh();
    LuaChon(Menu(menu, focus, len), menu, focus, len);
}